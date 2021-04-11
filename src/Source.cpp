#include <iostream>
#include <stdexcept>

import VulkanManager;

#ifndef NDEBUG
int main(void) noexcept
#else
int WinMain(void) noexcept
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