#include <iostream>



#define DIM 20

using namespace std;
class Mapa
{
	char matrix[DIM][DIM];
	SDL_Surface* sprite;
public:
	Mapa(SDL_Surface* sprite){
		this->setSprite(sprite);
		for (int i = 0; i < DIM; ++i){
			for(int j = 0 ; j < DIM ; j++)
				matrix[i][j] = '-';
		}		
	}
	~Mapa(){}

	SDL_Surface* getSprite(){
		return this->sprite;
	}

	void setSprite(SDL_Surface* sprite){
		this->sprite = sprite;

	}

	void blit(SDL_Surface* screen){
		SDL_BlitSurface(this->getSprite(),NULL,screen,NULL);
	}
	/* data */
};