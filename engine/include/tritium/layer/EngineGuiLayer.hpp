#pragma once
#include "../api.hpp"
#include "Layer.hpp"

namespace tritium {
class TRITIUM_API EngineGuiLayer : Layer {
    public:
        EngineGuiLayer(Engine* engine) : Layer(engine) {};
        void process();
        void event();
};
} // namespace tritium
