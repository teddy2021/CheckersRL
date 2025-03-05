
#include "game.hpp"

int main(){
	game g;
	g.display();
	bool cont = true;
	while(cont){
		cont = g.playTurn();
	}
	return 0;
}
