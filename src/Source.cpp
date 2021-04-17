#include <windows.h>
#include <iostream>
#include "./Extern.hpp"
#include "./Renderer.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "./tiny_obj_loader.hpp"


std::size_t frameCount = 0ui64;

#ifdef DEBUG
int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#else
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#endif
{
	VulkanRenderer renderer{};

	try
	{
		renderer.run();
	}

	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}