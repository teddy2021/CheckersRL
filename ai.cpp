#include "ai.hpp"

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


vector<int> randm::getMove(team t){
	vector<vector<int>> moves = brd->getValidMoves(t);
	if(moves.size() < 1){
		return vector<int>();
	}
	vector<int> move = moves[randomRange(0, moves.size() - 1)];
	if(move.size() > 4){
		int sets = move.size() / 4;
		int choice = rand() % sets;
		vector<int> temp(
				move.begin() + (choice * 4),
				move.begin() + (4+(choice * 4))	
				);
		move = temp;
	}
	return move;
}



