#pragma once

#include "keycode.hpp"

#include <vulkan/vulkan.hpp>
#include <memory>
#include <string>
#include <vector>
#include <functional>

namespace esdw {

struct WinSize {
    unsigned int width, height;
};

struct MousePos {
    int x, y;
};

struct KeyDownEvent {
    KeyCode keyCode;
};

struct KeyUpEvent {
    KeyCode keyCode;
};

struct MouseMoveEvent {
    MousePos pos; // Position in window
    MousePos screenPos; // Position relative to whole monitor
};

class Window {
public:
    // Set event handlers

    virtual void setKeyDownHandler(std::function<void(KeyDownEvent)> handler) = 0;
    virtual void setKeyUpHandler(std::function<void(KeyUpEvent)> handler) = 0;
    virtual void setMouseMoveHandler(std::function<void(MouseMoveEvent)> handler) = 0;

    virtual bool getKey(KeyCode keyCode) = 0;
    virtual MousePos getMouseScreenPos() = 0;
    virtual MousePos getMousePos() = 0;
    virtual void setMouseScreenPos(MousePos screenPos) = 0;
    virtual void setMousePos(MousePos pos) = 0;

    // Poll for window events
    virtual void poll() = 0;

    // Check if the close button has been pressed and close is requested
    virtual bool isCloseRequested() = 0;

    // Get size of the window in pixels
    virtual WinSize getSize() = 0;
    
    // Get a list of platform-specific extension names required for surface
    // rendering in Vulkan
    virtual std::vector<const char*> getRequiredInstanceExtensionNames() = 0;

    // Create a platform-specific Vulkan surface
    virtual vk::SurfaceKHR createSurface(vk::Instance instance) = 0;
};

// Platform-agnostic function to create a window for the native platform
// Definitions in platform-specific source files
std::unique_ptr<Window> createWindow(
    WinSize size,
    std::string title
);

}