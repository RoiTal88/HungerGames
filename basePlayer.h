#ifndef BASEPLAYER_H
#define BASEPLAYER_H


#include <iostream>
using namespace std;
#include "board.h"
#include <conio.h>


class basePlayer{
private:
		
public:
	basePlayer();
	virtual void movePlayer(char dir ,board* b)=0;
	virtual void removePlayer (int x1, int y1)const=0;
	virtual void drawPlayer()const=0;
	virtual void hitByArrow()=0;
	virtual void hitByBomb()=0;
	virtual void hitBycollision1()=0;
	virtual void hitBycollision2()=0;
	virtual void hitBycollision3()=0;
	virtual void stepedOnFood()=0;
	virtual void stepedOnQuiver()=0;
	virtual void firedArrow()=0;
	virtual void returnPos(int &x1, int &y1)const=0;
	virtual void changPos()=0;
	virtual void setNewPos(int x1 , int y1)=0;
	virtual void writePlayerStatus (int ScoreBoardXcord , int ScoreBoardYcord)const=0;
	virtual void writeStateBox(int ScoreBoardXcord,int ScoreBoardYcord)const=0;
	virtual void returnVitality(int& vital)const=0;
	virtual void returnNumOfArrows(int& x,int& y ,int& z)const=0;
	virtual char retuenSymbol()const=0;
	virtual void putSymbol(int i)=0;
	virtual void removeAllArrows()=0;
	virtual bool chackIfAlive()const=0;
	virtual char returnCharDirection()const=0;
	virtual void disablePlayer()=0;
	virtual void turnPlayerActive()=0;
	virtual int returnDirection()const=0;
	virtual void fierdWallBlowingArr()=0;
	virtual void fierdWallPircingArr()=0;
	
};
#endif