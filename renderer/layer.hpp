#ifndef TIDE_LAYER
#define TIDE_LAYER

#include <vulkan/vulkan.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>
#include <iostream>
#include <constants.hpp>

namespace tide
{
    class ValidationLayer
    {
    public:
        ValidationLayer(vk::Instance instance)
        {
            pfnVkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(instance.getProcAddr("vkCreateDebugUtilsMessengerEXT"));
            if (!pfnVkCreateDebugUtilsMessengerEXT)
            {
              std::cout << "GetInstanceProcAddr: Unable to find pfnVkCreateDebugUtilsMessengerEXT function." << std::endl;
              exit(1);
            }

            pfnVkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT"));
            if (!pfnVkDestroyDebugUtilsMessengerEXT)
            {
              std::cout << "GetInstanceProcAddr: Unable to find pfnVkDestroyDebugUtilsMessengerEXT function." << std::endl;
              exit(1);
            }

            vk::DebugUtilsMessengerCreateInfoEXT createInfo = populateDebugMessengerCreateInfo();
            _messenger = instance.createDebugUtilsMessengerEXT(createInfo);
            _instance = instance;
        }
        ~ValidationLayer()
        {
            _instance.destroyDebugUtilsMessengerEXT(_messenger);
        }

        static vk::DebugUtilsMessengerCreateInfoEXT populateDebugMessengerCreateInfo(PFN_vkDebugUtilsMessengerCallbackEXT debugCallback = defaultCallback)
        {
            vk::DebugUtilsMessengerCreateInfoEXT createInfo{};
            createInfo.sType = vk::StructureType::eDebugUtilsMessengerCreateInfoEXT;
            createInfo.messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
            createInfo.messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;
            createInfo.pfnUserCallback = debugCallback;
            return createInfo;
        }

    private:
        vk::DebugUtilsMessengerEXT _messenger;
        vk::Instance _instance;

        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
            auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
            if (func != nullptr) {
                return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
            } else {
                return VK_ERROR_EXTENSION_NOT_PRESENT;
            }
        }

        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
            if (func != nullptr) {
                func(instance, debugMessenger, pAllocator);
            }
        }

        static VKAPI_ATTR VkBool32 VKAPI_CALL defaultCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
        {
            if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
            {
                std::cerr << "Log: " << pCallbackData->pMessage << std::endl;
            }
            return VK_FALSE;
        }
    };
}

#endif // !TIDE_LAYER