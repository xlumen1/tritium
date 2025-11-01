#include "tritium/Window.hpp"

using namespace tritium;

Window::Window(const std::string& title, int width, int height) {
    std::cout << "[Window] Initializing SDL..." << std::endl;

    // Initialize with just the video subsystem
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        const char* err = SDL_GetError();
        std::cerr << "[Window] SDL_Init failed: " << (err ? err : "Unknown error") << std::endl;
        throw std::runtime_error("SDL_Init failed");
    }

    t_window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_VULKAN);

    if (!t_window) {
        const char* err = SDL_GetError();
        std::cerr << "[Window] SDL_CreateWindow failed: " << (err ? err : "Unknown error") << std::endl;
        SDL_Quit();
        throw std::runtime_error("SDL_CreateWindow failed");
    }

    std::cout << "[Window] Window created successfully!" << std::endl;
}

Window::~Window() {
    std::cout << "[Window] Destroying window" << std::endl;
    if (t_window) {
        SDL_DestroyWindow(t_window);
        std::cout << "[Window] Window destroyed" << std::endl;
    }
    SDL_Quit();
    std::cout << "[Window] Cleanup complete" << std::endl;
}

SDL_Window* Window::GetSDLWindow() const {
    return t_window;
}
