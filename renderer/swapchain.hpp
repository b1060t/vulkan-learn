#ifndef TIDE_SWAPCHAIN
#define TIDE_SWAPCHAIN

#include <vulkan/vulkan.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>
#include <constants.hpp>

namespace tide
{
    class SwapChain
	{
	public:
		SwapChain(vk::PhysicalDevice physicalDevice)
		{

		}
	private:
		vk::PhysicalDevice _physicalDevice;
		
		void createSwapChain()
		{

		}
	};
}

#endif // !TIDE_SWAPCHAIN