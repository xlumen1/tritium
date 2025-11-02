#include <iostream>
#include "tritium/Engine.hpp"

using namespace tritium;

Engine::Engine(int width, int height) : window("Tritium Engine", width, height) {
    std::cout << "[Tritium] Engine created\n";
}

bool Engine::initialize() {
    std::cout << "[Tritium] Engine initialized\n";
    return true;
}

void Engine::shutdown() {
    layers.clear();
    std::cout << "[Tritium] Engine shutdown\n";
    running = false;
}

Uid Engine::createLayer(std::shared_ptr<Layer> layer, int priority) {
    layers.push_back(EngineLayerData {
        layer,
        priority
    });
    return layer.get()->uid;
}

void Engine::killLayer(Uid uid) {
    std::cout << "[Engine] Killing layer " << uid.to_string() << std::endl;
    layers.erase(std::remove_if(layers.begin(), layers.end(),
        [&](const EngineLayerData& data) {
            return data.layer->uid == uid;
        }), layers.end());
}

std::vector<EngineLayerData> Engine::getLayers() {
    return layers;
}

Window& Engine::getWindow() { return window; }

void Engine::mainLoop() {
    running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            for (auto it = layers.begin(); it != layers.end(); it++) {
                it->layer->event(event);
            }
            if (event.type == SDL_EVENT_QUIT) {
                shutdown();
                return;
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
