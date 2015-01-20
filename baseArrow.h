#ifndef BASEARROW_H
#define BASEARROW_H


#include <iostream>
using namespace std;

#include "board.h"

extern void gotoxy(int, int); // prototype
extern void clrscr(); // prototype


class baseArrow{
private:

public:
	virtual void getDirection(int direction1)=0;   //function witch get the direction of the player in order to determin the direction of the arrow
	virtual void movementByDirection(board b)=0;	//this function is getting the board from the game and move the arrow according to the board
	virtual bool returnActivity()=0;	//function to return if the arrow is active
	virtual void disAbleActivity()=0;	//disabeling the activity of the arrow
	virtual void returnArrosPos(int& x1, int& y1)=0;	//return the arrow position
	virtual void setInitialPos(int x, int y,int direction)=0;	//setting to initial position acording to the player and direction
	virtual void removeLastPos(int direction)=0;	//removing the last position the the arrow was
	virtual void printArrow()=0; //printing the arrow position
	virtual void turnArrowActive()=0;
	virtual void putSymbole(char ch)=0;
	virtual bool isFierdOnce()=0;

};
#endif