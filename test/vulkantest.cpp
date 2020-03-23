#define ESDW_ENABLE_VULKAN_SUPPORT

#include <eseed/window/window.hpp>
#include <iostream>

#include <vulkan/vulkan.hpp>

int main() {
    std::shared_ptr<esdw::Window> window = esdw::createWindow(
        { 1366, 768 },
        "ESeed Window with Vulkan"
    );

    std::vector<const char*> extensions = window->getRequiredInstanceExtensionNames();
    std::vector<const char*> layers = {
        "VK_LAYER_KHRONOS_validation"
    };

    vk::Instance instance = vk::createInstance(vk::InstanceCreateInfo()
        .setExtensionCount((uint32_t)extensions.size())
        .setPExtensions(extensions.data())
        .setLayerCount((uint32_t)layers.size())
        .setPLayerNames(layers.data())
    );

    vk::SurfaceKHR surface = window->createSurface(instance);

    // Loop until X is pressed
    while (!window->isCloseRequested()) {

        // Check for window events 
        // (key presses, mouse move, close button, etc.)
        window->poll();

        // DRAW, UPDATE CODE, ETC...
    }
}