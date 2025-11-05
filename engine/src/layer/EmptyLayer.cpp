#include "tritium/layer/EmptyLayer.hpp"
#include "tritium/Engine.hpp"

using namespace tritium;

EmptyLayer::EmptyLayer(Engine& engine) : Layer(engine) {}
EmptyLayer::~EmptyLayer() {}

void EmptyLayer::message(LayerMessage message) {
    if (message.type == MessageType::SLEEP) {
        if (active) {
            std::cout << "[EmptyLayer] Going to sleep." << std::endl;
            active = false;
            LayerMessage reply;
            reply.sender = this->uid;
            reply.type = MessageType::ACKNOWLEDGE;
            reply.header = "SLEEP_ACK";
            t_engine.sendMessageToLayer(message.sender, reply);
        }
    }
    if (message.type == MessageType::WAKE) {
        active = true;
        LayerMessage reply;
        reply.sender = this->uid;
        reply.type = MessageType::ACKNOWLEDGE;
        reply.header = "WAKE_ACK";
        t_engine.sendMessageToLayer(message.sender, reply);
    }
}
