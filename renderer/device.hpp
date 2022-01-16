#ifndef TIDE_DEVICE
#define TIDE_DEVICE

#include <vulkan/vulkan.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>
#include <constants.hpp>
#include <optional>
#include <set>

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
        vk::Queue graphicsQueue;
        vk::Queue computeQueue;
        vk::Queue presentQueue;
        Device(vk::Instance instance, bool enableValidationLayers)
            :_enableValidationLayers(enableValidationLayers)
        {
            _instance = instance;
        }
        ~Device()
        {
            _device.destroy();
        }
    private:
        vk::PhysicalDevice _physicalDevice;
        vk::Device _device;
        vk::Instance _instance;
        vk::SurfaceKHR _surface;
        bool _enableValidationLayers;

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

        void createLogicDevice()
        {
            QueueFamilyIndices indices = findQueueFamilies();
            std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
            std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.computeFamily.value(), indices.presentFamily.value()};
            float queuePriority = 1.0f;
            for (uint32_t queueFamily : uniqueQueueFamilies) {
                vk::DeviceQueueCreateInfo queueCreateInfo{};
                queueCreateInfo.sType = vk::StructureType::eDeviceQueueCreateInfo;
                queueCreateInfo.queueFamilyIndex = queueFamily;
                queueCreateInfo.queueCount = 1;
                queueCreateInfo.pQueuePriorities = &queuePriority;
                queueCreateInfos.push_back(queueCreateInfo);
            }
            vk::PhysicalDeviceFeatures deviceFeatures{};
            deviceFeatures.samplerAnisotropy = VK_TRUE;
            vk::DeviceCreateInfo createInfo{};
            createInfo.sType = vk::StructureType::eDeviceCreateInfo;
            createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
            createInfo.pQueueCreateInfos = queueCreateInfos.data();
            createInfo.pEnabledFeatures = &deviceFeatures;
            createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
            createInfo.ppEnabledExtensionNames = deviceExtensions.data();
            if (_enableValidationLayers) {
                createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                createInfo.ppEnabledLayerNames = validationLayers.data();
            } else {
                createInfo.enabledLayerCount = 0;
            }
            _device = _physicalDevice.createDevice(createInfo);
            graphicsQueue = _device.getQueue(indices.graphicsFamily.value(), 0);
            computeQueue = _device.getQueue(indices.computeFamily.value(), 0);
            presentQueue = _device.getQueue(indices.presentFamily.value(), 0);
        }
    };
}

#endif // !TIDE_DEVICE