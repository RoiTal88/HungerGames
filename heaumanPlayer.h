#ifndef HEAUMANPLAYER_H
#define HEAUMANPLAYER_H

#include "basePlayer.h"
#include "board.h"


extern void gotoxy(int, int); // prototype
extern void clrscr(); // prototype

class heaumanPlayer: public basePlayer{
private:
	int type;
	bool isInGame;
	int direction;
	int moveCounter;
	int vitality;
	int arrows;
	int wallBlowingArrows;
	int wallPircingArrows;
	int x,y;
	char symbol;
	bool hasNotKilled;
	

public:
	heaumanPlayer();
	void turnPlayerActive();//
	void movePlayer(char dir,board* b);//
	void removePlayer (int x1, int y1)const;
	void drawPlayer()const;
	void hitByArrow();//
	void hitByBomb();//
	void hitBycollision1();//
	void hitBycollision2();//
	void hitBycollision3();//
	void stepedOnFood();//
	void stepedOnQuiver();//
	void firedArrow();//
	void returnPos(int &x1, int &y1)const;
	void changPos();//
	void setNewPos(int x1 , int y1);//
	void writePlayerStatus (int ScoreBoardXcord , int ScoreBoardYcord)const;
	void writeStateBox(int ScoreBoardXcord,int ScoreBoardYcord)const;
	void returnVitality(int& vital)const;
	void returnNumOfArrows(int& x,int& y ,int& z)const;
	char retuenSymbol()const;
	void putSymbol(int i);//
	void removeAllArrows();//
	bool chackIfAlive()const;
	void disablePlayer();//
	int returnDirection()const;
	char returnCharDirection()const;
	void fierdWallBlowingArr();//
	void fierdWallPircingArr();//
};
#endif