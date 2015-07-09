#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <string>
#include "astar.cpp"


#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

using namespace std;
class Ghost : public Obj
{


public:

	Ghost(SDL_Surface* sprite,int spriteDIM):  Obj( sprite, spriteDIM){
		Obj(sprite,spriteDIM);
		this->getCurrentRect()->y = 85;
		this->setVel(1);
		this->getPos()->x = 0;

	}

	~Ghost(){}

	void setDirection(int direction){
		this->direction = direction;
	}

	int getDirection(){
		return this->direction;
	}
	

	//map , pacman coordinates
	void move2(Mapa* map,int b,int d,Obj* player){
		int vc = 0;
		int rowDest = player->getRow();
		int colDest = player->getCol();
		auto answer = Astar(map->getMatrix(),map->getDIM(),map->getDIM(), Point(this->getRow(),this->getCol()), Point(rowDest, colDest ), vc );
	    if(this->colide(player))
	    	cout<<"Colidiu"<<endl;
	    if(answer.size() > 0){
		    int row = answer[answer.size()-1].first;
		    int col = answer[answer.size()-1].second;

			if(this->getCol() < col) this->setDirection(RIGHT);
		    else if (this->getCol() > col ) this->setDirection(LEFT);	    	
	    	else if (this->getRow() < row )this->setDirection(DOWN);
	    	else if (this->getRow() > row ) this->setDirection(UP);

	    	int posx;
			int newCol;

			int posy;
			int newRow;
			switch (this->getDirection()){
				case RIGHT:

					this->getPos()->x+=this->getVel();
					posx = this->getPos()->x + (this->getPos()->w /2 );
					newCol = (posx/b);
					
					if(newCol < d && map->getMatrix()[this->getRow()][newCol] != 'b' ){
						map->getMatrix()[this->getRow()][this->getCol()] = ' ';
						this->setCol(newCol);
						map->getMatrix()[this->getRow()][this->getCol()] = 'g';
					}
					else this->getPos()->x-=this->getVel(); //undo the move

					break;
				case LEFT:
					this->getPos()->x-=this->getVel();
					posx = this->getPos()->x + (this->getPos()->w /2 );
					newCol = (posx/b);
					
					if(newCol < d && map->getMatrix()[this->getRow()][newCol] != 'b' ){
						map->getMatrix()[this->getRow()][this->getCol()] = ' ';
						this->setCol(newCol);
						map->getMatrix()[this->getRow()][this->getCol()] = 'g';
					}
					else this->getPos()->x+=this->getVel(); //undo the move

					break;
				case UP:
					this->getPos()->y-=this->getVel();
					posy = this->getPos()->y + (this->getPos()->h /2 );
					newRow = (posy/b);
					
					if(newRow < d && map->getMatrix()[newRow][this->getCol()] != 'b'){
						map->getMatrix()[this->getRow()][this->getCol()] = ' ';
						this->setRow(newRow);
						map->getMatrix()[this->getRow()][this->getCol()] = 'g';
					}
						
					else this->getPos()->y+=this->getVel();//undo the move

					break;
				case DOWN:
					this->getPos()->y+=this->getVel();
					posy = this->getPos()->y + (this->getPos()->h /2 );
					newRow = (posy/b);
					
					if(newRow < d && map->getMatrix()[newRow][this->getCol()] != 'b'){
						map->getMatrix()[this->getRow()][this->getCol()] = ' ';
						this->setRow(newRow);
						map->getMatrix()[this->getRow()][this->getCol()] = 'g';
					}
					else this->getPos()->y-=this->getVel();//undo the move

					break;
			}    
		
	    }else{
	    	if(this->getCol() < colDest) this->setDirection(RIGHT);
		    else if (this->getCol() > colDest ) this->setDirection(LEFT);	    	
	    	else if (this->getRow() < rowDest )this->setDirection(DOWN);
	    	else if (this->getRow() > rowDest ) this->setDirection(UP);
	    }

	}
	
};