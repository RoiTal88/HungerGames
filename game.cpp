#include <iostream>
using namespace std;
#include "game.h"
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <typeinfo.h>

game::game(char* fileName):b(fileName)
{
	b.printMap();
	startPlay();
	
	
}

void game::startPlay(){
	int  i,k;
	int tempVit;
	srand((unsigned)time(NULL));
	flag1= flag2 = false;
	iterationCounter = 0;
	



	//////////////////dont forget to releas the memory allocation
	
	//exporting the human player cords
	b.exportHumanPlayerCords(humanCordX , humanCordY);
	b.exportNumOfPlayers(numOfPlayers);



	//the container of players
	allocateMemoryForPlayers();
	playerPosX = new int[numOfPlayers];
	playerPosY = new int[numOfPlayers];
	playerDirection = new int[numOfPlayers];
	playerVitality = new int [numOfPlayers];
	playersArrow = new arrow**[numOfPlayers];
	numOfArrowsForPlayer = new int[numOfPlayers];

	for(i=0;i<numOfPlayers;i++)
		numOfArrowsForPlayer[i] = 0;

	for(i=0;i<numOfPlayers;i++){
		playersArrow[i] = new arrow*[MAX_ARR_SIZE];
	}
	

	//initializ arrows
	for(i=0;i<numOfPlayers;i++){
		for(k=0;k<MAX_ARR_SIZE;k += 4){
			playersArrow[i][k]= new arrow;
			playersArrow[i][k]->putSymbole(248);
			playersArrow[i][k+1]= new arrow  ;
			playersArrow[i][k+1]->putSymbole(248);
			playersArrow[i][k+2]= new wallBlowingArr;
			playersArrow[i][k+2]->putSymbole(4);
			playersArrow[i][k+3]= new wallPircingArr;
			playersArrow[i][k+3]->putSymbole(15);
		}
	}



	///


	for(i=0;i<numOfPlayers;i++){
		if(typeid(*plArr[i]) == typeid(player))
			b.returnXYp(playerPosX[i],playerPosY[i],i);
	}

	if(humanCordX != UN_INITILAIZE_PLAYER && humanCordY != UN_INITILAIZE_PLAYER ){
		b.exportHumanPlayerCords(playerPosX[numOfPlayers-1],playerPosY[numOfPlayers-1]);
		plArr[numOfPlayers-1]->setNewPos(humanCordX,humanCordY);
		plArr[numOfPlayers-1]->turnPlayerActive();
		plArr[numOfPlayers-1]->putSymbol(numOfPlayers - 1);
		plArr[numOfPlayers-1]->drawPlayer();
	}

	for(i=0;i<numOfPlayers;i++){
		flag1 = b.checkIfLegit(playerPosX[i],playerPosY[i]);
		if(flag1 == false){
			playerPosX[i]= playerPosY[i] = UN_INITILAIZE_PLAYER;
		}
	}



	//set and chack the computerPlayers
	for (i=0 ; i<numOfPlayers; i++){
		
		flag1 = false;
		plArr[i]->putSymbol(i);
		if(playerPosX[i] == UN_INITILAIZE_PLAYER  && playerPosY[i] == UN_INITILAIZE_PLAYER){
			while(flag1 == false){
				if(b.checkIfLegit(playerPosX[i],playerPosY[i]) == true){
					plArr[i]->drawPlayer();
					flag1 = true;
					break;
				}
				else{
					plArr[i]->changPos();
					plArr[i]->returnPos(playerPosX[i],playerPosY[i]);
				}
			}
		}
		else {
			plArr[i]->setNewPos(playerPosX[i],playerPosY[i]);
			plArr[i]->drawPlayer();
		}
		
	}
	


	//saving the palyers cords
	for(i=0;i<numOfPlayers;i++){
		plArr[i]->returnPos(playerPosX[i],playerPosY[i]);
	}

	
	//writing the state box
	b.returnScoreBoardCord(scoreBoardCordX,scoreBoardCordY);
	plArr[0]->writeStateBox(scoreBoardCordX+1,scoreBoardCordY+1);

	writePlayerState(plArr,numOfPlayers);



	
	while(atLeastOneAlive(plArr,numOfPlayers) && !flag2){
		
		
		listenToKBHIT();

		if(iterationCounter % 2 == 0){
			for(i=0;i<numOfPlayers;i++){
				if(plArr[i]->chackIfAlive()){
					plArr[i]->movePlayer(temp2,&b);
					collitionChack(plArr,i,numOfPlayers);
				}
			
			}
			chackIfPlayerKilled(plArr);
			writePlayerState(plArr,numOfPlayers);
		}

		listenToKBHIT();



		for(i=0;i<numOfPlayers;i++){
			plArr[i]->returnPos(playerPosX[i],playerPosY[i]);
			playerDirection[i] = plArr[i]->returnDirection();
		}
		
		for(i=0;i<numOfPlayers;i++){
			chackHitByArrows(plArr,playersArrow,numOfPlayers,i);
		}

		
		if(iterationCounter %6 == 0){
			for(i=0;i<numOfPlayers;i++){
				if(typeid(*plArr[i]) == typeid(player))
					shootArrow(i);
			}
		}

		for(i=0;i<numOfPlayers;i++){
			if(typeid(*plArr[i]) == typeid(heaumanPlayer)){
				k = plArr[i]->returnDirection();
				if(k == RIGHT || k == LEFT || k== UP || k== DOWN)
					shootArrow(i);
			}
		}


		listenToKBHIT();

		for(i=0;i<numOfPlayers;i++){
			for(k=0;k<MAX_ARR_SIZE;k++)
				if(playersArrow[i][k]->returnActivity()){
					playersArrow[i][k]->movementByDirection(b);
				
				}
		
		}



		for(i=0;i<numOfPlayers;i++){
			chackHitByArrows(plArr,playersArrow,numOfPlayers,i);
		}


		if(iterationCounter%2 == 0){
			for(i=0;i<numOfPlayers;i++)
				plArr[i]->returnPos(playerPosX[i],playerPosY[i]);
			g.startGoodies(&b,playerPosX,playerPosY,scoreBoardCordX,scoreBoardCordY,numOfPlayers);
		}

		
		iterationCounter++;
		Sleep(50);
		if(temp == 27 ) {
			clrscr();
			cout << "Are you want to exit the game  Y/N ?:  ";
			cin>> temp;
			if (temp == 'y'|| temp == 'Y')
				flag2 = true;
			

			else{
				clrscr();
				b.printMap();
				plArr[0]->writeStateBox(scoreBoardCordX+1,scoreBoardCordY+1);
				
				}
			
			} 

		listenToKBHIT();
	
	
	}

	clrscr();
	if (flag2)
		cout <<"You Exit The Game BYE BYE"<<endl;
	else{
		cout <<  "the winner is player: " << chackWhoIsTheWinner(plArr,numOfPlayers) << endl;

	}
	
	freeAll();


}

void game::collitionChack(basePlayer** pl, int currPlayer,int numOfPLayers)const{
	int i;
	int vital1, vital2;
	int posXP1, posXP2;
	int posYP1, posYP2;
	pl[currPlayer]->returnPos(posXP1,posYP1);
	pl[currPlayer]->returnVitality(vital1);
	for(i=0;i<numOfPLayers;i++){
		pl[i]->returnPos(posXP2 ,posYP2);
		pl[i]->returnVitality(vital2);
		if(i != currPlayer&& (posXP1 == posXP2 && posYP1 == posYP2)){

			if(vital1 == vital2){
				pl[currPlayer]->hitBycollision3();
				pl[i]->hitBycollision3();
			}
			else if(vital1 > vital2){
				pl[currPlayer]->hitBycollision1();
				pl[i]->hitBycollision2();
			}
			else if(vital1 < vital2){
				pl[currPlayer]->hitBycollision2();
				pl[i]->hitBycollision1();			
			}
		}
	}

}
		


void game::arrowCollitionChack(arrow** arr,player* pl,int numOfPlayers,int* firedArrows)const {
	int i,k;
	int plCordX, plCordY;
	int arrCordX, arrCordY;

	for(i=0;i<numOfPlayers;i++){
		pl[i].returnPos(plCordX,plCordY);
		for(k=0;k<firedArrows[i];k++){
			arr[i][k].returnArrosPos(arrCordX, arrCordY);
			if(arrCordX == plCordX && arrCordY ==  plCordY)
				pl[i].hitByArrow();
		}

	
	}


}

bool game::atLeastOneAlive(basePlayer** pl, int numOfPlayers) const{
	int i,sum;
	int vital;

	sum = 0;
	for(i=0;i<numOfPlayers;i++){
		pl[i]->returnVitality(vital);
		if(vital > 0)
			sum++;
	
	}
	if(sum > 1)
		return true;
	else
		return false;
	

}

void game::chackHitByArrows(basePlayer** pl,arrow*** playersArrow,int numOfPlayers, int playerNumber)const{
	int k,j;
	int playerXPos,playerYPos;
	int arrowXPos,arrowYPos;


	pl[playerNumber]->returnPos(playerXPos,playerYPos);
	for(j=0;j<numOfPlayers;j++){
		for(k=0;k<MAX_ARR_SIZE;k++){
		
			playersArrow[j][k]->returnArrosPos(arrowXPos,arrowYPos);
			if(arrowXPos == playerXPos && arrowYPos == playerYPos && playersArrow[j][k]->returnActivity() ){
				pl[playerNumber]->hitByArrow();
				playersArrow[j][k]->disAbleActivity();
				
				pl[playerNumber]->drawPlayer();
			
			}
			
		}
	}
}

void game::chackIfPlayerKilled(basePlayer** arr) const {
	int i,tempVit;

	for(i=0;i<numOfPlayers;i++){
		arr[i]->returnVitality(tempVit);
		if(tempVit <= 0 && arr[i]->chackIfAlive())
			arr[i]->disablePlayer();
	}

}

char game::chackWhoIsTheWinner(basePlayer** arr,int numOfPlayers)const{
	int i,vit;
	for(i=0;i<numOfPlayers;i++){
		arr[i]->returnVitality(vit);
		if(vit > 0)
			return arr[i]->retuenSymbol();
		
	}

}

void game::writePlayerState(basePlayer ** pl,int numOfPlayers)const{
	int i,k;
	int vit,arrows1,arrows2,arrows3;
	char symbol;
	
	for(i=0;i<numOfPlayers;i++){
		pl[i]->returnVitality(vit);
		pl[i]->returnNumOfArrows(arrows1,arrows2,arrows3);
		symbol = pl[i]->retuenSymbol();
		

		gotoxy(scoreBoardCordX +1,scoreBoardCordY+2+i);
		
		for(k=0;k<10;k++){
			cout << " ";
		}
		if(vit <= 0){
			gotoxy(scoreBoardCordX + 1,scoreBoardCordY + 2 +i);
			cout<<"--KILLED--";
		}
		else{
			gotoxy(scoreBoardCordX + 1,scoreBoardCordY + 2 +i);
			cout <<symbol << " " << vit  <<" " <<arrows3<<arrows2<<arrows1;
		}
	}
}

void game::allocateMemoryForPlayers(){
	bool isInGame;

	if(humanCordX != UN_INITILAIZE_PLAYER && humanCordY != UN_INITILAIZE_PLAYER )
		isInGame = true;
	else 
		isInGame = false;

	if (numOfPlayers == 0 && isInGame == false){//if there is not any players on the map so the game will allocat 2 computer players
		plArr = new basePlayer*[2];
		plArr[0] = new player;
		plArr[1] = new player;
		numOfPlayers = 2;
	}
	else if(numOfPlayers == 2 && isInGame == true){
		plArr = new basePlayer*[2];
		plArr[0] = new player;
		plArr[1] = new heaumanPlayer;
		numOfPlayers = 2;
	}
	else if(numOfPlayers == 1 && isInGame == false){ 
		plArr = new basePlayer*[2];
		plArr[0] = new player;
		plArr[1] = new player;
		numOfPlayers = 2;
	}
	else if(numOfPlayers == 1 && isInGame == true){
		plArr = new basePlayer*[2];
		plArr[0] = new player;
		plArr[1] = new heaumanPlayer;
		numOfPlayers = 2;	
	
	}
	else if(numOfPlayers == 2 && isInGame == false){
		plArr = new basePlayer*[2];
		plArr[0] = new player;
		plArr[1] = new player;
		numOfPlayers = 2;
	
	}
	else if(numOfPlayers == 3 && isInGame == true ){
		plArr = new basePlayer*[3];
		plArr[0] = new player;
		plArr[1] = new player;
		plArr[2] = new heaumanPlayer;
		numOfPlayers = 3;
	}
}
void game::add_4_ArrowsToPlayer(int numOfPlayer) {
	int i;
	i=numOfPlayer;

	playersArrow[i][numOfArrowsForPlayer[i]]= new arrow ;
	playersArrow[i][numOfArrowsForPlayer[i]+1]= new arrow  ;
	playersArrow[i][numOfArrowsForPlayer[i]+2]= new wallBlowingArr;
	playersArrow[i][numOfArrowsForPlayer[i]+3]= new wallPircingArr;

}

void game::shootArrow(int i) {
	bool isOKToShoot,isOKToShoot2;
	char chOnBoard;
	int choosenArrow;


	choosenArrow = rand()%3;
	isOKToShoot = false;
	isOKToShoot2 = false;
	int j;

	for(j=0;j<numOfPlayers;j++){
		if(j != i){
			if((abs(playerPosX[i] - playerPosX[j]) <= 1 || abs(playerPosY[i] - playerPosY[j] )<= 1)){
				if(playerPosX[i] > EDGE_OF_BOARD_MIN_X && playerPosX[i] < EDGE_OF_BOARD_MAX_X && playerPosY[i] > EDGE_OF_BOARD_MIN_Y && playerPosY[i] < EDGE_OF_BOARD_MAX_Y)
					isOKToShoot = true;
				
			}
		}
	
	}

	if(playerPosX[i] > EDGE_OF_BOARD_MIN_X && playerPosX[i] < EDGE_OF_BOARD_MAX_X && playerPosY[i] > EDGE_OF_BOARD_MIN_Y && playerPosY[i] < EDGE_OF_BOARD_MAX_Y)
		isOKToShoot2 = true;
	
	chOnBoard = b.returnCharWithDirection(playerPosX[i],playerPosY[i],playerDirection[i]);

	if(chOnBoard == 'o' || chOnBoard == 'O'){
		return;
		temp = 0;
	}

	if(isOKToShoot || (typeid(*plArr[i]) == typeid(heaumanPlayer) && isOKToShoot2 == true )){
		int arrowsNum ,wallBlowingArrowNum, wallPircingArrowNum;

		plArr[i]->returnNumOfArrows(arrowsNum ,wallBlowingArrowNum, wallPircingArrowNum);
 //0-regular arrow 1-wall blowing arrow 2-wallpircing arrow

		if(((choosenArrow == 0 && typeid(*plArr[i]) == typeid(player)) || ((temp1 == 'p' || temp1 == 'P') && typeid(*plArr[i]) == typeid(heaumanPlayer) )) && arrowsNum > 0 ){
			for(k=0;k<MAX_ARR_SIZE;k++){
				if(typeid(*playersArrow[i][k]) == typeid(arrow)&& playersArrow[i][k]->isFierdOnce() == false){
						playersArrow[i][k]->getDirection(playerDirection[i]);
						playersArrow[i][k]->setInitialPos(playerPosX[i], playerPosY[i] ,playerDirection[i]);
						plArr[i]->firedArrow();
						if(chOnBoard == ' ')
							playersArrow[i][k]->printArrow();
						break;
				
							
				}
							
			}
		}
		else if	((((choosenArrow == 1 && typeid(*plArr[i]) == typeid(player)) || ((temp1 == 'o' || temp1 == 'O') && typeid(*plArr[i]) == typeid(heaumanPlayer) ))) && wallBlowingArrowNum > 0 ){
			for(k=0;k<MAX_ARR_SIZE;k++){
				if(typeid(*playersArrow[i][k]) == typeid(wallBlowingArr) && playersArrow[i][k]->isFierdOnce() == false){
				
						playersArrow[i][k]->getDirection(playerDirection[i]);
						playersArrow[i][k]->setInitialPos(playerPosX[i], playerPosY[i] ,playerDirection[i]);
						plArr[i]->fierdWallBlowingArr();
						if(chOnBoard == ' ')
							playersArrow[i][k]->printArrow();
						break;						
				
							
				}				
			}
		}

		else if	((((choosenArrow == 2 && typeid(*plArr[i]) == typeid(player)) || ((temp1 == 'i' || temp1 == 'I') && typeid(*plArr[i]) == typeid(heaumanPlayer) ))) && wallPircingArrowNum > 0 ){
			for(k=0;k<MAX_ARR_SIZE;k++){
				if(typeid(*playersArrow[i][k]) == typeid(wallPircingArr) && playersArrow[i][k]->isFierdOnce() == false  ){
						playersArrow[i][k]->getDirection(playerDirection[i]);
						playersArrow[i][k]->setInitialPos(playerPosX[i], playerPosY[i] ,playerDirection[i]);
						plArr[i]->fierdWallPircingArr();
						if(chOnBoard == ' ')
							playersArrow[i][k]->printArrow();
						break;						
				
							
				}				
			}
		}				
	

	}	
		
	

	temp1 = 0;

}

void game::listenToKBHIT(){
	if(kbhit()){
		temp = _getch();
		if(temp == 'I' || temp == 'i' || temp == 'o' || temp == 'O'|| temp == 'p' || temp == 'P')
			temp1= temp;
		else
			temp2 = temp;
	}

}


void game::freeAll(){
	int i,k;

	for (i=0 ; i<numOfPlayers;i++)
		 delete plArr[i];
	delete plArr;

	for(i=0;i<numOfPlayers;i++){
		for(k=0;k<MAX_ARR_SIZE;k++)
			delete playersArrow[i][k];
		delete playersArrow[i];
	}
	delete playersArrow;
	delete playerPosX ;
	delete playerPosY ;
	delete playerDirection ;
	delete playerVitality ;
	delete numOfArrowsForPlayer ;


}
