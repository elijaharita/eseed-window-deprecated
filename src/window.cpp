#include <eseed/window/window.hpp>

#include <stdexcept>

#ifdef ESDW_PLATFORM_WIN32
#include <eseed/window/windowwin32.hpp>
#endif

using namespace esdw;

std::unique_ptr<Window> esdw::createWindow(
    WinSize size, 
    std::string title
) {
#ifdef ESDW_PLATFORM_WIN32
#ifdef ESDW_ENABLE_VULKAN_SUPPORT
    return std::make_unique<WindowWin32Vulkan>(size, title);
#else
    return std::make_unique<WindowWin32>(size, title);
#endif
#endif
}