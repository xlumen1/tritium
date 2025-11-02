#pragma once
#include "api.hpp"
#include <SDL3/SDL.h>
#include <string>
#include <stdexcept>
#include <iostream>

namespace tritium {

class TRITIUM_API Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    SDL_Window* getSDLWindow() const;
    SDL_Renderer* getSDLRenderer() const;

private:
    SDL_Window* t_window = nullptr;
    SDL_Renderer* t_renderer = nullptr;
};

} // namespace tritium
