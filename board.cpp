
#include "board.h"
#include <fstream>
extern void gotoxy(int, int); // prototype


board::board(char* fileName)  
{
	ifstream fp;
	char temp[80];
	int i,k,j;
	bool seenO= false;
	bool seenFirstPlayerPos= false;
	numOfComPlayers = 0;

	thereIsHeauman = false;
	fp.open(fileName,ios::in);
	for(i=0;i<NUM_OF_PLAYERS;i++){
		playerPosX[i] =  playerPosY[i] = UN_INITILAIZE_PLAYER;
	}

	
	i=0;
	j=0;
	while(i<25){
		fp.getline(temp,81); //reads the text file
		for(k=0;k<79;k++){
			if(temp[k] == 'o' || temp[k] == 'O'){ //gets the score board position
				if (seenO== false)
				{
					seenO= true;
					scoreBoardX= k;
					scoreBoardY= i;
					map[i][k] = temp[k];
				}
				else
				{
					map[i][k] =' ';
				}
			}
			else if(temp[k] == 'P' || temp[k] == 'p'){ //gets the first player position
				playerPosX[j] = k;
				playerPosY[j] = i;
				map[i][k] = temp[k];
				numOfComPlayers++;
				j++;
			}
			else if(temp[k] == 'H' || temp[k] == 'h'){
				humanPlayerX = k;
				humanPlayerY = i;
				thereIsHeauman = true;
			}
			else
				map[i][k] = temp[k];
		}
		i++;
	}
	if (thereIsHeauman == false){
		humanPlayerY =  humanPlayerX = UN_INITILAIZE_PLAYER;
	
	}

	for(i=0;i<24;i++){
		for(k=0;k<79;k++){
			if(map[i][k] == 'P' ||map[i][k] == 'p'|| map[i][k] == 'h' || map[i][k] == 'H' )
				map[i][k] = ' ';
		}
	}

	printScoreboard (scoreBoardY, scoreBoardX); //prints the score board

	fp.close(); 
}





void board::printMap (){
	char wall,scoreboardWall;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	wall = 219; //wall char
	scoreboardWall = 177; //score board char
	for (int indexRow=0; indexRow<24; indexRow++){
		for (int indexCol=0; indexCol<79; indexCol++)
			{
				if (map[indexRow][indexCol] == 'W'||map[indexRow][indexCol] == 'w')
				{
					SetConsoleTextAttribute(hConsole, 8);
					cout<< wall;
					SetConsoleTextAttribute(hConsole, 15);
				}
				else if(map[indexRow][indexCol] == 'o' || map[indexRow][indexCol] == 'O')
				{
					SetConsoleTextAttribute(hConsole, 8);
					cout << scoreboardWall;
					SetConsoleTextAttribute(hConsole, 15);
				}
				else if(map[indexRow][indexCol] == 'F'){
					SetConsoleTextAttribute(hConsole, 14);
					cout << map[indexRow][indexCol];
					SetConsoleTextAttribute(hConsole, 15);
				}
				else if(map[indexRow][indexCol] == 'B'){
					SetConsoleTextAttribute(hConsole, 12);
					cout << map[indexRow][indexCol];
					SetConsoleTextAttribute(hConsole,15);				
				}
				else if(map[indexRow][indexCol] == 'Q'){
					SetConsoleTextAttribute(hConsole, 2);
					cout << map[indexRow][indexCol];
					SetConsoleTextAttribute(hConsole, 15);				
				}
				else 
					cout << map[indexRow][indexCol];

			}
		cout<<endl;
}

}

bool board::checkIfLegit(int x1, int y1)const{
	if(x1 == UN_INITILAIZE_PLAYER && y1 == UN_INITILAIZE_PLAYER)
		return false;
	if(map[y1][x1] != 'w' && map[y1][x1] != 'W' && map[y1][x1] != 'o' && map[y1][x1] != 'O' ){
		if(!(((y1 > scoreBoardY) && (y1 < scoreBoardY + 7)) && ((x1 > scoreBoardX) && (x1 < scoreBoardX + 12))))
			return true;
		else
			return false;
	}
	else
		return false;	
}

char board::returnCharOnBoard(int x1, int y1){
	if(x1 == -1 || x1 == 79 || y1 == -1 || y1 == 24)
		return ' ';
	else
		return (char)map[y1][x1];
}


void board::printScoreboard (int y, int x){

	int i;
	
	

	if((thereIsHeauman == true && numOfComPlayers < 2) || (thereIsHeauman == false && numOfComPlayers <= 2))
		numOfPlayers=2;
	else if(thereIsHeauman == true && numOfComPlayers == 2)
		numOfPlayers=3;

	if (x>67 || y>17)
	{
		exit (1);
		cout <<"the text map is not legal- score Board location not legal";
	}
	else{
		for (i=0; i<12; i++){
			map[y][x+i]= 'O';
			map[y+numOfPlayers+2][x+i] = 'O';
		}
		for(i=0;i<numOfPlayers + 3;i++){ //the +2 if for the bounds of the scoreBoard
			map[y+i][x]= 'O';
			map[y+i][x+11]= 'O';
		}
	}

}

void board::returnXYp(int& x1,int& y1,int playerNum){

	
	x1 = playerPosX[playerNum];
	y1 = playerPosY[playerNum];
}



void board::returnScoreBoardCord(int &x1, int &y1){
	x1 = scoreBoardX;
	y1 = scoreBoardY;
}



char board::returnCharWithDirection(int x1,int y1,int direction){
	if(direction == RIGHT)
		return map[y1][x1+1];
	else if(direction == LEFT)
		return map[y1][x1-1];
	else if(direction == UP)
		return map[y1-1][x1];
	else if(direction == DOWN)
		return map[y1+1][x1];
}

void board::writeChar(int x1, int y1) const{
	gotoxy(x1,y1);
	cout << map[y1][x1];

}

void board::getGoodiesInMap(int x1 ,int y1,char ch){

	map[y1][x1] = ch;
}

void board::writeCharToMatrix(int x1, int y1,char ch){
	map[y1][x1] = ch;

}


void board::exportHumanPlayerCords(int& x1, int& y1)const{
	x1 = humanPlayerX;
	y1 = humanPlayerY;

}
void board::exportNumOfPlayers(int &num)const{
	num = numOfPlayers;
}



