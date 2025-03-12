
#include "ai.hpp"
#include "pmove.hpp"

#pragma once
class pruning: public algorithm{
	private:
		int depth;
		int (*score)(board);
		pmove eval(board b);
	public:
		pruning(int dpt, int (*score)(board));
		pmove getMove(team t) override;

};
