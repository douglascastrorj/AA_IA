#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <string>

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

using namespace std;
class Obj
{

	SDL_Rect rect; //position on the sprite
	SDL_Surface* sprite; //image of the obj
	int row,col;


public:

	Obj(){
		
	}

	~Obj(){}

	void setRow(int row){
		this->row = row;
	}

	int getRow(){
		return this->row;
	}

	void setCol(int col){
		this->col = col;
	}

	int getCol(){
		return this->col;
	}


	SDL_Surface* getSprite(){
		return this->sprite;
	}

	void setSprite(string path){
		this->sprite = IMG_Load(path.c_str());
	}

	void setSprite(SDL_Surface* sprite){
		this->sprite = sprite;
	}
	

	void blit(SDL_Surface* screen){
		SDL_BlitSurface(this->getSprite(),NULL,screen,this->getPos());
	}

	bool colide(Obj obj){
		return false;

	}

	void move(SDL_Surface *screen,int direction){
		switch (direction){
			case RIGHT:
				this->setCol(this->getCol()+1);
				break;
			case LEFT:
				this->setCol(this->getCol()-1);
				break;
			case UP:
				this->setRow(this->getRow()-1);
				break;
			case DOWN:
				this->setRow(this->getRow()+1);
				break;
		}

	}
	
};