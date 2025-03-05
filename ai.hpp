#include "board.hpp"
#include "piece.hpp"
#include <vector>
using std::vector;

#include <stdlib.h>
#include <time.h>

#pragma once
class algorithm{
	protected:
		board * brd;
	public:
		algorithm(board *b): brd(b){};
		virtual vector<int> getMove(team t){return vector<int>();};

};

class randm: public algorithm{
	private:
		int randomSelection();
		int randomRange(int min, int max);
	public:
		randm(board *b): algorithm(b){ srand(time(0));};
		vector<int> getMove(team t) override;
};


