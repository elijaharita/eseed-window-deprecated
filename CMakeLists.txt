cmake_minimum_required(VERSION 3.10)

project(eseed_window)

if (NOT TARGET Vulkan::Vulkan)
    find_package(Vulkan REQUIRED)
endif()

# Set up library

add_library(eseed_window)
target_include_directories(eseed_window PUBLIC include/)
target_link_libraries(eseed_window PRIVATE Vulkan::Vulkan)

# Identify platform-specific resources

if(WIN32)
    message("Compiling for Win32")
    target_sources(eseed_window PRIVATE src/windowwin32.cpp)
    target_compile_definitions(eseed_window PRIVATE 
        ESDW_PLATFORM_WIN32 
        VK_USE_PLATFORM_WIN32_KHR
    )
else()
    message(FATAL_ERROR "This platform is not supported")
endif()

# Testing

if(ESDW_ENABLE_TESTING)
    enable_testing()

    add_executable(eseed_window_test test/test.cpp)
    target_link_libraries(eseed_window_test Vulkan::Vulkan eseed_window)
    add_test(eseed_window_test eseed_window_test)
endif()