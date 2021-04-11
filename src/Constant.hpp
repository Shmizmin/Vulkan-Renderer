#pragma once

#ifdef DEBUG
constexpr bool enableValidationLayers = true;
#else
constexpr bool enableValidationLayers = false;
#endif

constexpr auto MAX_FRAMES_IN_FLIGHT = 2ull;

constexpr auto WIDTH = 800u;
constexpr auto HEIGHT = 600u;

constexpr auto NAME = "Vulkan Renderer";