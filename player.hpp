#include <vector>
using std::vector;

#include "piece.hpp"
#include "pmove.hpp"
#pragma once

enum p_type {human, computer};

class player{

	protected:
		team t;
		int score;
		p_type type;
	public:
		player(): t(black), score(0), type(human){};
		player(team tm, p_type pt): t(tm), score(0), type(pt){};
		
		void incrScore();

		team getTeam();

		p_type getType();

		int getScore();

		virtual pmove selectMove(){return pmove(0,0,0,0);};
};

template <typename al>
class ai: public player{

	private:
		al *algorithm;

	public:
		ai(team tm, al *algo): player(tm, computer), algorithm(algo){};

		pmove selectMove() override{
			return algorithm->getMove(t);
		};
};
