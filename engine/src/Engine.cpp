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

void Engine::createLayer(Layer* layer, int priority) {
    layers.push_back(EngineLayerData {
        layer,
        priority
    });
}

void Engine::killLayer(Uid uid) {
    for (auto it = layers.begin(); it != layers.end(); it++) {
        if (it->layer->uid == uid) {
            layers.erase(it);
            break;
        }
    }
}

std::vector<EngineLayerData> Engine::getLayers() {
    return layers;
}

Window& Engine::getWindow() { return window; }

void Engine::mainLoop() {
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            for (auto it = layers.begin(); it != layers.end(); it++) {
                it->layer->event(event);
            }
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColorFloat(window.getSDLRenderer(), 0.0, 0.0, 0.0, 1.0);
        SDL_RenderClear(window.getSDLRenderer());

        for (auto it = layers.begin(); it != layers.end(); it++) {
            it->layer->process();
        }

        SDL_RenderPresent(window.getSDLRenderer());

        SDL_Delay(16); // TODO: Adaptive Framerate
    }
}
