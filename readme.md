# eseed window

## Goal
This library is a bare minimum cross-platform window utility for rendering. Currently only Vulkan is supported, although OpenGL support and others may be added in the future.

## Usage

Link `eseed_window` in CMake:

```
add_subdirectory("path/to/eseed_window")
target_link_libraries(target eseed_window)
```

## Current platform support

- Win32

## Possible future platforms

- Linux
- Mac

## Quick introduction

```cpp
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
```

## Full feature list

### General
- Check for window close button press
- Get window size
  - *Set (planned)*
- Platform-agnostic window creation
- Poll for events

### Mouse and keyboard
- Handlers
  - Key down
  - Key up
  - Mouse move
  - *Mouse button down and up (planned)*
- Get key status
- Get and set mouse position
  - Screen space and window space

### Vulkan
- Get required instance extensions for platform
- Create platform-specific Vulkan surface