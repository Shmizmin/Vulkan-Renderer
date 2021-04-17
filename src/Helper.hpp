#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include <vulkan/vulkan.h>

struct QueueFamilyIndices
{
	std::optional<std::uint32_t> graphicsFamily;
	std::optional<std::uint32_t> presentFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct UniformBufferObject
{
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
};