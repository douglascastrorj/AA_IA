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

	int spriteNumber;
	SDL_Rect currentRect; //position on the sprite
	SDL_Rect pos; //position on the screen
	SDL_Surface* sprite; //image of the obj
	int row,col;


public:

	Obj(SDL_Surface* sprite,int spriteDIM){
		this->setSpriteNumber(0);
		this->setSprite(sprite);
		this->setPos(0,0,spriteDIM,spriteDIM);
		this->setCurrentRect(0,20,spriteDIM,spriteDIM);
	}

	~Obj(){}

	void setSpriteNumber(int n){
		this->spriteNumber = n;
	}

	int getSpriteNumber(){
		return this->spriteNumber;
	}

	SDL_Rect* getPos(){
		return &this->pos;
	}

	void setPos(int x,int y,int w,int h){
		this->pos.x = x;
		this->pos.y = y;
		this->pos.w = w;
		this->pos.h = h;
	}

	SDL_Rect* getCurrentRect(){
		return &this->currentRect;
	}

	void setCurrentRect(int x,int y,int w,int h){
		this->currentRect.x = x;
		this->currentRect.y = y;
		this->currentRect.w = w;
		this->currentRect.h = h;
	}

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
		SDL_BlitSurface(this->getSprite(),this->getCurrentRect(),screen,this->getPos());
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