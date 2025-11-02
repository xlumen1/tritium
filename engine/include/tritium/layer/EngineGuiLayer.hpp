#pragma once
#include "../api.hpp"
#include "Layer.hpp"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

namespace tritium {
class TRITIUM_API EngineGuiLayer : Layer {
    public:
        EngineGuiLayer(Engine& engine);
        void process() override;
        void event(SDL_Event event) override;
};
} // namespace tritium
