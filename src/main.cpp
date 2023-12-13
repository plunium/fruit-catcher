// main.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include "textures.hpp"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int FRUIT_WIDTH = 50;
const int FRUIT_HEIGHT = 50;
const int CHARACTER_WIDTH = 100;
const int CHARACTER_HEIGHT = 100;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* gCharacterTexture = nullptr;
SDL_Texture* gFruitTexture = nullptr;

class Character {
public:
    int x, y;
    bool keyLeft;
    bool keyRight; 

    // Ajout du constructeur de character 
    Character() : x(0), y(0), keyLeft(false), keyRight(false) {}

    void handleEvent(SDL_Event& e) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                keyLeft = true;
                break;
            case SDLK_RIGHT:
                keyRight = true;
                break;
            }
        } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    keyLeft = false;
                    break;
                case SDLK_RIGHT:
                    keyRight = false;
                    break;
            }
        }
    }


    void update() {
       if (keyLeft && !keyRight) {
        x -= 5;
       } else if (keyRight && !keyLeft) {
        x += 5;
       }

        if (x < 0) {
            x = 0;
        } else if (x > SCREEN_WIDTH - CHARACTER_WIDTH) {
            x = SCREEN_WIDTH - CHARACTER_WIDTH;
        }
    }

    void render() {
        SDL_Rect characterRect = { x, y, CHARACTER_WIDTH, CHARACTER_HEIGHT };
        SDL_RenderCopy(gRenderer, gCharacterTexture, nullptr, &characterRect);
    }
};

class Fruit {
public:
    int x, y;

    void resetPosition() {
        x = rand() % (SCREEN_WIDTH - FRUIT_WIDTH);
        y = 0;
    }

    void update() {
        y += 5; // vitesse de chute des fruits

        if (y > SCREEN_HEIGHT) {
            resetPosition();
        }
    }

    void render() {
        SDL_Rect fruitRect = { x, y, FRUIT_WIDTH, FRUIT_HEIGHT };
        SDL_RenderCopy(gRenderer, gFruitTexture, nullptr, &fruitRect);
    }
};

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Fruit Catcher Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

bool loadMedia() {
        // Construction et chemin des fichiers d'images
            std::string characterPath = "res/gfx/character.png";
            std::string fruitPath = "res/gfx/fruit.png";

    gCharacterTexture = loadTexture(gRenderer, "C:\\fruit_game\\bin\\debug\\res\\gfx\\krillin.png");
    if (gCharacterTexture == nullptr) {
        std::cerr << "Failed to load character image!" << std::endl;
        return false;
    }

    gFruitTexture = loadTexture(gRenderer, "C:\\fruit_game\\bin\\debug\\res\\gfx\\apple.png");
    if (gFruitTexture == nullptr) {
        std::cerr << "Failed to load fruit image!" << std::endl;
        return false;
    }

    return true;
}

void close() {
    SDL_DestroyTexture(gCharacterTexture);
    SDL_DestroyTexture(gFruitTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    IMG_Quit();
    SDL_Quit();
}

int SDL_main(int argc, char* argv[]) {
    if (!init() || !loadMedia()) {
        std::cerr << "Failed to initialize or load media!" << std::endl;
        close();
        return 1;
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    Character character;
    character.x = SCREEN_WIDTH / 2 - CHARACTER_WIDTH / 2;
    character.y = SCREEN_HEIGHT - CHARACTER_HEIGHT;

    Fruit fruit;
    fruit.resetPosition();

    SDL_Event e;
    bool quit = false;

    while (!quit) {

        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            character.handleEvent(e);
        }

        character.update();
        character.render();

        fruit.update();
        fruit.render();

        SDL_RenderPresent(gRenderer);
        SDL_RenderClear(gRenderer);

        SDL_Delay(16);  // Ajout d'un délai pour éviter une boucle trop rapide
    }

    close();

    return 0;
}
