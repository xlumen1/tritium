#include "tritium/layer/EngineToolLayer.hpp"
#include "tritium/Engine.hpp"
#include <any>

using namespace tritium;

EngineToolLayer::EngineToolLayer(Engine& engine) : Layer(engine) {}
EngineToolLayer::~EngineToolLayer() {}

void EngineToolLayer::process() {
    if (!has_init) {
        Uid gui = t_engine.getLayerByName("EngineGuiLayer");
        if (gui.is_valid()) {
            // Test UI
            LayerMessage message;
            message.type = MessageType::SEND_DATA;
            message.header = "REGISTER_RENDER_MODULE";
            message.payload = [&]() {
                ImGui::Begin("Test Layer");
                ImGui::Text("Hello from EngineToolLayer!");
                ImGui::End();
            };
        } else {
            std::cout << "[EngineToolLayer] Couldn't find EngineGuiLayer";
            t_engine.killLayer(uid);
        }
        has_init = true;
    }
}

void EngineToolLayer::message(LayerMessage message) {
    if (message.type == MessageType::SLEEP) {
        if (active) {
            std::cout << "[EngineToolLayer] Going to sleep." << std::endl;
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

void EngineToolLayer::event(SDL_Event event) {}
