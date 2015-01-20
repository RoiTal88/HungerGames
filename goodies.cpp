# include "goodies.h"



goodies :: goodies (){ //consractor

	bomb= 'B';
	food= 'F';
	quiver= 'Q';
}


void goodies ::startGoodies (board* b,int* posX,int* posY,int scoreboardX,int scoreboardY,int numOfPlayers) {
	int howManyGoodies,i, whatToPut;
	int x, y;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
		howManyGoodies= (rand()%2)+1;

		for (i=0; i<howManyGoodies; i++) // checks how many items to put on the board each interaction
		{
			whatToPut= rand()%100;

			if (whatToPut >= 0 && whatToPut <20) //the propobility of food
			{
				if(getLegitPos(x,y,b,posX,posY,scoreboardX,scoreboardY,numOfPlayers)){
				
					b->getGoodiesInMap (x,y,food);
					gotoxy(x,y);
					SetConsoleTextAttribute(hConsole, 14);
					cout << food;
					SetConsoleTextAttribute(hConsole, 15);
					//food
				}
			}
			else if (whatToPut >= 20 && whatToPut <30)  //the propobility of quiver
			{
				
				if(getLegitPos(x,y,b,posX,posY,scoreboardX,scoreboardY,numOfPlayers)){
					b->getGoodiesInMap (x,y,quiver);
					gotoxy(x,y);
					SetConsoleTextAttribute(hConsole, 2);
					cout << quiver;
					SetConsoleTextAttribute(hConsole, 15);
					//quiver
				}
			}

			else if (whatToPut >= 30 && whatToPut <35) //the propobility of bomb
			{
				if(getLegitPos(x,y,b,posX,posY,scoreboardX,scoreboardY,numOfPlayers)){
					b->getGoodiesInMap (x,y,bomb);
					gotoxy(x,y);
					SetConsoleTextAttribute(hConsole, 12);
					cout << bomb;
					SetConsoleTextAttribute(hConsole,15);
					//bomb
				}
			}

		}//for
		
	
}

bool goodies :: getLegitPos (int& x1,int &y1,board* b,int* posX,int* posY ,int scoreboardX,int scoreboardY,int numOfPlayers)const
{
	bool okInboard,notNearPlayer,notInScoreboard;
	int x,y,i;
	
	okInboard = notNearPlayer = notInScoreboard = false;
	x = rand()%79;
	y = rand()%24;
	
	if(!(okInboard && notNearPlayer && notInScoreboard)){ //chacks if the randum position is legit
		
		for(i=0;i<numOfPlayers;i++){
			okInboard = b->checkIfLegit(x,y);
			if(((x <= posX[i] - 2) ||(x >= posX[i] + 2)) && ((y <= posY[i] -2) || (y >= posY[i] + 2)))
				notNearPlayer = true;
			if(!(((y > scoreboardY) && (y < scoreboardY + 7)) && ((x > scoreboardX) && (x < scoreboardX + 12))))
				notInScoreboard = true;
		}


	

	
	
	if(okInboard && notNearPlayer && notInScoreboard){
		x1 = x;
		y1 = y;
		return true;
	}
	
	return false;
	}
}