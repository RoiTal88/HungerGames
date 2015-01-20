#ifndef PLAYER_H
#define PLAYER_H


#include "basePlayer.h"
#include "board.h"

extern void gotoxy(int, int); // prototype
extern void clrscr(); // prototype

class player : public basePlayer {
private:
	int vitality;
	int arrows;
	int wallBlowingArrows;
	int wallPircingArrows;
	int x,y;
	char symbol;
	bool hasNotKilled;	
	int direction;
	

public:
	player();
	void turnPlayerActive();
	void movePlayer(char dir ,board* b);//
	void removePlayer (int x1, int y1) const;
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
	void move(int direction);//
	void changeDirection();//
	char returnCharDirection()const;
	int returnDirection()const;
	void fierdWallBlowingArr();//
	void fierdWallPircingArr();//
};

#endif