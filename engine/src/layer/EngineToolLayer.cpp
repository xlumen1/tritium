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
            std::cout << "[EngineToolLayer] Sending demo window to " << gui.to_string() << std::endl;
            LayerMessage demoWindow;
            demoWindow.type = MessageType::SEND_DATA;
            demoWindow.header = "REGISTER_RENDER_MODULE";
            demoWindow.sender = uid;
            demoWindow.payload = std::function<void()>([&]() {
                ImGui::Begin("Test Layer");
                ImGui::Text("Hello from EngineToolLayer!");
                ImGui::End();
            });
            t_engine.sendMessageToLayer(gui, demoWindow);

            LayerMessage layerManager;
            layerManager.payload = std::function<void()>([&]() {
                // Layer Manager
                ImGui::Begin("Layer Manager");
                ImGui::Text("Loaded Layers:");
                ImGui::BeginChild("Scrolling");
                auto layers = t_engine.getLayers();
                for (auto it = layers.begin(); it != layers.end(); it++) {
                    ImGui::Text("%06d: %s (%s)", it->priority, it->layer->uid.to_string().c_str(), it->layer->layerName().c_str());
	            	ImGui::SameLine();
                    if (ImGui::Button(("Kill Layer##" + it->layer->uid.to_string()).c_str())) {
                        t_engine.killLayer(it->layer->uid);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(((it->layer->active ? "Sleep##" : "Wake##") + it->layer->uid.to_string()).c_str())) {
                        LayerMessage message;
                        message.sender = this->uid;
                        message.type = it->layer->active ? MessageType::SLEEP : MessageType::WAKE;
                        t_engine.sendMessageToLayer(it->layer->uid, message);
                    }
                    if (it != layers.end() - 1) {
                        ImGui::Separator();
                    }
                }
                ImGui::EndChild();
                ImGui::End();
            });
            layerManager.type = MessageType::SEND_DATA;
            layerManager.header = "REGISTER_RENDER_MODULE";
            layerManager.sender = uid;
            t_engine.sendMessageToLayer(gui, layerManager);
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
