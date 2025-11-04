#pragma once
#include "api.hpp"
#include "Window.hpp"
#include "layer/Layer.hpp"
#include "uid.hpp"
#include <vector>
#include <memory>

namespace tritium {

struct EngineLayerData {
    std::shared_ptr<Layer> layer;
    int priority;
};

class TRITIUM_API Engine {
public:
    Engine(int width = 1280, int height = 720);
    bool initialize();
    void shutdown();

    Window& getWindow();
    void mainLoop();
    Uid createLayer(std::shared_ptr<Layer> layer, int priority);
    void killLayer(Uid uid);
	void cleanLayers();
    std::vector<EngineLayerData> getLayers();
private:
    bool running;
    Window window;
    std::vector<EngineLayerData> layers;
	std::vector<Uid> dyingLayers;
};
} // namespace tritium
