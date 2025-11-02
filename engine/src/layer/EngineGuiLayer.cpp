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

void EngineGuiLayer::process() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // Layer Manager
    ImGui::Begin("Layer Manager");
    ImGui::Text("Loaded Layers:");
    ImGui::BeginChild("Scrolling");
    auto layers = t_engine.getLayers();
    for (auto it = layers.begin(); it != layers.end(); it++) {
        ImGui::Text("%06d: %s", it->priority, it->layer->uid.to_string().c_str());
    }
    ImGui::EndChild();
    ImGui::End();

    ImGui::Render();

    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), t_engine.getWindow().getSDLRenderer());
}

void EngineGuiLayer::event(SDL_Event event) {
    ImGui_ImplSDL3_ProcessEvent(&event);
}
