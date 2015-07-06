#define FPS 30

#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"


#include "classes/Mapa.h"
#include "classes/Obj.h"
#include "classes/Ghost.h"

SDL_Surface* sprite = NULL;
SDL_Surface *screen;
SDL_Surface* sprite_player ;
SDL_Surface* fundo;

using namespace std;
int main(){
	SDL_Init(SDL_INIT_EVERYTHING);

	//load images and set ap screen
	screen = SDL_SetVideoMode(680,440,16,SDL_SWSURFACE);
	sprite = IMG_Load("image/block.png");
	SDL_Surface* sprite_player = IMG_Load("image/sprite.png");
	fundo = IMG_Load("image/fundo.png");

	Mapa *m = new Mapa(sprite);
	Obj *player = new Obj(sprite_player,15);

	Ghost *ghost = new Ghost(sprite_player,15);

	// ghost->getCurrentRect()->y = 85;
	// ghost->setVel(3);

	SDL_Event event;
	bool running = true;	
	while(running){

		int t1 = SDL_GetTicks();

		SDL_BlitSurface(fundo,NULL,screen,NULL);
		m->blit(screen);
		player->blit(screen);

		int row = player->getRow();
		int col = player->getCol();
		player->move(m,BLOCK_DIM,DIM);

		ghost->move(m,BLOCK_DIM,DIM,col,row);
		// if(row != player->getRow() || col != player->getCol())
		ghost->blit(screen);
		
		// ghost->move(m,BLOCK_DIM,DIM);
		// ghost->setDirection(DOWN);

		//handling the events
		while(SDL_PollEvent(&event)){
			if( event.type==SDL_QUIT){
				running = false;
			}
			if( event.type == SDL_MOUSEMOTION )	{
				
			}
			if(event.type == SDL_KEYDOWN){
				switch( event.key.keysym.sym )
				{
					case SDLK_UP: { 
						player->setDirection(UP);
						break;
					}
					case SDLK_DOWN: {
						player->setDirection(DOWN);
						break;
					}
					case SDLK_LEFT:{ 
						player->setDirection(LEFT); 
						break;
					}
					case SDLK_RIGHT:{ 
						player->setDirection(RIGHT);
						break;
					}
				}
			}
		}

		int t2 = SDL_GetTicks();
        int wait = t2 - t1;
        wait = (1000/FPS) - wait;

        if(wait > 0)
			SDL_Delay(wait);
		

		SDL_Flip(screen);

	}
	SDL_Quit();
	return 0;
}