#pragma once
#include "../api.hpp"
#include "Layer.hpp"
#include "SDL3/SDL_gpu.h"

namespace tritium {

class TRITIUM_API EngineGpuLayer : public Layer {
public:
    EngineGpuLayer(Engine& engine);
    ~EngineGpuLayer();

    void process() override;
    void event(SDL_Event event) override;

private:
    SDL_GPUDevice* device = nullptr;
    SDL_GPUTexture* render_target = nullptr;
    SDL_GPUShader* vertex_shader = nullptr;
    SDL_GPUShader* fragment_shader = nullptr;
    SDL_GPUGraphicsPipeline* graphics_pipeline = nullptr;

    void createPipeline();
};

} // namespace tritium
