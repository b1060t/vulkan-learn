#ifndef TIDE_DEVICE
#define TIDE_DEVICE

#include <vulkan/vulkan.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>
#include <constants.hpp>
#include <optional>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    std::optional<uint32_t> computeFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value() && computeFamily.has_value();
    }
};

namespace tide
{
    class Device
    {
    public:
        Device(vk::Instance instance)
        {
            _instance = instance;
        }
        ~Device()
        {

        }
    private:
        vk::PhysicalDevice _physicalDevice;
        vk::Device _device;
        vk::Instance _instance;
        vk::SurfaceKHR _surface;

        bool isDeviceSuitable(vk::PhysicalDevice device)
        {
            return true;
        }

        void pickPhysicalDevice()
        {
            std::vector<vk::PhysicalDevice> devices = _instance.enumeratePhysicalDevices();

            for (const auto& device : devices)
            {
                if (isDeviceSuitable(device))
                {
                    _physicalDevice = device;
                    break;
                }
            }

            if (!_physicalDevice) {
                throw std::runtime_error("failed to find a suitable GPU!");
            }
        }

        QueueFamilyIndices findQueueFamilies() {
            QueueFamilyIndices indices;
            std::vector<vk::QueueFamilyProperties> queueFamilyProperties = _physicalDevice.getQueueFamilyProperties();
            int i = 0;
            for (const auto& queueFamily : queueFamilyProperties) {
                if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
                    indices.graphicsFamily = i;
                }
                if (queueFamily.queueFlags & vk::QueueFlagBits::eCompute) {
                    indices.computeFamily = i;
                }
                VkBool32 presentSupport = false;
                vkGetPhysicalDeviceSurfaceSupportKHR(_physicalDevice, i, _surface, &presentSupport);
                if (presentSupport) {
                    indices.presentFamily = i;
                }
                if (indices.isComplete()) {
                    break;
                }
                i++;
            }
            return indices;
        }
    };
}

#endif // !TIDE_DEVICE