#include "tritium/Engine.hpp"
#include "tritium/layer/EngineGuiLayer.hpp"
#include "tritium/layer/EmptyLayer.hpp"
#include "tritium/layer/EngineToolLayer.hpp"
#include "tritium/layer/Layer.hpp"
#include <iostream>

int main() {
    tritium::Engine engine;
    if (!engine.initialize()) {
        std::cerr << "Editor failed to init engine!\n";
        return -1;
    }

    std::cout << "[Editor] Welcome to Tritium Editor (stub)\n";

    engine.createLayer(std::make_shared<tritium::EngineGuiLayer>(engine), 16); // postware
    engine.createLayer(std::make_shared<tritium::EmptyLayer>(engine), -1); // preware
    engine.createLayer(std::make_shared<tritium::EngineToolLayer>(engine), 17);

    try {
        engine.mainLoop();
    } catch (const std::exception& e) {
        SDL_Log("Fatal error: %s", e.what());
        engine.shutdown();
        return -1;
    }
    return 0;
}
