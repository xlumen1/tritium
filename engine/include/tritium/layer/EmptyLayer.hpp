#pragma once
#include "../api.hpp"
#include "Layer.hpp"

namespace tritium {
class TRITIUM_API EmptyLayer : public Layer {
    public:
        EmptyLayer(Engine& engine) : Layer(engine) {};
        void process() override {};
        void event(SDL_Event event) override {};
		void message(LayerMessage message) override {};
        std::string layerName() const override {
            return "EmptyLayer";
        };
};
} // namespace tritium
