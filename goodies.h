#ifndef GOODIES_H
#define GOODIES_H
#include <iostream>
using namespace std;

# include "board.h"
#include <windows.h>

extern void gotoxy(int, int); // prototype
extern void clrscr(); // prototype

class goodies{

	char bomb;  
	char food;
	char quiver;
	HANDLE  hConsole; //system function for colors

public:
	goodies ();  //constractor
	//this functions are for the deployment of the goodies according to conditions
	void startGoodies (board* b,int* posX,int* posY ,int scoreboardX,int scoreboardY,int numOfPlayers); 
	bool getLegitPos  (int& x1,int& y1,board* b,int* posX,int* posY ,int scoreboardX,int scoreboardY,int numOfPlayers)const;
};


#endif