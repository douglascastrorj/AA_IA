#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <string>

#include <stdlib.h>

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

using namespace std;
class Obj
{
	
	int spriteNumber;
	int vel;
	SDL_Rect currentRect; //position on the sprite
	SDL_Rect pos; //position on the screen
	SDL_Surface* sprite; //image of the obj
	int row,col;
protected:
	int direction;

public:

	Obj(SDL_Surface* sprite,int spriteDIM){
		this->setSpriteNumber(0);
		this->setSprite(sprite);
		this->setPos(100,0,spriteDIM,spriteDIM);
		this->setCurrentRect(5,25,spriteDIM,spriteDIM);
		this->setRow(0);
		this->setCol(0);
		this->vel = 2;
		this->setDirection(RIGHT);
	}

	~Obj(){}

	void setVel(int vel){
		this->vel = vel;
	}

	int getVel(){
		return this->vel;
	}

	void setDirection(int direction){
		if(direction == LEFT)
			this->getCurrentRect()->y = 5;
		else if (direction == RIGHT)
			this->getCurrentRect()->y = 25;
		else if(direction == UP)
			this->getCurrentRect()->y = 45;
		else 
			this->getCurrentRect()->y = 65;

		this->direction = direction;
	}

	int getDirection(){
		return this->direction;
	}

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

	bool colide(Obj* obj){
		if(this->getRow() == obj->getRow() && this->getCol() == obj->getCol())
			return true;
		return false;
	}

	// b = BLOCK_DIM
	void move(Mapa* map,int b,int d){
		int posx;
		int newCol;

		int posy;
		int newRow;
		switch (this->getDirection()){
			case RIGHT:

				this->getPos()->x+=this->vel;
				posx = this->getPos()->x + (this->getPos()->w /2 );
				newCol = (posx/b);
				
				if(newCol < d && map->getMatrix()[this->getRow()][newCol] != 'b' )
					this->setCol(newCol);
				else this->getPos()->x-=this->vel; //undo the move

				break;
			case LEFT:
				this->getPos()->x-=this->vel;
				posx = this->getPos()->x + (this->getPos()->w /2 );
				newCol = (posx/b);
				
				if(newCol < d && map->getMatrix()[this->getRow()][newCol] != 'b' )
					this->setCol(newCol);
				else this->getPos()->x+=this->vel; //undo the move

				break;
			case UP:
				this->getPos()->y-=this->vel;
				posy = this->getPos()->y + (this->getPos()->h /2 );
				newRow = (posy/b);
				
				if(newRow < d && map->getMatrix()[newRow][this->getCol()] != 'b')
					this->setRow(newRow);
				else this->getPos()->y+=this->vel;//undo the move

				break;
			case DOWN:
				this->getPos()->y+=this->vel;
				posy = this->getPos()->y + (this->getPos()->h /2 );
				newRow = (posy/b);
				
				if(newRow < d && map->getMatrix()[newRow][this->getCol()] != 'b')
					this->setRow(newRow);
				else this->getPos()->y-=this->vel;//undo the move

				break;
		}

	}
	
};