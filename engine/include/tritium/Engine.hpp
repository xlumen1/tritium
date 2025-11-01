#pragma once
#include "api.hpp"

namespace tritium {
class TRITIUM_API Engine {
public:
    Engine();
    bool initialize();
    void shutdown();
};
}
