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

	Ghost(SDL_Surface* sprite,int spriteDIM):Obj( sprite, spriteDIM){
		Obj(sprite,spriteDIM);
		this->getCurrentRect()->y = 85;
		this->setVel(2);
		this->getPos()->x = 0;

	}

	~Ghost(){}

	

	//map , pacman coordinates
	void move2(Mapa* map,int b,int d,int rowDest,int colDest){
		int vc = 0;
		auto answer = Astar(map->getMatrix(),map->getDIM(),map->getDIM(), Point(this->getRow(),this->getCol()), Point(rowDest, colDest ), vc );
	    for(int i = 0; i < answer.size(); i++)
	        cout << "linha " << answer[i].first << " coluna " << answer[i].second <<endl;
		
	    // for(int i = 0; i < answer.size(); i++)
	    //     cout <<"Col: "<<  answer[i].first << " Row: " << answer[i].second <<endl;

	    if(answer.size() > 0){
		    int row = answer[answer.size()-1].first;
		    int col = answer[answer.size()-1].second;
			cout <<"TEM Q IR PARA Col: "<<  col<< " Row: " <<row <<endl;	
			cout << "ESTOU EM col " << this->getCol() << " ROW " << this->getRow() <<endl;	

			if(this->getCol() < col) this->setDirection(RIGHT);
		    else if (this->getCol() > col ) this->setDirection(LEFT);	    	
	    	else if (this->getRow() < row )this->setDirection(DOWN);
	    	else if (this->getRow() > row ) this->setDirection(UP);

	    	// cout << this->getDirection() << endl;
	    	if (this->getDirection() == RIGHT)
	    		cout << "RIGHT" <<endl;
	    	if (this->getDirection() == LEFT)
	    		cout << "LEFT" <<endl;
	    	if (this->getDirection() == DOWN)
	    		cout << "UP" <<endl;
	    	if (this->getDirection() == UP)
	    		cout << "DOWN" <<endl;

	    	int posx;
			int newCol;

			int posy;
			int newRow;
			switch (this->getDirection()){
				case RIGHT:

					this->getPos()->x+=this->getVel();
					posx = this->getPos()->x + (this->getPos()->w /2 );
					newCol = (posx/b);
					
					if(newCol < d && map->getMatrix()[this->getRow()][newCol] != 'b' )
						this->setCol(newCol);
					else this->getPos()->x-=this->getVel(); //undo the move

					break;
				case LEFT:
					this->getPos()->x-=this->getVel();
					posx = this->getPos()->x + (this->getPos()->w /2 );
					newCol = (posx/b);
					
					if(newCol < d && map->getMatrix()[this->getRow()][newCol] != 'b' )
						this->setCol(newCol);
					else this->getPos()->x+=this->getVel(); //undo the move

					break;
				case UP:
					this->getPos()->y-=this->getVel();
					posy = this->getPos()->y + (this->getPos()->h /2 );
					newRow = (posy/b);
					
					if(newRow < d && map->getMatrix()[newRow][this->getCol()] != 'b')
						this->setRow(newRow);
					else this->getPos()->y+=this->getVel();//undo the move

					break;
				case DOWN:
					this->getPos()->y+=this->getVel();
					posy = this->getPos()->y + (this->getPos()->h /2 );
					newRow = (posy/b);
					
					if(newRow < d && map->getMatrix()[newRow][this->getCol()] != 'b')
						this->setRow(newRow);
					else this->getPos()->y-=this->getVel();//undo the move

					break;
			}    
		
	    } 
	    


	}
	
};