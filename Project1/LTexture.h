#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <SDL_ttf.h>

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

    typedef struct {
        SDL_Rect alpharect;
        SDL_Color color;
    } AlphaRect;
        

    std::vector<Entity> backgrounds;
    std::vector<Entity> returnBackgrounds() { return backgrounds; }

    std::vector<Entity> backgroundsWithRepeat;
    std::vector<Entity> returnBackgroundsWithRepeat() { return backgrounds; }

    std::vector<MyRect> backgroundRects;
    std::vector<MyRect> returnRects() { return backgroundRects; }

    std::vector<SDL_Rect> backgroundRectsWithRepeat;
    std::vector<SDL_Rect> returnRectsWithRepeat() { return backgroundRectsWithRepeat; }


    std::vector<SDL_Rect> textRects;
    std::vector<SDL_Rect> returnTextRects() { return textRects; }

    std::vector<AlphaRect> alphaRects;

    std::vector<SDL_Rect> playersRect;

    struct MyButtons {
        SDL_Rect rect;
        std::string text;
        std::string action;
        SDL_Color textColor;
        SDL_Point textPosition;
        bool active;
        int buttonID;
        int nextButton;
        SDL_Texture* texture;
    };

    struct MyText {
		SDL_Rect rect;
		std::string text;
		SDL_Color textColor;
		SDL_Point textPosition;
		SDL_Texture* texture;
	};

    int activeButton;
    int getActiveButton() { return activeButton; }

    std::vector<MyButtons> buttons;
    std::vector<MyText> texts;

    void modifyButton(int buttonID, bool active, SDL_Color color, int activeButton, SDL_Renderer* renderer);

    void createButton(SDL_Rect rect,
        std::string text,
        std::string action,
        SDL_Color textColor,
        SDL_Point textPosition,
        bool active,
        int buttonID,
        int nextButton,
        SDL_Renderer* renderer);

    void createTextRect(int x, int y, int WIDTH, int HEIGHT);

    void createText(SDL_Rect rect,
        std::string text,
        SDL_Color textColor,
        SDL_Point textPosition,
        SDL_Renderer* renderer);

    TTF_Font* fontText = NULL;

    SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
    SDL_Surface* setTextSurface(TTF_Font* font, std::string text, SDL_Color textColor);

    void addBackgroundLayer(SDL_Texture* texture, int posX, int posY);
    void addBackgroundLayer(SDL_Texture* texture, int posX, int posY, bool repeat);

    void createRect(SDL_Texture* texture, int x, int y, int WIDTH, int HEIGHT);
    void createRectWithRepeat(int x, int y, int WIDTH, int HEIGHT);

    void createRectWithColor(SDL_Color color, int x, int y, int WIDTH, int HEIGHT);

    void setActiveButton(int i) {
        if (i <= 0) {
            activeButton = 0;
        }
        else if (i >= buttons.size() - 1) {
			activeButton = buttons.size() - 1;
        }
        else {
            activeButton = i;
        }
    }

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

    bool loadText(std::string textureText, SDL_Color textColorParam, SDL_Point position, SDL_Renderer* renderer);

    //Make sure to call child destructors
    virtual ~LTexture() {};
};
#endif // !LTEXTURE_H
