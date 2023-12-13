// textures.hpp
#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filePath);

#endif // TEXTURES_HPP
