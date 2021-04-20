#pragma once

#include <array>
#include <cstdint>

const unsigned char WIN32_TO_HID[256] =
{
	  0,  0,  0,  0,  0,  0,  0,  0, 42, 43,  0,  0,  0, 40,  0,  0,    // 16
	225,224,226, 72, 57,  0,  0,  0,  0,  0,  0, 41,  0,  0,  0,  0,    // 32
	 44, 75, 78, 77, 74, 80, 82, 79, 81,  0,  0,  0, 70, 73, 76,  0,    // 48
	 39, 30, 31, 32, 33, 34, 35, 36, 37, 38,  0,  0,  0,  0,  0,  0,    // 64
	  0,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18,    // 80
	 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,  0,  0,  0,  0,  0,    // 96
	 98, 89, 90, 91, 92, 93, 94, 95, 96, 97, 85, 87,  0, 86, 99, 84,    //112
	 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69,104,105,106,107,    //128
	108,109,110,111,112,113,114,115,  0,  0,  0,  0,  0,  0,  0,  0,    //144
	 83, 71,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    //160
	225,229,224,228,226,230,  0,  0,  0,  0,  0,  0,  0,127,128,129,    //176    L/R shift/ctrl/alt  mute/vol+/vol-
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 51, 46, 54, 45, 55, 56,    //192
	 53,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    //208
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 47, 49, 48, 52,  0,    //224
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    //240
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0     //256
};

enum Action
{ 
	UP,
	DOWN,
	MOVE
};

enum Key
{
	KEY_NONE = 0, // Undefined. (No event)
	KEY_A = 4,
	KEY_B = 5,
	KEY_C = 6,
	KEY_D = 7,
	KEY_E = 8,
	KEY_F = 9,
	KEY_G = 10,
	KEY_H = 11,
	KEY_I = 12,
	KEY_J = 13,
	KEY_K = 14,
	KEY_L = 15,
	KEY_M = 16,
	KEY_N = 17,
	KEY_O = 18,
	KEY_P = 19,
	KEY_Q = 20,
	KEY_R = 21,
	KEY_S = 22,
	KEY_T = 23,
	KEY_U = 24,
	KEY_V = 25,
	KEY_W = 26,
	KEY_X = 27,
	KEY_Y = 28,
	KEY_Z = 29,
	KEY_1 = 30, // 1 and !
	KEY_2 = 31, // 2 and @
	KEY_3 = 32, // 3 and #
	KEY_4 = 33, // 4 and $
	KEY_5 = 34, // 5 and %
	KEY_6 = 35, // 6 and ^
	KEY_7 = 36, // 7 and &
	KEY_8 = 37, // 8 and *
	KEY_9 = 38, // 9 and (
	KEY_0 = 39, // 0 and )
	KEY_Enter = 40, // (Return)
	KEY_Escape = 41,
	KEY_Delete = 42,
	KEY_Tab = 43,
	KEY_Space = 44,
	KEY_Minus = 45, // - and (underscore)
	KEY_Equals = 46, // = and +
	KEY_LeftBracket = 47, // [ and {
	KEY_RightBracket = 48, // ] and }
	KEY_Backslash = 49, // \ and |
	// KEY_NonUSHash     = 50, // # and ~
	KEY_Semicolon = 51, // ; and :
	KEY_Quote = 52, // ' and "
	KEY_Grave = 53,
	KEY_Comma = 54, // , and <
	KEY_Period = 55, // . and >
	KEY_Slash = 56, // / and ?
	KEY_CapsLock = 57,
	KEY_F1 = 58,
	KEY_F2 = 59,
	KEY_F3 = 60,
	KEY_F4 = 61,
	KEY_F5 = 62,
	KEY_F6 = 63,
	KEY_F7 = 64,
	KEY_F8 = 65,
	KEY_F9 = 66,
	KEY_F10 = 67,
	KEY_F11 = 68,
	KEY_F12 = 69,
	KEY_PrintScreen = 70,
	KEY_ScrollLock = 71,
	KEY_Pause = 72,
	KEY_Insert = 73,
	KEY_Home = 74,
	KEY_PageUp = 75,
	KEY_DeleteForward = 76,
	KEY_End = 77,
	KEY_PageDown = 78,
	KEY_Right = 79, // Right arrow
	KEY_Left = 80, // Left arrow
	KEY_Down = 81, // Down arrow
	KEY_Up = 82, // Up arrow
	KP_NumLock = 83,
	KP_Divide = 84,
	KP_Multiply = 85,
	KP_Subtract = 86,
	KP_Add = 87,
	KP_Enter = 88,
	KP_1 = 89,
	KP_2 = 90,
	KP_3 = 91,
	KP_4 = 92,
	KP_5 = 93,
	KP_6 = 94,
	KP_7 = 95,
	KP_8 = 96,
	KP_9 = 97,
	KP_0 = 98,
	KP_Point = 99, // . and Del
	KP_Equals = 103,
	KEY_F13 = 104,
	KEY_F14 = 105,
	KEY_F15 = 106,
	KEY_F16 = 107,
	KEY_F17 = 108,
	KEY_F18 = 109,
	KEY_F19 = 110,
	KEY_F20 = 111,
	KEY_F21 = 112,
	KEY_F22 = 113,
	KEY_F23 = 114,
	KEY_F24 = 115,
	// KEY_Help          = 117,
	KEY_Menu = 118,
	KEY_Mute = 127,
	KEY_VolumeUp = 128,
	KEY_VolumeDown = 129,
	KEY_LeftControl = 224, // WARNING : Android has no Ctrl keys.
	KEY_LeftShift = 225,
	KEY_LeftAlt = 226,
	KEY_LeftGUI = 227,
	KEY_RightControl = 228,
	KEY_RightShift = 229, // WARNING : Win32 fails to send a WM_KEYUP message if both shift keys are pressed, and one released.
	KEY_RightAlt = 230,
	KEY_RightGUI = 231
};

struct EventType
{
	enum { NONE, MOUSE, KEY, TEXT, MOVE, RESIZE, FOCUS, TOUCH, CLOSE, UNKNOWN } tag; // event type
	union
	{
		struct { Action action; std::int16_t x; std::int16_t y; std::uint8_t btn; } mouse;     // mouse move/click
		struct { Action action; Key keycode; } key;       // Keyboard key state
		struct { const char* str; } text;      // Text entered
		struct { std::int16_t x; std::int16_t y; } move;      // Window move
		struct { std::uint16_t width; std::uint16_t height; } resize;    // Window resize
		struct { bool has_focus; } focus;     // Window gained/lost focus
		struct { Action action; float x; float y; std::uint8_t id; } touch;     // multi-touch display
		struct {                                                  } close;     // Window is closing
	};
};

template<std::size_t ARR_SIZE>
class EventFIFO
{
	int head, tail;
	std::array<EventType, ARR_SIZE> buf = {};

public:
	EventFIFO() : head(0), tail(0) {}
	bool isEmpty() { return head == tail; }
	void push(EventType const& item) { ++head; buf[head %= ARR_SIZE] = item; }
	EventType* pop() { if (head == tail) return 0; ++tail; return &buf[tail %= ARR_SIZE]; }
};