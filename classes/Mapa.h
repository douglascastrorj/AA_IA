#include <iostream>
#include <cstdlib>
#include <fstream>

// #define BLOCK_DIM 34
#define BLOCK_DIM 15
#define DIM 20

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
	Mapa(SDL_Surface* sprite,string path){
		this->matrix = create2DArray(DIM,DIM);
		this->setSprite(sprite);

		ifstream input;
		input.open(path);
		if (input.is_open()) {
			for (int i = 0; i < DIM; i++){
				for (int j = 0; j < DIM; j++)	{
					char c;
					input.get(c);
					this->getMatrix()[i][j] = c;
					input.get(c);			
				}	
			}
		}


		
	}
	~Mapa(){}

	int getDIM(){
		return DIM;
	}

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