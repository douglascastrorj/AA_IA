#define FPS 30

#include <iostream>
#include <time.h>

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

void sleepcp(int milliseconds) // cross-platform sleep function
	{
	    clock_t time_end;
	    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
	    while (clock() < time_end)
	    {
	    }
	}

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

	Ghost *ghost1 = new Ghost(sprite_player,15);
	Ghost *ghost2= new Ghost(sprite_player,15);
	Ghost *ghost3 = new Ghost(sprite_player,15);
	Ghost *ghost4 = new Ghost(sprite_player,15);
	Ghost *ghost5 = new Ghost(sprite_player,15);

	ghost2->getPos()->x = 13*15;
	ghost2->getPos()->y = 13*15;

	ghost3->getPos()->x = 17*15;
	ghost3->getPos()->y = 19*15;

	ghost4->getPos()->x = 5*15;
	ghost4->getPos()->y = 5*15;

	ghost5->getPos()->x = 8*15;
	ghost5->getPos()->y = 10*15;


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

		// ghost->move(m,BLOCK_DIM,DIM);
		ghost1->move2(m,BLOCK_DIM,DIM,row,col);
		ghost1->blit(screen);

		ghost2->move2(m,BLOCK_DIM,DIM,row+1,col);
		ghost2->blit(screen);

		ghost3->move2(m,BLOCK_DIM,DIM,row,col+1);
		ghost3->blit(screen);

		ghost4->move2(m,BLOCK_DIM,DIM,row-1,col);
		ghost4->blit(screen);

		ghost5->move2(m,BLOCK_DIM,DIM,row,col-1);
		ghost5->blit(screen);
		
		
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
		// sleepcp(10000);

	}
	SDL_Quit();
	return 0;
}