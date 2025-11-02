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

    // Sample Test Window
    ImGui::Begin("Hello, World!");
    ImGui::Text("Hello, World!");
    ImGui::End();

    ImGui::Render();

    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), t_engine.getWindow().getSDLRenderer());
}

void EngineGuiLayer::event(SDL_Event event) {
    ImGui_ImplSDL3_ProcessEvent(&event);
}
