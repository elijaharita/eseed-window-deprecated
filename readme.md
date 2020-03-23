# eseed window

## Goal
This library is a bare minimum cross-platform window utility for rendering.

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

int main() {
    std::shared_ptr<esdw::Window> window = esdw::createWindow(
        { 1366, 768 },
        "Title"
    );

    while (!window->isCloseRequested()) {
        // loop until X is pressed
    }
}
```