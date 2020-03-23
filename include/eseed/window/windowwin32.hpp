#pragma once

#include "window.hpp"

#ifdef NOMINMAX
#include <windows.h>
#else
#define NOMINMAX
#include <windows.h>
#undef NOMINMAX
#endif

#include <string>

namespace esdw {

class WindowWin32 : public Window {
public:
    WindowWin32(WinSize size, std::string title);
    ~WindowWin32();

    void setKeyDownHandler(std::function<void(KeyDownEvent)> handler) override;
    void setKeyUpHandler(std::function<void(KeyUpEvent)> handler) override;
    void setMouseMoveHandler(std::function<void(MouseMoveEvent)> handler) override;

    bool getKey(KeyCode keyCode) override;
    MousePos getMouseScreenPos() override;
    MousePos getMousePos() override;
    void setMouseScreenPos(MousePos screenPos) override;
    void setMousePos(MousePos pos) override;
    
    void poll() override;

    bool isCloseRequested() override;

    WinSize getSize() override;

    std::vector<const char*> getRequiredInstanceExtensionNames() override;
    vk::SurfaceKHR createSurface(vk::Instance instance) override;

private:
    HINSTANCE hInstance;
    WNDCLASS wc;
    HWND hWnd;
    bool closeRequested = false;
    std::function<void(KeyDownEvent)> keyDownHandler;
    std::function<void(KeyUpEvent)> keyUpHandler;
    std::function<void(MouseMoveEvent)> mouseMoveHandler;

    static LRESULT CALLBACK windowProc(
        HWND hWnd, 
        UINT uMsg, 
        WPARAM wParam, 
        LPARAM lParam
    );
};

}