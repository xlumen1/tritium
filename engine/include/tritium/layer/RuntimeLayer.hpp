#pragma once
#include "../api.hpp"
#include "Layer.hpp"

namespace tritium {
class TRITIUM_API RuntimeLayer : public Layer {
    public:
        RuntimeLayer(Engine& engine);
        void process() override;
        void event(SDL_Event event) override;
        std::string layerName() const override {
            return "RuntimeLayer";
        };
};
} // namespace tritium
