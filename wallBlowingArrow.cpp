#include "wallBlowingArrow.h"

wallBlowingArr::wallBlowingArr(){}

#define EDGE_OF_BOARD_MIN_X 0
#define EDGE_OF_BOARD_MAX_X 78
#define EDGE_OF_BOARD_MAX_Y 23
#define EDGE_OF_BOARD_MIN_Y  0

//movment by direction
void wallBlowingArr::movementByDirection(board& b){
	char tempCh;
	
	if(posX == EDGE_OF_BOARD_MIN_X || posX == EDGE_OF_BOARD_MAX_X || posY == EDGE_OF_BOARD_MIN_Y || posY == EDGE_OF_BOARD_MAX_Y){ // if the arrow is in the edge of the map
		tempCh = b.returnCharOnBoard(posX,posY);
		if(tempCh != 'F' && tempCh != 'B' && tempCh != 'Q'){
			gotoxy(posX,posY);
			cout <<" ";
			b.writeCharToMatrix(posX,posY,' ');
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
	tempCh = b.returnCharOnBoard(posX,posY);

	if(tempCh == 'o' || tempCh == 'O'){
		activity = false;
		return;
	}

	// if a wall has detected the arrow will deleted
	if(tempCh ==  'w' || tempCh ==  'W' || tempCh ==  'O' || tempCh ==  'o'){
		activity = false;
		gotoxy(posX,posY);
		cout<< " ";
		b.writeCharToMatrix(posX,posY,' ');
		return;
	}
	//movement form direction
	if (direction == 0){
		prevChar = tempCh = b.returnCharOnBoard(posX+1,posY);
		if(tempCh ==  'w' || tempCh ==  'W' || tempCh ==  'O' || tempCh ==  'o'){//if the next is a wall
			if(tempCh != 'o' && tempCh != 'O'){
				posX += 1;
				gotoxy(posX,posY);
				b.writeCharToMatrix(posX,posY,' ');
				cout<<" ";
			}
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
	
	else if(direction == 1){
		prevChar = tempCh = b.returnCharOnBoard(posX-1,posY);
		if(tempCh ==  'w' || tempCh ==  'W' || tempCh ==  'O' || tempCh ==  'o'){//if the next is a wall
			if(tempCh != 'o' && tempCh != 'O'){
				posX -= 1;
				gotoxy(posX,posY);
				b.writeCharToMatrix(posX,posY,' ');
				cout<<" ";
			}
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

	else if(direction == 2){
		prevChar = tempCh = b.returnCharOnBoard(posX,posY-1);
		if(tempCh ==  'w' || tempCh ==  'W' || tempCh ==  'O' || tempCh ==  'o'){//if the next is a wall
			if(tempCh != 'o' && tempCh != 'O'){
				posY -= 1;
				gotoxy(posX,posY);
				b.writeCharToMatrix(posX,posY,' ');
				cout<<" ";
			}
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

	else if(direction == 3){
		prevChar = tempCh = b.returnCharOnBoard(posX,posY+1);
		if(tempCh ==  'w' || tempCh ==  'W' || tempCh ==  'O' || tempCh ==  'o'){//if the next is a wall
			if(tempCh != 'o' && tempCh != 'O'){
				posY += 1;
				gotoxy(posX,posY);
				b.writeCharToMatrix(posX,posY,' ');
				cout<<" ";
			}
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




