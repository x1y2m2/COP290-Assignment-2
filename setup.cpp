/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include "setup.h"

void maze_init(){
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			maze[i][j] = true;
		}
	}
}

void maze_generate(int x, int y){
	maze[x][y] = false;
	while (true){
		int t = 0;
		if((x>1)&&(cc(x-1,y))){
			t++;
		}
		if((x<WIDTH-2)&&(cc(x+1,y))){
			t++;
		}
		if((y>1)&&(cc(x,y-1))){
			t++;
		}
		if((y<HEIGHT-2)&&(cc(x,y+1))){
			t++;
		}
		if(t>0){
			int r = rand()%t;
			if((x>1)&&(cc(x-1,y))){
				if(r>0){
					r--;
				}else if(r==0){
					maze_generate(x-1,y);
					continue;
				}
			}
			if((x<WIDTH-2)&&(cc(x+1,y))){
				if(r>0){
					r--;
				}else if(r==0){
					maze_generate(x+1,y);
					continue;
				}
			}
			if((y>1)&&(cc(x,y-1))){
				if(r>0){
					r--;
				}else if(r==0){
					maze_generate(x,y-1);
					continue;
				}
			}
			if((y<HEIGHT-2)&&(cc(x,y+1))){
				if(r>0){
					r--;
				}else if(r==0){
					maze_generate(x,y+1);
					continue;
				}
			}
		}else{
			break;
		}
	}
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

void setup()
{
	srand((unsigned int)time(NULL));
	maze_init();
	maze_generate(1,1);
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			
			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render red filled quad
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
				for(int i=0;i<HEIGHT;i++){
					for(int j=0;j<WIDTH;j++){
						SDL_Rect fillRect = {12*i,12*j,12,12};
						if(maze[i][j]){
							SDL_RenderFillRect(gRenderer,&fillRect);
						}
					}
				}

				//Update screen
				pBlue;
				SDL_Rect rct = {12,12,12,12};
				SDL_RenderFillRect(gRenderer,&rct);
				//SDL_RenderPresent( gRenderer );
				int x = WIDTH-2;
				int y = HEIGHT-2;
				while(maze[y][x]){
					x--;
				}
				rct = {12*y,12*x,12,12};
				pYellow;
				SDL_RenderFillRect(gRenderer, &rct);
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();
}

bool cc(int x, int y){
	bool check = maze[x][y];
	int ch=0;
	if((x>1)&&(!maze[x-1][y])){
		ch++;
	}
	if((x<WIDTH-2)&&(!maze[x+1][y])){
		ch++;
	}
	if((y>1)&&(!maze[x][y-1])){
		ch++;
	}
	if((y<HEIGHT-2)&&(!maze[x][y+1])){
		ch++;
	}
	return check && (ch<2);
}
