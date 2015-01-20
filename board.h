#ifndef BOARD_H
#define BOARD_H

# include <iostream>
using namespace std;
#include <windows.h>


enum utility {NUM_OF_PLAYERS=2 ,MAX_HIGHET=79, MAX_WIDTH=24, UN_INITILAIZE_PLAYER= -1, MAX_ARR_SIZE=200,UP=2, DOWN=3, LEFT=1, RIGHT=0};

class board {

	
	char map[MAX_WIDTH][MAX_HIGHET]; //the map witch is holding the map itself and all the information on walls scoreboard and goodies
	char copyMap[MAX_WIDTH][MAX_HIGHET]; //helper to the map
	int playerPosX[NUM_OF_PLAYERS], playerPosY[NUM_OF_PLAYERS];
	int scoreBoardX;	//the position of the score board
	int scoreBoardY;	//the position of the score board
	HANDLE  hConsole;   //system function for colors
	int humanPlayerX , humanPlayerY;
	bool thereIsHeauman;
	int numOfComPlayers;
	int numOfPlayers;

public:
	
	board(char* fileName);  //constractor
	void printMap ();//  //printing the map 
	bool checkIfLegit(int x1, int y1) const; //chack if the position (x1,y1) is leagal according to the conditions (see definition)
	char returnCharOnBoard(int x1, int y1);	//returnig the char in position(x1,y1) on the board
	void printScoreboard(int x, int y);	//printing the score board acoording to positions (x,y) - left top corner
	void returnXYp(int& x1,int& y1,int playerNum);//	//return the position of player 1
	void returnScoreBoardCord(int& x1, int& y1);//	//return the posision of the score board
	char returnCharWithDirection(int x1,int y1, int direction);//	//return the next char according to direction
	void writeChar(int x1,int y1) const;	//wirte char on the screen
	void getGoodiesInMap(int x1 ,int y1,char ch); //wirte the goodies on the map (matrix)
	void writeCharToMatrix(int x1, int x2, char ch);	// // write char to the matrix
	void exportHumanPlayerCords(int& x1, int&y1) const;
	void exportNumOfPlayers(int& num)const;

};

#endif

