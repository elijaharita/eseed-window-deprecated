cmake_minimum_required(VERSION 3.10)

project(eseed_window)

option(ESDW_ENABLE_TESTING OFF)
option(ESDW_ENABLE_VULKAN_SUPPORT OFF)

if (ESDW_ENABLE_VULKAN_SUPPORT)
    message("Vulkan support is enabled")
    if (NOT TARGET Vulkan::Vulkan)
        message("Vulkan target not found, using FindVulkan")
        find_package(Vulkan REQUIRED)
    endif()
endif()

# Set up library

add_library(eseed_window
    src/window.cpp
)
target_include_directories(eseed_window PUBLIC include/)

# Identify platform-specific resources

if(WIN32)
    message("Compiling for Win32")
    target_sources(eseed_window PRIVATE src/windowwin32.cpp)
    target_compile_definitions(eseed_window PRIVATE ESDW_PLATFORM_WIN32)
    if (ESDW_ENABLE_VULKAN_SUPPORT)
        target_link_libraries(eseed_window PRIVATE Vulkan::Vulkan)
        target_compile_definitions(eseed_window PRIVATE VK_USE_PLATFORM_WIN32_KHR)
    endif()
else()
    message(FATAL_ERROR "This platform is not supported")
endif()

# Testing

if(ESDW_ENABLE_TESTING)
    enable_testing()

    # Basic test
    add_executable(eseed_window_test test/test.cpp)
    target_link_libraries(eseed_window_test eseed_window)
    add_test(eseed_window_test eseed_window_test)

    if(ESDW_ENABLE_VULKAN_SUPPORT)
        add_executable(eseed_window_test_vulkan test/vulkantest.cpp)
        target_link_libraries(eseed_window_test_vulkan Vulkan::Vulkan eseed_window)
        add_test(eseed_window_test_vulkan eseed_window_test_vulkan)
    endif()
endif()