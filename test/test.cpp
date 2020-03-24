#include <eseed/window/window.hpp>
#include <iostream>

#include <vulkan/vulkan.hpp>

int main() {
    std::shared_ptr<esdw::Window> window = esdw::createWindow(
        { 1366, 768 },
        "ESeed Window with Vulkan"
    );

    // Collect instance extensions required for surface use on current platform
    // Any additional required extensions can be appended to this list, or
    // vice-versa
    std::vector<const char*> extensions = window->getRequiredInstanceExtensionNames();
    std::vector<const char*> layers = { "VK_LAYER_KHRONOS_validation" };

    vk::Instance instance = vk::createInstance(vk::InstanceCreateInfo()
        .setEnabledExtensionCount((uint32_t)extensions.size())
        .setPpEnabledExtensionNames(extensions.data())
        .setEnabledLayerCount((uint32_t)layers.size())
        .setPpEnabledLayerNames(layers.data())
    );

    // Create platform-specific Vulkan surface
    vk::SurfaceKHR surface = window->createSurface(instance);

    // ...

    // Loop until close button is pressed
    while (!window->isCloseRequested()) {

        // Check for window events 
        // (key presses, mouse move, close button, etc.)
        window->poll();

        // DRAW & UPDATE CODE, ETC...
    }
}