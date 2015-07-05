#include <iostream>
#include <cstdlib>

// #define BLOCK_DIM 34
#define BLOCK_DIM 15
#define DIM 10

using namespace std;
class Mapa
{
	char **matrix;
	SDL_Surface* sprite;

	char** create2DArray(unsigned height, unsigned width)
	{
		char** array2D = 0;
		array2D = new char*[height];

		for (int h = 0; h < height; h++){
			array2D[h] = new char[width];
			for (int w = 0; w < width; w++)	{
				// fill in some initial values
				// (filling in zeros would be more logic, but this is just for the example)
				array2D[h][w] = ' ';
			}
		}

		return array2D;
	}
public:
	Mapa(SDL_Surface* sprite){
		this->matrix = create2DArray(DIM,DIM);
		this->setSprite(sprite);

		
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

	char** getMatrix(){
		return this->matrix;
	}

	void blit(SDL_Surface* screen){
		SDL_Rect pos = {0,0,BLOCK_DIM,BLOCK_DIM};
		SDL_Rect sprite_pos = {0,0,BLOCK_DIM,BLOCK_DIM};
		
		for (int i = 0; i < DIM; i++){
			pos.x = 0;
			for(int j = 0; j<DIM ;j++){
				if(this->matrix[i][j] == 'b')
					SDL_BlitSurface(this->getSprite(),&sprite_pos,screen,&pos);
				pos.x += BLOCK_DIM;
			}
			pos.y += BLOCK_DIM;
		}
	}
	
};