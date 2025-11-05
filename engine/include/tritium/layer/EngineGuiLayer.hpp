#pragma once
#include "../api.hpp"
#include "Layer.hpp"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <vector>
#include <functional>

namespace tritium {
class TRITIUM_API EngineGuiLayer : public Layer {
    public:
        EngineGuiLayer(Engine& engine);
		~EngineGuiLayer();
        void process() override;
        void event(SDL_Event event) override;
		void message(LayerMessage message) override;
        std::string layerName() const override {
            return "EngineGuiLayer";
        };
    private:
        std::unordered_map<Uid, std::function<void()>> callbacks;
        std::vector<Uid> renderModuleUids;
};
} // namespace tritium
