#pragma once
#include "api.hpp"
#include "Window.hpp"

namespace tritium {
class TRITIUM_API Engine {
public:
    Engine(int width = 1280, int height = 720);
    bool initialize();
    void shutdown();

    Window& GetWindow();
    void MainLoop();
private:
    Window window;
};
} // namespace tritium
