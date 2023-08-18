#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <SDL.h>
#include <iostream>

class LTexture
{
public:
    SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);

    //Make sure to call child destructors
    virtual ~LTexture() {};
};
#endif // !LTEXTURE_H
