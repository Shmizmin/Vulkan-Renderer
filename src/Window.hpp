#pragma once

#include "./Event.hpp"
#include "./Extern.hpp"

#include <cstdint>
#include <cassert>
#include <functional>

#include <windows.h>
#include <windowsx.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

#define WM_RESHAPE (WM_USER + 0)
#define WM_ACTIVE  (WM_USER + 1)

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_ERASEBKGND:
			if (frameCount > 1) std::invoke(frameDraw);
			return 0;

		case WM_CLOSE:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
			if (frameCount > 1) std::invoke(frameDraw);
			return 0;
		
		case WM_GETMINMAXINFO:
			return 0;

		case WM_EXITSIZEMOVE:
		{ 
			PostMessage(hWnd, WM_RESHAPE, 0, 0);
			break;
		}
		
		case WM_ACTIVATE:
		{ 
			PostMessage(hWnd, WM_ACTIVE, wParam, lParam);
			break;
		}

		case WM_SETCURSOR:
		{
			if (LOWORD(lParam) == HTCLIENT)
			{
				SetCursor(NULL);
				return 0;
			}
		
			else break;
		}
		
		default: break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

struct Window32
{
public:
	HINSTANCE hInstance;
	HWND hWnd;

	struct { std::int16_t x; std::int16_t y; }mousepos = {};
	bool mouse[5] = {};
	bool keys[256] = {};

	bool running = false;
	bool textinput = false;
	bool has_focus = false;
	EventFIFO<3> eventFIFO;

	struct shape_t { std::int16_t x; std::int16_t y; std::int16_t width; std::int16_t height; } shape = {};
	VkInstance  instance = 0;
	VkSurfaceKHR surface = 0;

	EventType MouseEvent(eAction action, std::int16_t x, std::int16_t y, uint8_t btn)
	{
		mousepos = { x, y };
		if (action != eMOVE) mouse[btn] = (action == eDOWN);
		EventType e = { EventType::MOUSE, {action, x, y, btn} };
		return e;
	}

	EventType KeyEvent(eAction action, uint8_t key)
	{
		keys[key] = (action == eDOWN);
		EventType e = { EventType::KEY };
		e.key = { action, (eKeycode)key };
		return e;
	}

	EventType TextEvent(const char* str)
	{
		EventType e = { EventType::TEXT };
		e.text.str = str;
		return e;
	}

	EventType MoveEvent(std::int16_t x, std::int16_t y)
	{
		shape.x = x;
		shape.y = y;
		EventType e = { EventType::MOVE };
		e.move = { x, y };
		return e;
	}

	EventType ResizeEvent(std::int16_t width, std::int16_t height)
	{
		shape.width = width;
		shape.height = height;
		EventType e = { EventType::RESIZE };
		e.resize = { static_cast<std::uint16_t>(width), static_cast<std::uint16_t>(height) };
		return e;
	}

	EventType FocusEvent(bool has_focus)
	{
		this->has_focus = has_focus;
		EventType e = { EventType::FOCUS };
		e.focus.has_focus = has_focus;
		return e;
	}

	EventType CloseEvent()
	{
		running = false;
		return { EventType::CLOSE };
	}

	template<bool Wait = false>
	EventType GetEvent()
	{
		if (!eventFIFO.isEmpty()) { return *eventFIFO.pop(); }

		MSG msg = {};
		if constexpr (Wait) running = (GetMessage(&msg, NULL, 16, 0) > 0);             // Blocking mode
		else                running = (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0);  // Non-blocking mode

		if (running)
		{
			TranslateMessage(&msg);
			std::int16_t x = GET_X_LPARAM(msg.lParam);
			std::int16_t y = GET_Y_LPARAM(msg.lParam);

			if (msg.message == WM_KEYDOWN || msg.message == WM_KEYUP)
			{
				if (msg.wParam == VK_CONTROL) msg.wParam = (msg.lParam & (1 << 24)) ? VK_RCONTROL : VK_LCONTROL;

				if (msg.wParam == VK_SHIFT)
				{
					if (!!(GetKeyState(VK_LSHIFT) & 128) != KeyState(KEY_LeftShift)) PostMessage(hWnd, msg.message, VK_LSHIFT, 0);
					if (!!(GetKeyState(VK_RSHIFT) & 128) != KeyState(KEY_RightShift)) PostMessage(hWnd, msg.message, VK_RSHIFT, 0);
					return { EventType::NONE };
				}
			}

			else if (msg.message == WM_SYSKEYDOWN || msg.message == WM_SYSKEYUP)
			{
				if (msg.wParam == VK_MENU) msg.wParam = (msg.lParam & (1 << 24)) ? VK_RMENU : VK_LMENU;
			}
			

			static char buf[4] = {};
			uint8_t bestBtn = BtnState(1) ? 1 : BtnState(2) ? 2 : BtnState(3) ? 3 : 0;
			switch (msg.message)
			{	
				case WM_MOUSEMOVE: return MouseEvent(eMOVE, x, y, bestBtn);
				case WM_LBUTTONDOWN: return MouseEvent(eDOWN, x, y, 1);
				case WM_MBUTTONDOWN: return MouseEvent(eDOWN, x, y, 2);
				case WM_RBUTTONDOWN: return MouseEvent(eDOWN, x, y, 3);
				case WM_LBUTTONUP: return MouseEvent(eUP, x, y, 1);
				case WM_MBUTTONUP: return MouseEvent(eUP, x, y, 2);
				case WM_RBUTTONUP: return MouseEvent(eUP, x, y, 3);

				case WM_MOUSEWHEEL:
				{
					uint8_t wheel = (GET_WHEEL_DELTA_WPARAM(msg.wParam) > 0) ? 4 : 5;
					POINT point = { x, y };
					ScreenToClient(msg.hwnd, &point);
					return { EventType::MOUSE, {eDOWN, (std::int16_t)point.x, (std::int16_t)point.y, wheel} };
				}

				case WM_KEYDOWN: return KeyEvent(eDOWN, WIN32_TO_HID[msg.wParam]);

				case WM_KEYUP: return KeyEvent(eUP, WIN32_TO_HID[msg.wParam]);

				case WM_SYSKEYDOWN:
				{
					MSG discard; GetMessage(&discard, NULL, 0, 0);
					return KeyEvent(eDOWN, WIN32_TO_HID[msg.wParam]);
				}

				case WM_SYSKEYUP: return KeyEvent(eUP, WIN32_TO_HID[msg.wParam]);

				case WM_CHAR: { strncpy_s(buf, (const char*)&msg.wParam, 4);  return TextEvent(buf); }

				case WM_ACTIVE: { return FocusEvent(msg.wParam != WA_INACTIVE); }

				case WM_RESHAPE:
				{
					if (!has_focus)
					{
						PostMessage(hWnd, WM_RESHAPE, msg.wParam, msg.lParam);
						return FocusEvent(true);
					}

					RECT r;

					GetClientRect(hWnd, &r);
					auto w = static_cast<std::int16_t>(r.right - r.left);
					auto h = static_cast<std::int16_t>(r.bottom - r.top);
					if (w != shape.width || h != shape.height) return ResizeEvent(w, h);


					GetWindowRect(hWnd, &r);
					auto x = static_cast<std::int16_t>(r.left);
					auto y = static_cast<std::int16_t>(r.top);
					if (x != shape.x || y != shape.y) return MoveEvent(x, y);
				}

				case WM_CLOSE: { return CloseEvent(); }
			}

			DispatchMessage(&msg);
		}

		return { EventType::NONE };
	}

	void Close() { eventFIFO.push(CloseEvent()); }
	bool KeyState(eKeycode key) { return keys[key]; }
	bool BtnState(std::uint8_t btn) { return (btn < 3) ? mouse[btn] : 0; }
	void MousePos(std::int16_t& x, std::int16_t& y) { x = mousepos.x; y = mousepos.y; }



public:
	void OnMouseEvent(eAction action, std::int16_t x, std::int16_t y, std::uint8_t btn) {}
	void OnKeyEvent(eAction action, eKeycode keycode) {}
	void OnTextEvent(const char* str) {}
	void OnMoveEvent(std::int16_t x, std::int16_t y) { }
	void OnResizeEvent(std::int16_t width, std::int16_t height) { }
	void OnFocusEvent(bool hasFocus) {}
	void OnTouchEvent(eAction action, float x, float y, std::uint8_t id) {}
	void OnCloseEvent() {}

	template<bool Wait>
	bool ProcessEvents()
	{
		EventType e = GetEvent<Wait>();
		while (e.tag != EventType::NONE)
		{
			switch (e.tag)
			{
				case EventType::MOUSE: OnMouseEvent(e.mouse.action, e.mouse.x, e.mouse.y, e.mouse.btn);  break;
				case EventType::KEY: OnKeyEvent(e.key.action, e.key.keycode);                        break;
				case EventType::TEXT: OnTextEvent(e.text.str);                                         break;
				case EventType::MOVE: OnMoveEvent(e.move.x, e.move.y);                                 break;
				case EventType::RESIZE: OnResizeEvent(e.resize.width, e.resize.height);                    break;
				case EventType::FOCUS: OnFocusEvent(e.focus.has_focus);                                  break;
				case EventType::CLOSE: OnCloseEvent(); return false;
				default: break;
			}

			e = GetEvent<Wait>();
		}

		return running;
	}

	Window32(const wchar_t* title, unsigned int width, unsigned int height)
	{
		hInstance = GetModuleHandle(NULL);

		auto im = static_cast<HICON>(::LoadImage(NULL, L"C:/Users/Connor/Desktop/Vulkan Root/Vulkan Renderer/resources/icon.ico", IMAGE_ICON, 256, 256, LR_LOADFROMFILE));;

		// Initialize the window class structure:
		WNDCLASSEX win_class;
		win_class.cbSize = sizeof(WNDCLASSEX);
		win_class.style = CS_HREDRAW | CS_VREDRAW;
		win_class.lpfnWndProc = WndProc;
		win_class.cbClsExtra = 0;
		win_class.cbWndExtra = 0;
		win_class.hInstance = hInstance;
		win_class.hIcon = im;
		win_class.hCursor = LoadCursor(NULL, IDC_ARROW);
		win_class.hbrBackground = (HBRUSH)(NULL_BRUSH);
		win_class.lpszMenuName = NULL;
		win_class.lpszClassName = title;
		win_class.hInstance = hInstance;
		win_class.hIconSm = im;
		// Register window class:
		ATOM atom = RegisterClassEx(&win_class);

		assert(atom && "Failed to register the window class.");

		// Create window with the registered class:
		RECT wr = { 0, 0, (LONG)width, (LONG)height };
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
		hWnd = CreateWindowEx(0,
			title,                                          // class name
			title,                                          // app name
			WS_VISIBLE | WS_OVERLAPPEDWINDOW,  // window style
			100, 100,                                       // x/y coords
			wr.right - wr.left,                             // width
			wr.bottom - wr.top,                             // height
			NULL,                                           // handle to parent
			NULL,                                           // handle to menu
			hInstance,                                      // hInstance
			NULL);                                          // no extra parameters
		assert(hWnd && "Failed to create a window.");

		auto r = ResizeEvent(width, height);
		running = true;
		eventFIFO.push(r);
	}

	~Window32()
	{
		DestroyWindow(hWnd);
	}

	bool CanPresent(VkPhysicalDevice gpu, std::uint32_t queue_family)
	{
		return vkGetPhysicalDeviceWin32PresentationSupportKHR(gpu, queue_family) == VK_TRUE;
	}

#pragma region Setters
	void SetTitle(const wchar_t* title)
	{
		SetWindowText(hWnd, title);
	}

	void SetPos(unsigned int x, unsigned int y)
	{
		SetWindowPos(hWnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
		if (x != shape.x || y != shape.y) eventFIFO.push(MoveEvent(x, y));  // Trigger window moved event
	}

	void SetSize(unsigned int w, unsigned int h)
	{
		RECT wr = { 0, 0, (LONG)w, (LONG)h };
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);  // Add border size to create desired client area size
		int total_width = wr.right - wr.left;
		int total_height = wr.bottom - wr.top;
		SetWindowPos(hWnd, NULL, 0, 0, total_width, total_height, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE);
		if ((w != shape.width) | (h != shape.height)) eventFIFO.push(ResizeEvent(w, h));  // Trigger resize event
	}

	void CreateSurface(VkInstance instance)
	{
		if (surface) return;
		this->instance = instance;
		VkWin32SurfaceCreateInfoKHR win32_createInfo;
		win32_createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		win32_createInfo.pNext = NULL;
		win32_createInfo.flags = 0;
		win32_createInfo.hinstance = hInstance;
		win32_createInfo.hwnd = hWnd;

		if (vkCreateWin32SurfaceKHR(instance, &win32_createInfo, NULL, &surface) != VK_SUCCESS)
			exit(78);
	}
#pragma endregion
};