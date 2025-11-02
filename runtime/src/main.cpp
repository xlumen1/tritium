#include "tritium/Engine.hpp"
#include "tritium/layer/RuntimeLayer.hpp"
#include <iostream>

int main() {
    tritium::Engine engine;
    if (!engine.initialize()) {
        std::cerr << "Failed to init engine!\n";
        return -1;
    }

    std::cout << "[Runtime] Running game loop (stub)...\n";

    engine.createLayer(std::make_shared<tritium::RuntimeLayer>(engine), 0);

    try {
        engine.mainLoop();
    } catch (const std::exception& e) {
        SDL_Log("Fatal error: %s", e.what());
        engine.shutdown();
        return -1;
    }

    return 0;
}
