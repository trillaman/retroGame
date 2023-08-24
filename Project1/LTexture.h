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
        bool repeat;
    } Entity;

    typedef struct {
        SDL_Rect stretchRect;
        SDL_Texture* texture;
    } MyRect;
        

    std::vector<Entity> backgrounds;
    std::vector<Entity> returnBackgrounds() { return backgrounds; }

    std::vector<Entity> backgroundsWithRepeat;
    std::vector<Entity> returnBackgroundsWithRepeat() { return backgrounds; }

    std::vector<MyRect> backgroundRects;
    std::vector<MyRect> returnRects() { return backgroundRects; }

    std::vector<SDL_Rect> backgroundRectsWithRepeat;
    std::vector<SDL_Rect> returnRectsWithRepeat() { return backgroundRectsWithRepeat; }


    SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);

    void addBackgroundLayer(SDL_Texture* texture, int posX, int posY);
    void addBackgroundLayer(SDL_Texture* texture, int posX, int posY, bool repeat);

    void createRect(SDL_Texture* texture, int x, int y, int WIDTH, int HEIGHT);
    void createRectWithRepeat(int x, int y, int WIDTH, int HEIGHT);

    SDL_Point getTextureSize(SDL_Texture* texture) {
        SDL_Point size;
        SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
        return size;
    }

    SDL_Point getTextureWidthInPixels(SDL_Texture* texture) {
		SDL_Point size;
		SDL_QueryTexture(texture, NULL, NULL, &size.x, NULL);
		return size;
	}

    std::vector<SDL_Rect> getRectsWithRepeat() {};

    bool loadText(std::string textureText, SDL_Color textColorParam, SDL_Renderer* renderer);

    //Make sure to call child destructors
    virtual ~LTexture() {};
};
#endif // !LTEXTURE_H
