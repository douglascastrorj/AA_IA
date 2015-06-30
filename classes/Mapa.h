#include <iostream>
#include <cstdlib>

#define BLOCK_DIM 34

#define DIM 10

using namespace std;
class Mapa
{
	char matrix[DIM][DIM];
	SDL_Surface* sprite;
public:
	Mapa(SDL_Surface* sprite){
		this->setSprite(sprite);

		for (int i = 0; i < DIM; ++i){
			for(int j = 0 ; j < DIM ; j++){
				// int c = rand() % 2;
				// if(c > 0) 
				matrix[i][j] = ' ';
				// else matrix[i][j] = 'b';

			}
		}	
		matrix[1][2] = 'b';	
		matrix[1][7] = 'b';

		matrix[2][1] = 'b';
		matrix[2][2] = 'b';
		matrix[2][4] = 'b';
		matrix[2][5] = 'b';
		matrix[2][7] = 'b';
		matrix[2][8] = 'b';

		matrix[3][2] = 'b';
		matrix[3][7] = 'b';

		matrix[4][2] = 'b';
		matrix[4][7] = 'b';

		matrix[5][6] = 'b';

		matrix[7][1] = 'b';
		matrix[7][4] = 'b';
		matrix[7][5] = 'b';
		matrix[7][7] = 'b';
		matrix[7][8] = 'b';

		matrix[8][1] = 'b';
	}
	~Mapa(){}

	SDL_Surface* getSprite(){
		return this->sprite;
	}

	void setSprite(SDL_Surface* sprite){
		this->sprite = sprite;

	}

	void blit(SDL_Surface* screen){
		SDL_Rect pos = {0,0,BLOCK_DIM,BLOCK_DIM};
		
		for (int i = 0; i < DIM; i++){
			pos.x = 0;
			for(int j = 0; j<DIM ;j++){
				if(this->matrix[i][j] == 'b')
					SDL_BlitSurface(this->getSprite(),NULL,screen,&pos);
				pos.x += BLOCK_DIM;
			}
			pos.y += BLOCK_DIM;
		}
	}
	/* data */
};