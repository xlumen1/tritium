#include "tritium/layer/EngineGuiLayer.hpp"
#include <iostream>

using namespace tritium;

void EngineGuiLayer::process() {
    return;
}

void EngineGuiLayer::event() {
    std::cout << "[Layer] Layer " << uid.to_string() << " received event" << std::endl;
}
