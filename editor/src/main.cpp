#include "tritium/Engine.hpp"
#include "tritium/layer/EngineGuiLayer.hpp"
#include <iostream>

int main() {
    tritium::Engine engine;
    if (!engine.initialize()) {
        std::cerr << "Editor failed to init engine!\n";
        return -1;
    }

    std::cout << "[Editor] Welcome to Tritium Editor (stub)\n";

    engine.createLayer(reinterpret_cast<tritium::Layer*>(new tritium::EngineGuiLayer(engine)), 16);

    try {
        engine.mainLoop();
    } catch (const std::exception& e) {
        SDL_Log("Fatal error: %s", e.what());
        return -1;
    }

    engine.shutdown();
    return 0;
}
