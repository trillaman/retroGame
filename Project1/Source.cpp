#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;
SDL_Texture* texture = nullptr;

typedef struct {
	int x;
	int y;
	SDL_Texture* texture;
} Entity;

class MyScene {
public:
	void Update();
	void Render();
	void Destroy();
	void Load();
	void Unload();
	void addBackgroundLayer(SDL_Texture* texture, int posX, int posY);
	void createRect(int x, int y, int WIDTH, int HEIGHT);

	std::vector<Entity> backgrounds;
	std::vector<Entity> returnBackgrounds() { return backgrounds; }

	std::vector<SDL_Rect> backgroundRects;
	std::vector<SDL_Rect> returnRects() { return backgroundRects; }
	

};

void MyScene::addBackgroundLayer(SDL_Texture* texture, int posX, int posY) {
	printf("Adding background");
	Entity bg = { 0, 0, nullptr };
	memset(&bg, 0, sizeof(Entity));
	bg.x = posX;
	bg.y = posY;
	bg.texture = texture;
	this->backgrounds.push_back(bg);
}

void MyScene::createRect(int x, int y, int WIDTH, int HEIGHT) {
		SDL_Rect stretchRect;
		stretchRect.x = x;
		stretchRect.y = y;
		stretchRect.w = WIDTH;
		stretchRect.h = HEIGHT;
		this->backgroundRects.push_back(stretchRect);
}



void initSDL(void) {
    int rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    int windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

}

void prepareScene(void) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void presentScene(void) {
    SDL_RenderPresent(renderer);
}

SDL_Texture* loadTexture(std::string path) {
	SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = nullptr;
	loadedSurface = IMG_Load(path.c_str());
   
    if (loadedSurface == NULL) {
        printf("Unable to load texture\n");
    }
    else {
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture\n");
		}
		SDL_FreeSurface(loadedSurface);
    }
	SDL_SetSurfaceBlendMode(loadedSurface, SDL_BLENDMODE_BLEND);
	printf("Texture loaded");
	return newTexture;
}


void closeSDL(void) {
	SDL_DestroyTexture(texture);
	texture = nullptr;
    
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    bool quit = false;
    
    SDL_Event e;
    
    initSDL();
    
	MyScene myscene;
	
	myscene.addBackgroundLayer(loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\BG\\Layer_0000_9.png"), 0,0);
    myscene.addBackgroundLayer(loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\BG\\Layer_0001_8.png"), 0, -6);

	std::vector<Entity> backgrounds = myscene.returnBackgrounds();

	for (int i = 0; i < backgrounds.size(); i++) {
		myscene.createRect(backgrounds[i].x, backgrounds[i].y, SCREEN_WIDTH, SCREEN_HEIGHT);
		printf("%d, %d", backgrounds[i].x, backgrounds[i].y);
	}

	std::vector<SDL_Rect> rects = myscene.returnRects();

    while(!quit){
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
        prepareScene();

		for (int i = 0; i < backgrounds.size(); i++) {
			SDL_RenderCopy(renderer, backgrounds[i].texture, NULL, &rects[i]);
		}

		presentScene();
        SDL_Delay(16);
    }

    closeSDL();

    return 0;
}