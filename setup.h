#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>

using namespace std;

#define WIDTH 40
#define HEIGHT 40

#define WHITE SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF )
#define pBlue SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF )
#define pYellow SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF )

bool maze[HEIGHT][WIDTH];

bool cc(int x, int y);

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

void maze_init();
void maze_generate(int x, int y);
void setup();
