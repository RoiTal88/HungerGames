#include "heaumanPlayer.h"


#define MAX_ARROW_FOR_PLAYER 9


heaumanPlayer::heaumanPlayer(){
	isInGame = false;
	direction =-1;
	moveCounter = 0;
	vitality= 1000;
	arrows= 2;
	wallBlowingArrows = 1;
	wallPircingArrows = 1;
	hasNotKilled = true;
}



void heaumanPlayer::turnPlayerActive(){
	isInGame = true;

}
void heaumanPlayer::movePlayer(char dir ,board* b){
	int posX,posY;
	char temp;
	
	this->returnPos(posX,posY);

	if(dir == 'W' || dir == 'w'
		|| dir == 'S' || dir == 's'
		|| dir == 'A' || dir == 'a'
		|| dir == 'D' || dir == 'd')
		direction = dir;

	
	if(direction != -1){

		if((posY == 0 && (direction == 'W' || direction == 'w')) ||
			( posY == 23 && (direction == 'S' || direction == 's')) ||
			( posX == 0 && (direction == 'A' || direction == 'a')) ||
			( posX == 78 && (direction == 'D' || direction == 'd'))){

			this->removePlayer(posX,posY);
			if(posY == 0 && (direction == 'W' || direction == 'w')){
				temp = b->returnCharOnBoard(posX, posY + 23);
				if(temp != 'W' && temp != 'w' && temp != 'O' && temp != 'o')
					this->setNewPos(posX, posY + 23);
				else{
					direction = -1;
					this->drawPlayer();
					return;
				}
			}
			else if( posY == 23 && (direction == 'S' || direction == 's')){
				temp = b->returnCharOnBoard(posX, posY - 23);
				if(temp != 'W' && temp != 'w' && temp != 'O' && temp != 'o')
					this->setNewPos(posX, posY - 23);
				else{
					direction = -1;
					this->drawPlayer();
					return;
				}
				
			}

			else if( posX == 0 && (direction == 'A' || direction == 'a')){
				temp = b->returnCharOnBoard(posX + 78, posY);
				if(temp != 'W' && temp != 'w' && temp != 'O' && temp != 'o')
					this->setNewPos(posX + 78, posY);
				else{
					direction = -1;
					this->drawPlayer();
					return;
				}
				
			}

			else if( posX == 78 && (direction == 'D' || direction == 'd')){
				temp = b->returnCharOnBoard(posX - 78, posY);
				if(temp != 'W' && temp != 'w' && temp != 'O' && temp != 'o')
					this->setNewPos(posX - 78, posY);
				else{
					direction = -1;
					this->drawPlayer();
					return;
				}				
				
			}
			if(temp == 'B')
				this->hitByBomb();
			else if(temp == 'F')
				this->stepedOnFood();
			else if(temp == 'Q')
				this ->stepedOnQuiver();
			b->writeCharToMatrix(x,y,' ');

			this->drawPlayer();

			return;
			}
		else{
			/*
			((posY == 0 && (direction == 'W' || direction == 'w')) ||
			( posY == 23 && (direction == 'S' || direction == 's')) ||
			( posX == 0 && (direction == 'A' || direction == 'a')) ||
			( posX == 78 && (direction == 'D' || direction == 'd'))){
			*/
			if(direction == 'W' || direction == 'w'){//up
				this->removePlayer(posX,posY);
				temp = b->returnCharWithDirection(posX,posY,2);
				if(temp == 'W' || temp == 'w' || temp == 'O' || temp == 'o' )
					direction = -1;

				else{
					if(temp == 'B')
						this->hitByBomb();
					else if(temp == 'F')
						this->stepedOnFood();
					else if(temp == 'Q')
						this ->stepedOnQuiver();
					this->setNewPos(posX,posY-1);
				}
			}
			else if(direction == 'S' || direction == 's'){//down
				this->removePlayer(posX,posY);
				temp = b->returnCharWithDirection(posX,posY,3);
				if(temp == 'W' || temp == 'w' || temp == 'O' || temp == 'o')
					direction = -1;
				else{
					if(temp == 'B')
						this->hitByBomb();
					else if(temp == 'F')
						this->stepedOnFood();
					else if(temp == 'Q')
						this ->stepedOnQuiver();
					this->setNewPos(posX,posY+1);
				}
			}
			else if(direction == 'A' || direction == 'a'){//left
				this->removePlayer(posX,posY);
				temp = b->returnCharWithDirection(posX,posY,1);
				if(temp == 'W' || temp == 'w' || temp == 'O' || temp == 'o')
					direction = -1;
				else{
					if(temp == 'B')
						this->hitByBomb();
					else if(temp == 'F')
						this->stepedOnFood();
					else if(temp == 'Q')
						this ->stepedOnQuiver();
					this->setNewPos(posX-1,posY);
					
				}
			}
			else if((direction == 'D' || direction == 'd')){//right
				this->removePlayer(posX,posY);
				temp = b->returnCharWithDirection(posX,posY,0);
				if(temp == 'W' || temp == 'w' || temp == 'O' || temp == 'o' )
					direction = -1;
				else{
					
					if(temp == 'B')
						this->hitByBomb();
					else if(temp == 'F')
						this->stepedOnFood();
					else if(temp == 'Q')
						this ->stepedOnQuiver();
					this->setNewPos(posX+1,posY);

				}
				
			}
			
			this->drawPlayer();
			b->writeCharToMatrix(posX,posY,' ');
		}
	}
		
	
		
	
	moveCounter++;
}

void heaumanPlayer::setNewPos(int x1, int y1){
	x=x1;
	y=y1;
}

void heaumanPlayer::drawPlayer ()const{
	gotoxy(x,y);
	cout << symbol;
}

void heaumanPlayer::removePlayer(int x1,int y1)const{
	gotoxy(x,y);
	cout << ' ';

}

void heaumanPlayer::hitByArrow (){
	vitality -= 500;

}

void heaumanPlayer::hitByBomb (){     //the player has step by a bomb
	vitality -= 750;
}
void heaumanPlayer::hitBycollision1(){ //when the player have the highest vitality
	vitality -= 10;
}
void heaumanPlayer::hitBycollision2(){ //when the player have low vitality from other player
	vitality -= 200;
}
void heaumanPlayer::hitBycollision3(){ //when the players vitality are the same level
	vitality -= 50;
}
void heaumanPlayer::stepedOnFood(){    //when steping on food
	vitality += 200;
}
void heaumanPlayer::stepedOnQuiver(){  //when stepping on arrow quiver
	arrows += 2;
	wallBlowingArrows++;
	wallPircingArrows++;

	if(arrows > MAX_ARROW_FOR_PLAYER)
		arrows = MAX_ARROW_FOR_PLAYER;
	if(wallBlowingArrows > MAX_ARROW_FOR_PLAYER)
		wallBlowingArrows = MAX_ARROW_FOR_PLAYER;
	if(wallPircingArrows > MAX_ARROW_FOR_PLAYER)
		wallPircingArrows = 9;

}

void heaumanPlayer::firedArrow(){
	arrows -= 1;
}



void heaumanPlayer::returnPos(int &x1, int &y1)const{
	x1 =x ;
	y1 =y;

}


void heaumanPlayer::changPos(){
	x= rand()%79;
	y= rand()%24;

}




char heaumanPlayer::retuenSymbol()const{
	return symbol;

}





void heaumanPlayer::writePlayerStatus(int ScoreBoardXcord , int ScoreBoardYcord)const{
	int i;
	for(i=0;i<10;i++){
		gotoxy(ScoreBoardXcord+i,ScoreBoardYcord);
		cout << " ";
	}
	gotoxy(ScoreBoardXcord,ScoreBoardYcord);
	cout <<symbol << " " << vitality  <<" " <<arrows;

}
void heaumanPlayer::writeStateBox(int x1, int y1)const{
	gotoxy(x1,y1);
	cout<<"PL Lif Arr";
}

void heaumanPlayer::returnVitality(int& vital)const{
	vital = vitality;
}

void heaumanPlayer::returnNumOfArrows(int& x,int& y ,int& z)const{
	x = arrows;
	y = wallBlowingArrows;
	z = wallPircingArrows;
}

void heaumanPlayer::putSymbol(int i){
	symbol = i + 'A';

}

void heaumanPlayer::removeAllArrows(){
	arrows = 0;

}
bool heaumanPlayer::chackIfAlive()const{
	return hasNotKilled;
}

void heaumanPlayer::disablePlayer(){

	hasNotKilled = false;
	if(x != -1 && y != -1){
		gotoxy(x,y);
		cout << " ";
		x=-1;
		y=-1;
	}
}

int heaumanPlayer::returnDirection()const{
	if(direction == 'W' || direction == 'w')
		return 2;
	else if (direction == 'S' || direction == 's')
		return 3;
	else if (direction == 'A' || direction == 'a')
		return 1;
	else if (direction == 'D' || direction == 'd')
		return 0;

}

void heaumanPlayer::fierdWallBlowingArr(){
	wallBlowingArrows -= 1;
}
void heaumanPlayer::fierdWallPircingArr(){
	wallPircingArrows -= 1;

}
char heaumanPlayer::returnCharDirection()const{
	return direction;

}
