#include "ai.hpp"
#include "pmove.hpp"

#include <vector>
using std::vector;

int randm::randomSelection(){
	return rand();
}


int randm::randomRange(int min, int max){
	if(min == max)
	{
		return min;
	}
	return min + (rand() % max);
}


pmove randm::getMove(team t){
	vector<pmove> moves = brd->getValidMoves(t);
	if(moves.size() < 1){
		return pmove(-1,-1,-1,-1);
	}
	pmove m = moves[randomRange(0, moves.size() - 1)];
	return m;
}



