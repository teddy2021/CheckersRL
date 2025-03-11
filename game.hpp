#include "board.hpp"
#include "player.hpp"
#include "pmove.hpp"
#include "ai.hpp"

#include <curses.h>

enum end_state {P1_VIC, P2_VIC, QUIT, UNWINNABLE};


#pragma once
class game{
	private:
		board brd;

		WINDOW * b_win;
		WINDOW * i_win;

		player *p1;
		player *p2;

		algorithm * a1;
		algorithm * a2;

		int curs_x;
		int curs_y;

		bool getInput();
		void selectMove(player *plr);
		void doMove(pmove m);
	public:
		game();
		~game();		
		void display();

		end_state getEndState();

		bool playTurn();
};
