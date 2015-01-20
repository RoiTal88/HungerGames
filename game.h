#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
#include "arrow.h"
#include "goodies.h"
#include "heaumanPlayer.h"
#include "basePlayer.h"
#include "wallBlowingArrow.h"
#include "wallPircingArrow.h"


#define EDGE_OF_BOARD_MIN_X 0
#define EDGE_OF_BOARD_MAX_X 78
#define EDGE_OF_BOARD_MAX_Y 23
#define EDGE_OF_BOARD_MIN_Y  0


class game {
private:
	board b;
	basePlayer** plArr;
	int playerFiredArrowNum[NUM_OF_PLAYERS];
	int *playerPosX, *playerPosY;
	int* playerDirection;
	int* playerVitality;
	arrow*** playersArrow;
	int* numOfArrowsForPlayer;
	int humanCordX,humanCordY;
	char humanDirection;
	int numOfPlayers;
	int playerX,playerY;
	char boardMap[MAX_HIGHET][MAX_WIDTH];
	bool flag1,flag2;
	char chOnBoard;
	int xCord , yCord;
	int scoreBoardCordX, scoreBoardCordY;
	int i,k,iterationCounter;
	int arrowCordX, arrowCordY;
	char temp,temp1,temp2;
	goodies g;
	
	

public:

	game (char*);
	void startPlay();//
	void collitionChack(basePlayer** pl,int currPlayer,int numOfPlayers) const;
	void arrowCollitionChack(arrow** arr,player* pl,int numOfPlayers,int* fierdArrows)const;
	bool atLeastOneAlive(basePlayer** pl,int numOfPlayers) const;
	void chackHitByArrows(basePlayer** pl,arrow*** playersArrow,int numOfPlayers, int playerNumber)const;
	void chackIfPlayerKilled(basePlayer** arr)const ;
	char chackWhoIsTheWinner(basePlayer** arr,int numOfPlayers)const;
	void writePlayerState(basePlayer ** pl,int numOfPlayers)const ;
	void allocateMemoryForPlayers();//
	void add_4_ArrowsToPlayer(int numOfPlayer); // ;
	void shootArrow(int i) ;//
	void freeAll();
	void listenToKBHIT();
	
	
};

#endif