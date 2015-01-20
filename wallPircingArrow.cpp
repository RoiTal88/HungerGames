#include "wallPircingArrow.h"


wallPircingArr::wallPircingArr(){}
	
#define EDGE_OF_BOARD_MIN_X 0
#define EDGE_OF_BOARD_MAX_X 78
#define EDGE_OF_BOARD_MAX_Y 23
#define EDGE_OF_BOARD_MIN_Y  0


//movment by direction
void wallPircingArr::movementByDirection(board& b){
	char tempCh;
	
	tempCh = b.returnCharOnBoard(posX,posY);

	if(tempCh == 'o' || tempCh == 'O'){
		activity = false;
		return;
	}

	if(posX == EDGE_OF_BOARD_MIN_X || posX == EDGE_OF_BOARD_MAX_X || posY == EDGE_OF_BOARD_MIN_Y || posY == EDGE_OF_BOARD_MAX_Y){ // if the arrow is in the edge of the map
		
		if(tempCh != 'w' && tempCh != 'W' && tempCh != 'o' && tempCh != 'O' && tempCh != 'F' && tempCh != 'B' && tempCh != 'Q' ){
			gotoxy(posX,posY);
			cout <<" ";
		}
		activity = false;
		return;
	}

	if(tempCh == ' '){
		gotoxy(posX,posY);
		cout << ' ';
	}





	//movement form direction
	if (direction == 0){
		posX = posX+1;


	}
	
	else if(direction == 1){
		posX = posX -1;
	}

	else if(direction == 2){
		posY = posY-1;
	}

	else if(direction == 3){
		posY = posY+1;
	}


	tempCh = b.returnCharOnBoard(posX,posY);
	
	if (tempCh == ' '){
		gotoxy(posX,posY);
		cout << symbol;
	}

	tempCh = b.returnCharWithDirection(posX,posY,direction);
	if(tempCh == 'o' || tempCh == 'O'){
		activity = false;
		tempCh = b.returnCharOnBoard(posX,posY);
		if(tempCh == ' ')
			gotoxy(posX,posY);
			cout << ' ';
	}
	
}