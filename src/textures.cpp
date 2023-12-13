// textures.cpp
#include "textures.hpp"

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filePath) {
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(filePath.c_str());

    if (surface == nullptr) {
        std::cerr << "Failed to load image " << filePath << "! SDL_image Error: " << IMG_GetError() << std::endl;
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr) {
            std::cerr << "Unable to create texture from " << filePath << "! SDL Error: " << SDL_GetError() << std::endl;
        } else {
            std::cout << "Texture loaded successfully from " << filePath << std::endl;
        }
        SDL_FreeSurface(surface);
    }

    return texture;
}



