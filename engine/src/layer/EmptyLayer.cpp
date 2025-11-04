#pragma once
#include "tritium/layer/EmptyLayer.hpp"

using namespace tritium;

EmptyLayer::EmptyLayer(Engine& engine) : Layer(engine) {}
EmptyLayer::~EmptyLayer() {}

void EmptyLayer::message(LayerMessage message) {
    if (message.type == MessageType::SLEEP) {
        if (active) {
            std::cout << "[EmptyLayer] Going to sleep." << std::endl;
            active = false;
        }
    }
    if (message.type == MessageType::WAKE) {
        active = true;
    }
}
