#ifndef TIDE_COMP
#define TIDE_COMP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>
#include <iostream>
#include <layer.hpp>
#include <device.hpp>
#include <constants.hpp>

#define WIDTH 800
#define HEIGHT 600

namespace tide
{
    class App
    {
    public:
        bool framebufferResized = false;

        App(std::vector<const char*> extensions, bool debug = true)
        {
            _extensions = extensions;

            vk::ApplicationInfo applicationInfo("Comp", 1, "Tide", 1, VK_API_VERSION_1_1);
            vk::InstanceCreateInfo instanceCreateInfo{};
            instanceCreateInfo.pApplicationInfo = &applicationInfo;
            if(debug)
            {
                _extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
                instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
                vk::DebugUtilsMessengerCreateInfoEXT debugCreateInfo = ValidationLayer::populateDebugMessengerCreateInfo();
                instanceCreateInfo.pNext = &debugCreateInfo;
            }
            else
            {
                instanceCreateInfo.enabledLayerCount = 0;
                instanceCreateInfo.pNext = nullptr;
            }
            instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(_extensions.size());
            instanceCreateInfo.ppEnabledExtensionNames = _extensions.data();

            _instance = vk::createInstance(instanceCreateInfo);
            _validationLayer = ValidationLayer(_instance);

            VkSurfaceKHR tmpSurface;
            if (glfwCreateWindowSurface(_instance, window, nullptr, &tmpSurface) != VK_SUCCESS) {
                throw std::runtime_error("failed to create window surface!");
            }
            _surface = vk::SurfaceKHR(tmpSurface);
        }
        void clean()
        {

        }
        ~App()
        {
            vkDestroySurfaceKHR(_instance, _surface, nullptr);
            _validationLayer.~ValidationLayer();
            _instance.destroy();
        }
    private:
        GLFWwindow* window;

        vk::raii::Context _context;
        vk::Instance _instance = nullptr;
        ValidationLayer _validationLayer = nullptr;
        vk::SurfaceKHR _surface;

        std::vector<const char*> _extensions;

        bool _enableValidation;

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
            auto app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
            app->framebufferResized = true;
        }

        void initWindow() {
            glfwInit();

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

            window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
            glfwSetWindowUserPointer(window, this);
            glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
        }
    };
}



#endif // !TIDE_CONTEXT