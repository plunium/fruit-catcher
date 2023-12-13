# fruit-catcher

1 fichier main avec les fonctions principales du code et 2 fichiers textures pour le SDL_renderer

Projet d'un jeu de type "Fruit  Catcher", 1 personnage tenant un "récipient" pour attraper des fruits tombant aléatoirement du haut de l'écran.
Idées :
- Menu principal avec boutton "jouer", bouton "review scoring" pour voir le score des parties précédentes
- Ajouter un système de scoring
- Ajouter des "bombes" ou objets qui font mourir le joueur si attrapés


l'idée était de d'abord définir la fonction 'main' qui est le point d'entrée du programme qui contient la boucle principale des événements la mise à jour des objets.

Dans le fichier main : 

int main(int argc, char* argv[]) {
    // ...

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            character.handleEvent(e);
        }

        character.render();

        fruit.update();
        fruit.render();

        SDL_RenderPresent(gRenderer);
        SDL_RenderClear(gRenderer);

        SDL_Delay(16);  // Ajout d'un léger délai pour éviter une boucle trop rapide
    }

    close();

    return 0;
}

J'ai créé la classe "character" qui définit les propriétés du personnage (position, direction et vélocité) :

class Character {
public:
    int x, y;
    int direction;
    int velocity;

    // ...
};

Fonctions de la classe "character" qui définissent le comportement du personnage et son rendu dans la fenêtre :

void Character::handleEvent(SDL_Event& e);
void Character::setDirection(int dir);
void Character::render();



La classe "fruit" qui définit les propriétés associés aux fruits et leurs positions : 

class Fruit {
public:
    int x, y;

    // ...
};

Fonctions de la classe "fruit", ces fonctions définissent le comportement des fruits, notamment la réinitialisation de leur position, la mise à jour de leur position (pour simuler la chute), et leur rendu :

void Fruit::resetPosition();
void Fruit::update();
void Fruit::render();


Les constantes qui définissent les dimensions de la fenêtre, des fruits et du personnage :

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int FRUIT_WIDTH = 50;
const int FRUIT_HEIGHT = 50;
const int CHARACTER_WIDTH = 100;
const int CHARACTER_HEIGHT = 100;

La déclaration des éléments de SDL qui représentent la dimension de la fenêtre .exe, la texture des fruits et de notre character :

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* gCharacterTexture = nullptr;
SDL_Texture* gFruitTexture = nullptr;

Les fonctions d'initialisation et de fermeture responsables de l'initialisation de SDL, du chargement des médias (textures), et de la fermeture propre du programme :

bool init();
bool loadMedia();
void close();

J'ai crée deux fichier "textures.cpp" et "textures.hpp" qui seront responsables du chargement des textures à partir des fichiers .png

La fonction de gestion des textures dans "textures.hpp" :

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filePath);
