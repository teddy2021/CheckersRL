#include "board.hpp"
#include "piece.hpp"
#include "pmove.hpp"

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
		virtual pmove getMove(team t){return pmove(-1,-1,-1,-1);};

};

class randm: public algorithm{
	private:
		int randomSelection();
		int randomRange(int min, int max);
	public:
		randm(board *b): algorithm(b){ srand(time(0));};
		pmove getMove(team t) override;
};


