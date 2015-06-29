#define FPS 30

#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"


#include "classes/Mapa.h"

SDL_Surface* sprite = NULL;
SDL_Surface *screen;
using namespace std;
int main(){
	SDL_Init(SDL_INIT_EVERYTHING);

	//load images and set ap screen
	screen = SDL_SetVideoMode(900,900,8,SDL_SWSURFACE);
	sprite = IMG_Load("image/sprite.png");

	if(sprite == NULL)
		cout << "ghjklç\n";


	Mapa *m = new Mapa(sprite);

	SDL_Event event;
	bool running = true;	
	while(running){

		int t1 = SDL_GetTicks();

		m->blit(screen);

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
					case SDLK_UP: {  break;}
					case SDLK_DOWN: {  break;}
					case SDLK_LEFT:{  break;}
					case SDLK_RIGHT:{ break;}
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