#pragma once
#include "../api.hpp"
#include "../uid.hpp"
#include <iostream>

namespace tritium {
class Engine; // Prevents circular dep

class TRITIUM_API Layer {
public:
    Layer(Engine* engine) : t_engine(engine) {
        uid = Uid::generate();
        std::cout << "[Layer] Layer " << uid.to_string() << " created" << std::endl;
    };
    ~Layer() {
        std::cout << "[Layer] Layer " << uid.to_string() << " destroyed" << std::endl;
    };
    virtual void process() = 0;
    virtual void event() = 0;

    Uid uid;
private:
    Engine* t_engine;
};
} // namespace tritium
