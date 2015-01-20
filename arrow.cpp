#include <iostream>
using namespace std;
#include "arrow.h"


#define EDGE_OF_BOARD_MIN_X 0
#define EDGE_OF_BOARD_MAX_X 78
#define EDGE_OF_BOARD_MAX_Y 23
#define EDGE_OF_BOARD_MIN_Y 0


arrow::arrow(){  //constractr
	symbol = 248;
	activity = false;
	isFierdAllready = false;
}
//setting the initial position
void arrow::setInitialPos(int x , int y,int direction){  
	if(direction == RIGHT){
		posX = x + 1;
		posY = y;
	}
	else if(direction == LEFT){
		posX = x - 1;
		posY = y;
	}
	else if(direction == UP){
		posX = x;
		posY = y - 1;
	}
	else if(direction == DOWN){
		posX = x;
		posY = y + 1;
	
	}
}


//getting the direction of the player from the map and active the arrow
void arrow::getDirection(int direction1){
	direction = direction1;
	activity = true;
	isFierdAllready = true;
}

//movment by direction
void arrow::movementByDirection(board& b){
	char tempCh;
	
	tempCh = b.returnCharOnBoard(posX,posY);

	if(tempCh ==  'w' || tempCh ==  'W' || tempCh ==  'O' || tempCh ==  'o'){
		activity = false;
		return;
	}

	if(posX == EDGE_OF_BOARD_MIN_X || posX == EDGE_OF_BOARD_MAX_X || posY == EDGE_OF_BOARD_MIN_Y || posY == EDGE_OF_BOARD_MAX_Y){ // if the arrow is in the edge of the map
		
		if(tempCh != 'F' && tempCh != 'B' && tempCh != 'Q'){
			gotoxy(posX,posY);
			cout <<" ";
     	}
		activity = false;
		return;
	}

	//if the previous char position is on goodies so it wont erase it
	if(prevChar != 'B' && prevChar != 'Q' && prevChar != 'F' ){
		gotoxy(posX,posY);
		cout<<" ";
	}
	//return the currnt char on board
	


	
	//movement form direction
	if (direction == RIGHT){
		prevChar = tempCh = b.returnCharOnBoard(posX+1,posY);
		if(tempCh ==  'w' || tempCh ==  'W' || tempCh ==  'O' || tempCh ==  'o'){//if the next is a wall
			gotoxy(posX,posY);
			cout<<" ";
			activity = false;
		}
		else if(tempCh == 'F' || tempCh == 'B' || tempCh == 'Q'){  //if the next is a goodies so it wont write the arrow only set the new pos
			posX = posX +1;
			
		}
		else{
			gotoxy(posX+1,posY); //if on empty space
			cout <<symbol;
			posX = posX+1;
		}
	}
	
	else if(direction == LEFT){
		prevChar = tempCh = b.returnCharOnBoard(posX-1,posY);
		if(tempCh ==  'w' || tempCh ==  'W' || tempCh ==  'O' || tempCh ==  'o'){//if the next is a wall
			gotoxy(posX,posY);
			cout<<" ";
			activity = false;
		}
		else if(tempCh == 'F' || tempCh == 'B' || tempCh == 'Q'){//if the next is a goodies so it wont write the arrow only set the new pos
			posX = posX -1;
			
		}
		else{
			gotoxy(posX-1,posY);//if on empty space
			cout <<symbol;
			posX = posX-1;
		}
	}

	else if(direction == UP){
		prevChar = tempCh = b.returnCharOnBoard(posX,posY-1);
		if(tempCh ==  'w' || tempCh ==  'W' || tempCh ==  'O' || tempCh ==  'o'){//if the next is a wall
			gotoxy(posX,posY);
			cout<<" ";
			activity = false;
		}
		else if(tempCh == 'F' || tempCh == 'B' || tempCh == 'Q'){//if the next is a goodies so it wont write the arrow only set the new pos
			posY = posY -1;
			
		}
		else{
			gotoxy(posX,posY-1);//if on empty space
			cout <<symbol;
			posY = posY-1;
		}
	}

	else if(direction == DOWN){
		prevChar = tempCh = b.returnCharOnBoard(posX,posY+1);
		if(tempCh ==  'w' || tempCh ==  'W' || tempCh ==  'O' || tempCh ==  'o'){//if the next is a wall
			gotoxy(posX,posY);
			cout<<" ";
			activity = false;
		}
		else if(tempCh == 'F' || tempCh == 'B' || tempCh == 'Q'){//if the next is a goodies so it wont write the arrow only set the new pos
			posY = posY +1;
			
		}
		else{
			gotoxy(posX,posY+1);//if on empty space
			cout <<symbol;
			posY = posY +1;
		}
	}

	
}

bool arrow::returnActivity()const{ //returnig the activity
	return activity;
}

void arrow::disAbleActivity(){ // disabaling the arrow
	activity = false;
}

void arrow::returnArrosPos(int& x1, int& y1)const{ //return the currnt position of the arrrow
	x1 = posX;
	y1 = posY;

}

void arrow::removeLastPos(int direction)const{  //removing last position
		if (direction == RIGHT){
		gotoxy(posX,posY);
		cout <<' ';
		
	}
	else if(direction == LEFT){
		gotoxy(posX,posY);
		cout <<' ';
		
	}
	else if(direction == UP){
		gotoxy(posX,posY);
		cout <<' ';
		
	}
	else if(direction == DOWN){
		gotoxy(posX,posY);
		cout <<' ';
		
	}

}
void arrow::printArrow()const{
	gotoxy(posX,posY);
	cout <<symbol;

}

void arrow::turnArrowActive(){
	activity = true;
}

void arrow::putSymbole(char ch){
	symbol = ch;

}
bool arrow::isFierdOnce()const{
	return isFierdAllready;

}