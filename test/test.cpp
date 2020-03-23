#include <eseed/window/window.hpp>
#include <iostream>

int main() {
    std::shared_ptr<esdw::Window> window = esdw::createWindow(
        { 1366, 768 },
        "ESeed Window"
    );

    esdw::WinSize size = window->getSize();
    std::cout << "Window size: " << size.width << " : " << size.height << std::endl;

    // Loop until X is pressed
    while (!window->isCloseRequested()) {

        // Check for window events 
        // (key presses, mouse move, close button, etc.)
        window->poll();

        // DRAW, UPDATE CODE, ETC...
    }
}