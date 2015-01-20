#include "player.h"
#define MAX_ARROW_FOR_PLAYER 9
#define DOWN_EDGE 24
#define	UP_EDGE -1
#define	LEFT_EDGE -1
#define RIGHT_EDGE 79

player::player(){
	vitality= 1000;
	arrows= 2;
	wallBlowingArrows = 1;
	wallPircingArrows = 1;
	x = rand()%79;
	y = rand()%24;
	hasNotKilled = true;
	direction = rand()%4;
}

void player::turnPlayerActive(){
	hasNotKilled = true;
}

void player::movePlayer(char dir,board* b){
	char chOnBoard;
	int xCord,yCord;
	
	
	this->removePlayer(x,y);
	xCord = x;
	yCord = y;
	this->move(direction);
	chOnBoard = b->returnCharOnBoard(x,y);

	//case the next move is a wall
	if(chOnBoard ==  'w' || chOnBoard ==  'W' || chOnBoard ==  'O' || chOnBoard ==  'o' ){
		while(1){
			this->changeDirection();
						chOnBoard =b->returnCharWithDirection(xCord,yCord,direction);
			if(chOnBoard !=  'w' || chOnBoard !=  'W' || chOnBoard !=  'O' || chOnBoard !=  'o' ){
				if(chOnBoard == ' ' || chOnBoard == 'B' || chOnBoard == 'F' || chOnBoard == 'Q'){
					this->setNewPos(xCord,yCord);
					this->drawPlayer();
					if(chOnBoard == 'B')
						this->hitByBomb();
					else if(chOnBoard == 'F')
						this->stepedOnFood();
					else if(chOnBoard == 'Q')
						this->stepedOnQuiver();
					b->writeCharToMatrix(x,y,' ');
					break;
				}
			}
		}	
	}
	//case next move is bomb
	else if (chOnBoard == 'B'){
		this->hitByBomb();
		b->writeCharToMatrix(x,y,' ');
	}
	//case next move is food			
	else if(chOnBoard == 'F'){
		this->stepedOnFood();
		b->writeCharToMatrix(x,y,' ');
	}
	//case next move is quiver			
	else if(chOnBoard == 'Q'){
		this->stepedOnQuiver();
		b->writeCharToMatrix(x,y,' ');
	}
	else{
		/*
		#define DOWN_EDGE 23
		#define	UP_EDGE 0
		#define	LEFT_EDGE 0
		#define RIGHT_EDGE 78
		*/
		if(x == LEFT_EDGE || x == RIGHT_EDGE ||  y == UP_EDGE || y == DOWN_EDGE){
			if(x == LEFT_EDGE && direction == 1){
				chOnBoard = b->returnCharOnBoard(x + RIGHT_EDGE,y);
				if(chOnBoard != 'W' && chOnBoard != 'w' && chOnBoard != 'O' && chOnBoard != 'o'){
					this->setNewPos(x + RIGHT_EDGE,y);
					this->drawPlayer();
				}
			}
			else if(x == RIGHT_EDGE && direction == 0 ){
				chOnBoard = b->returnCharOnBoard(x - RIGHT_EDGE,y);
				if(chOnBoard != 'W' && chOnBoard != 'w' && chOnBoard != 'O' && chOnBoard != 'o'){
					this->setNewPos(x - RIGHT_EDGE,y);
					this->drawPlayer();
				}	
			}
			else if(y == DOWN_EDGE && direction == 3 ){
				chOnBoard = b->returnCharOnBoard(x ,y - DOWN_EDGE);
				if(chOnBoard != 'W' && chOnBoard != 'w' && chOnBoard != 'O' && chOnBoard != 'o'){
					this->setNewPos(x,y - DOWN_EDGE);
					this->drawPlayer();
				}
			}
			else if(y == UP_EDGE && direction == 2 ){
				chOnBoard = b->returnCharOnBoard(x ,y + DOWN_EDGE);
				if(chOnBoard != 'W' && chOnBoard != 'w' && chOnBoard != 'O' && chOnBoard != 'o'){
					this->setNewPos(x,y + DOWN_EDGE);
					this->drawPlayer();
				}
			}
			if((chOnBoard == 'W' || chOnBoard == 'w' || chOnBoard == 'O' || chOnBoard == 'o')){
				while(1){
					this->changeDirection();
								chOnBoard =b->returnCharWithDirection(xCord,yCord,direction);
					if(chOnBoard !=  'w' || chOnBoard !=  'W' || chOnBoard !=  'O' || chOnBoard !=  'o' ){
						if(chOnBoard == ' ' || chOnBoard == 'B' || chOnBoard == 'F' || chOnBoard == 'Q'){
							this->setNewPos(xCord,yCord);
							this->drawPlayer();
							if(chOnBoard == 'B')
								this->hitByBomb();
							else if(chOnBoard == 'F')
								this->stepedOnFood();
							else if(chOnBoard == 'Q')
								this->stepedOnQuiver();
							b->writeCharToMatrix(x,y,' ');
							break;
						}
					}
				}
			}
			if(chOnBoard == 'B')
				this->hitByBomb();
			else if(chOnBoard == 'F')
				this->stepedOnFood();
			else if(chOnBoard == 'Q')
				this ->stepedOnQuiver();
			b->writeCharToMatrix(x,y,' ');
			
		}
		else{
			this->drawPlayer();
		
		}
		
		
	}
	
	if(rand()%10 ==0)
		direction = rand()%4;
}



void player::changeDirection(){ 
	int direct;

	direct = direction;

	while (direct == direction){
		direct = rand()%4;
	
	}

	direction = direct;
}



void player::move(int direction){
	switch (direction){
	case 0:
		x++;
		break;
	case 1:
		x--;
		break;
	case 2:
		y--;
		break;
	case 3:
		y++;
		break;
	}


}

void player::drawPlayer ()const{
	gotoxy(x,y);
	cout << symbol;
}

void player::removePlayer(int x1,int y1)const{
	gotoxy(x,y);
	cout << ' ';

}

void player::hitByArrow (){
	vitality -= 500;

}

void player::hitByBomb (){     //the player has step by a bomb
	vitality -= 750;
}
void player::hitBycollision1(){ //when the player have the highest vitality
	vitality -= 10;
}
void player::hitBycollision2(){ //when the player have low vitality from other player
	vitality -= 200;
}
void player::hitBycollision3(){ //when the players vitality are the same level
	vitality -= 50;
}
void player::stepedOnFood(){    //when steping on food
	vitality += 200;
}
void player::stepedOnQuiver(){  //when stepping on arrow quiver
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

void player::firedArrow(){
	arrows -= 1;
}



void player::returnPos(int &x1, int &y1)const{
	x1 =x ;
	y1 =y;

}


void player::changPos(){
	x= rand()%79;
	y= rand()%24;

}




char player::retuenSymbol()const{
	return symbol;

}





void player::writePlayerStatus(int ScoreBoardXcord , int ScoreBoardYcord)const{
	int i;
	for(i=0;i<10;i++){
		gotoxy(ScoreBoardXcord+i,ScoreBoardYcord);
		cout << " ";
	}
	gotoxy(ScoreBoardXcord,ScoreBoardYcord);
	cout <<symbol << " " << vitality  <<" " <<arrows;

}
void player::writeStateBox(int x1, int y1)const{
	gotoxy(x1,y1);
	cout<<"PL Lif Arr";
}

void player::returnVitality(int& vital)const{
	vital = vitality;
}

void player::returnNumOfArrows(int& x,int& y ,int& z)const{
	x = arrows;
	y = wallBlowingArrows;
	z = wallPircingArrows;
}

void player::putSymbol(int i){
	symbol = i + 'A';

}

void player::removeAllArrows(){
	arrows = 0;

}
bool player::chackIfAlive()const{
	return hasNotKilled;
}

void player::disablePlayer(){

	hasNotKilled = false;
	if(x != -1 && y != -1){
		gotoxy(x,y);
		cout << " ";
		x=-1;
		y=-1;
	}
}
void player::setNewPos(int x1, int y1){
	x=x1;
	y=y1;
}


int player::returnDirection()const{
	return direction;
}

void player::fierdWallBlowingArr(){
	wallBlowingArrows -= 1;
}
void player::fierdWallPircingArr(){
	wallPircingArrows -= 1;

}

char player::returnCharDirection()const{
	return direction;

}
