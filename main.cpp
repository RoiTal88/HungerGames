#include <iostream>
using namespace std;
#include "gotoxy.h"
# include "game.h"

void main(int argc,char** argv){
	
	if (argv[1]== NULL){
		exit (1);
		cout<< "the text map is not legal";
	}
	else
	{
		game g(argv[1]);
	}
	
}