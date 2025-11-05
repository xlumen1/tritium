#pragma once
#include "../api.hpp"
#include "Layer.hpp"
#include "imgui.h"

namespace tritium {
    class TRITIUM_API EngineToolLayer : public Layer {
        public:
            EngineToolLayer(Engine& engine);
		    ~EngineToolLayer();
            void process() override;
            void event(SDL_Event event) override;
		    void message(LayerMessage message) override;
            std::string layerName() const override {
                return "EngineToolLayer";
            };
        private:
            bool has_init = false;
    };
} // namespace tritium