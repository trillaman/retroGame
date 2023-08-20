#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>

class LTexture
{
public:
    typedef struct {
        int x;
        int y;
        SDL_Texture* texture;
    } Entity;

    std::vector<Entity> backgrounds;
    std::vector<Entity> returnBackgrounds() { return backgrounds; }

    std::vector<SDL_Rect> backgroundRects;
    std::vector<SDL_Rect> returnRects() { return backgroundRects; }

    SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
    
    void addBackgroundLayer(SDL_Texture* texture, int posX, int posY);
    void createRect(int x, int y, int WIDTH, int HEIGHT);
    
    
    //Make sure to call child destructors
    virtual ~LTexture() {};
};
#endif // !LTEXTURE_H
