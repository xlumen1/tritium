#include <iostream>
#include "tritium/Engine.hpp"

using namespace tritium;

Engine::Engine() {
    std::cout << "[Tritium] Engine created.\n";
}

bool Engine::initialize() {
    std::cout << "[Tritium] Engine initialized.\n";
    return true;
}

void Engine::shutdown() {
    std::cout << "[Tritium] Engine shutdown.\n";
}
