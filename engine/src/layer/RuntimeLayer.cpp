#include "tritium/layer/RuntimeLayer.hpp"
#include "tritium/Engine.hpp"
#include <iostream>

using namespace tritium;

RuntimeLayer::RuntimeLayer(Engine& engine) : Layer(engine) {}

void RuntimeLayer::process() {
    t_engine.shutdown();
}

void RuntimeLayer::event(SDL_Event event) {}
