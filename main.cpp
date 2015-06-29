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
	sprite = IMG_Load("image/block.png");



	if(sprite == NULL)
		cout << "ghjklç\n";

	
	Mapa *m = new Mapa(sprite);

	SDL_BlitSurface(sprite,NULL,screen,NULL);
	
	// m->blit(screen);
	SDL_Delay(1000);
	SDL_Quit();
	return 0;
}