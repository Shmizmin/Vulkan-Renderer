#include <iostream>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"

import Manager;

#ifdef DEBUG
int main(void)
#else
int WinMain(void)
#endif
{
	VulkanRenderer app;

	try
	{
		app.run();
	}

	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}