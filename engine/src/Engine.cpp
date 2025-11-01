#include <iostream>
#include "tritium/Engine.hpp"

using namespace tritium;

Engine::Engine(int width, int height) : window("Tritium Engine", width, height) {
    std::cout << "[Tritium] Engine created.\n";
}

bool Engine::initialize() {
    std::cout << "[Tritium] Engine initialized.\n";
    return true;
}

void Engine::shutdown() {
    std::cout << "[Tritium] Engine shutdown.\n";
}

Window& Engine::GetWindow() { return window; }

void Engine::MainLoop() {
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // TODO: Frame Rendering
        SDL_Delay(16); // TODO: Adaptive Framerate
    }
}
