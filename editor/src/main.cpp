#include "tritium/Engine.hpp"
#include <iostream>

int main() {
    tritium::Engine engine;
    if (!engine.initialize()) {
        std::cerr << "Editor failed to init engine!\n";
        return -1;
    }

    std::cout << "[Editor] Welcome to Tritium Editor (stub)\n";

    engine.shutdown();
    return 0;
}
