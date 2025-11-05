#pragma once
#include "../api.hpp"
#include "../uid.hpp"
#include "../MessageType.hpp"
#include <iostream>
#include <any>
#include <SDL3/SDL.h>

namespace tritium {
class Engine; // Prevents circular dep

struct TRITIUM_API LayerMessage {
    Uid sender;
    MessageType type;
    std::string header;
    std::any payload;
};

class TRITIUM_API Layer {
public:
    Layer(Engine& engine) : t_engine(engine) {
        uid = Uid::generate();
        std::cout << "[Layer] Layer " << uid.to_string() << " created" << std::endl;
    };
    ~Layer() {
        std::cout << "[Layer] Layer " << uid.to_string() << " destroyed" << std::endl;
    };
    virtual void process() = 0;
    virtual void event(SDL_Event event) = 0;
	virtual void message(LayerMessage message) = 0;
    virtual std::string layerName() const = 0;

    Uid uid;
    bool active{true};
protected:
    Engine& t_engine;
};
} // namespace tritium
