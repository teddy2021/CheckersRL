#include "board.hpp"
#include "player.hpp"

#include "ai.hpp"

#include <curses.h>
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
		void doMove(int sx, int sy, int nx, int ny);
	public:
		game();
		~game();		
		void display();

		bool playTurn();
};
