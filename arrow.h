#ifndef ARROW_H
#define ARROW_H

#include <iostream>
using namespace std;
#include "board.h"



extern void gotoxy(int, int); // prototype
extern void clrscr(); // prototype

class arrow{


protected:
	int direction;  //the direction
	int posX,posY;	//the position of the arrow
	bool activity;	//activity for telling if the the arrow if fired
	char symbol;	//the symbole of the arrow
	char temp;		
	char prevChar;
	bool isFierdAllready;
	
public:
	arrow(); //constractor

	virtual void getDirection(int direction1);  // //function witch get the direction of the player in order to determin the direction of the arrow
	virtual void movementByDirection(board& b);//	//this function is getting the board from the game and move the arrow according to the board
	virtual bool returnActivity() const;	//function to return if the arrow is active
	virtual void disAbleActivity();	// //disabeling the activity of the arrow
	virtual void returnArrosPos(int& x1, int& y1)const;	//return the arrow position
	virtual void setInitialPos(int x, int y,int direction);	// //setting to initial position acording to the player and direction
	virtual void removeLastPos(int direction)const ;	//removing the last position the the arrow was
	virtual void printArrow()const; //printing the arrow position
	virtual void turnArrowActive(); //
	virtual void putSymbole(char ch); //
	virtual bool isFierdOnce()const;
};

#endif