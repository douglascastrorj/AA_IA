#include <iostream>
#include <cstdlib>

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

		matrix[1][12] = 'b';	
		matrix[1][17] = 'b';

		matrix[2][10] = 'b';
		matrix[2][11] = 'b';
		matrix[2][14] = 'b';
		matrix[2][15] = 'b';
		matrix[2][17] = 'b';
		matrix[2][18] = 'b';

		matrix[3][12] = 'b';
		matrix[3][17] = 'b';

		matrix[4][12] = 'b';
		matrix[4][17] = 'b';

		matrix[5][16] = 'b';

		matrix[7][11] = 'b';
		matrix[7][14] = 'b';
		matrix[7][15] = 'b';
		matrix[7][17] = 'b';
		matrix[7][18] = 'b';

		matrix[8][11] = 'b';


		matrix[11][2] = 'b';	
		matrix[11][7] = 'b';

		matrix[12][1] = 'b';
		matrix[12][2] = 'b';
		matrix[12][4] = 'b';
		matrix[12][5] = 'b';
		matrix[12][7] = 'b';
		matrix[12][8] = 'b';

		matrix[13][2] = 'b';
		matrix[13][7] = 'b';

		matrix[14][2] = 'b';
		matrix[14][7] = 'b';

		matrix[15][6] = 'b';

		matrix[17][1] = 'b';
		matrix[17][4] = 'b';
		matrix[17][5] = 'b';
		matrix[17][7] = 'b';
		matrix[17][8] = 'b';

		matrix[18][1] = 'b';

		matrix[11][12] = 'b';	
		matrix[11][17] = 'b';

		matrix[12][10] = 'b';
		matrix[12][11] = 'b';
		matrix[12][14] = 'b';
		matrix[12][15] = 'b';
		matrix[12][17] = 'b';
		matrix[12][18] = 'b';

		matrix[13][12] = 'b';
		matrix[13][17] = 'b';

		matrix[14][12] = 'b';
		matrix[14][17] = 'b';

		matrix[15][16] = 'b';

		matrix[17][11] = 'b';
		matrix[17][14] = 'b';
		matrix[17][15] = 'b';
		matrix[17][17] = 'b';
		matrix[17][18] = 'b';

		matrix[18][11] = 'b';





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