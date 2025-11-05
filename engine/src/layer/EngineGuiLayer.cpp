#include "tritium/layer/EngineGuiLayer.hpp"
#include "tritium/Engine.hpp"
#include <iostream>

using namespace tritium;

EngineGuiLayer::EngineGuiLayer(Engine& engine) : Layer(engine) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(1.0);
    style.FontScaleDpi = 1.0;

    ImGui_ImplSDL3_InitForSDLRenderer(t_engine.getWindow().getSDLWindow(), t_engine.getWindow().getSDLRenderer());
    ImGui_ImplSDLRenderer3_Init(t_engine.getWindow().getSDLRenderer());
}

EngineGuiLayer::~EngineGuiLayer() {
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();

	ImGui::DestroyContext();
}

void EngineGuiLayer::process() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Quit", "Alt+F4")) {
                t_engine.scheduleKill();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Callback windows
    for (auto it = renderModuleUids.begin(); it != renderModuleUids.end(); it++) {
        callbacks.at(*it)();
    }

    ImGui::Render();

    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), t_engine.getWindow().getSDLRenderer());
}

void EngineGuiLayer::event(SDL_Event event) {
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void EngineGuiLayer::message(LayerMessage message) {
    std::cout << "[EngineGuiLayer] Got message from " << message.sender.to_string() << " with header " << message.header << std::endl;
    if (message.type == MessageType::SLEEP) {
        if (active) {
            std::cout << "[EngineGuiLayer] Going to sleep." << std::endl;
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
    if (message.type == MessageType::SEND_DATA) {
        if (message.header.compare("REGISTER_RENDER_MODULE") == 0) {
            try {
                auto nfuid = Uid::generate();
                auto func = std::any_cast<std::function<void()>>(message.payload);
                callbacks[nfuid] = func;
                renderModuleUids.push_back(nfuid);
                std::cout << "[EngineGuiLayer] Registered render module from layer " << message.sender.to_string() << std::endl;
            } catch (const std::bad_any_cast& e) {
                std::cerr << "[EngineGuiLayer] Failed to register render module from layer " << message.sender.to_string() << ": " << e.what() << std::endl;
            }
        }
    }

}
