#include "tritium/Engine.hpp"
#include <iostream>

int main() {
    tritium::Engine engine;
    if (!engine.initialize()) {
        std::cerr << "Failed to init engine!\n";
        return -1;
    }

    std::cout << "[Runtime] Running game loop (stub)...\n";

    for (int i = 0; i < 3; ++i)
        std::cout << "Tick " << i << "\n";

    engine.shutdown();
    return 0;
}
