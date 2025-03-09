#include "game.hpp"
#include "player.hpp"
#include "pmove.hpp"
#include "ai.hpp"
#include <bits/stdc++.h>
#include <curses.h>
bool game::getInput(){
	int x = 0;
	int y = 0;
	getmaxyx(b_win, y, x);
	int ch;
	int ent = 0;

	int sx = -1;
	int sy = -1;
	int ex = -1;
	int ey = -1;

	WINDOW * s_win = newwin(5, 20, 23,0);
	while((ch = getch()) != ERR && ent < 2){
		switch(ch){
			case KEY_BACKSPACE:
				ent -= 1;
				sx = -1;
				sy = -1;
				ex = -1;
				ey = -1;
				break;
			case '\n':
			case KEY_ENTER:
				ent += 1;
				if(ent == 1){
					sx = curs_x;
					sy = 22 - curs_y + 1;
				}
				else if(ent == 2){
					ex = curs_x;
					ey = 22 - curs_y + 1;
				}
				break;
			case KEY_UP:
				curs_y -= 2;
				curs_y = std::max(curs_y, 1);
				wmove(stdscr, curs_y, curs_x);
				break;
			case KEY_DOWN:
				curs_y += 2;
				curs_y = std::min(curs_y, y - 7);
				wmove(stdscr, curs_y, curs_x);
				break;
			case KEY_LEFT:
				curs_x -= 4;
				curs_x = std::max(4, curs_x);
				wmove(stdscr, curs_y, curs_x);
				break;
			case KEY_RIGHT:
				curs_x += 4;
				curs_x = std::min(x-7, curs_x);
				wmove(stdscr, curs_y, curs_x);
				break;
			case 'Q':
			case 'q':
				return false;
			default:
				break;
		}
		wmove(s_win, 0, 0);
		wprintw(s_win, "ent: %i\nsx: %i\nsy: %i\nex: %i\ney: %i\n", ent, sx/4 - 1, sy/2-4, ex/4 - 1, ey/2-4);
		wrefresh(s_win);
		display();
	}
	sx /= 4;
	sx -= 1;
	
	sy /= 2;
	sy -= 4;
	
	ex /= 4;
	ex -= 1;
	
	ey /= 2;
	ey -= 4;

	pmove m(sx, sy, ex, ey);
	doMove(m);
	display();
	return true;
}

void game::doMove(pmove m){
	pair<int> start = m.getStart();
	pair<int> end = m.getEnd();
	int sx = start.x;
	int sy = start.y;
	int nx = end.x;
	int ny = end.y;
	if(std::abs(nx-sx) > 1 && std::abs(ny-sy) > 1){
		brd.jumpPiece(sx, sy, nx, ny);
	}
	else{  
		brd.movePiece(sx,sy,nx,ny);
	}
}

void game::display(){
	wmove(b_win, 0, 0);
	brd.showBoard(b_win);
	wrefresh(b_win);

	wmove(i_win, 0,0);
	wprintw(i_win, "cx: %i\ncy: %i\n", curs_x, 22 - curs_y);
	wrefresh(i_win);
	
	wmove(b_win, curs_y, curs_x);

	refresh();
}

bool game::playTurn(){
	bool res = true;
	switch(p1->getType()){
		case human:
			res = getInput();
			if(res == false){
				return res;
			}
			break;
		case computer:
			selectMove(p1);
			break;
		default:
			break;
	}

	switch(p2->getType()){
		case human:
			res = getInput();
			if(res == false){
				return res;
			}
			break;
		case computer:
			selectMove(p2);
			break;
		default:
			break;
	}
	display();
	return res;
}

void game::selectMove(player *plr){
	pmove m = plr->selectMove();
	pair<int> start = m.getStart();
	if(start.x == -1){
		return;
	}
	doMove(m);
}

game::game(): brd(), curs_x(4), curs_y(1) {
	p1 = new player();
	a1 = nullptr;
	a2 = new randm(&brd);
	p2 = new ai<algorithm>(red, a2);
	initscr();
	noecho();
	cbreak();
	b_win = newwin(22, 39, 0, 0);
	i_win = newwin(6, 9, 0, 40);
	keypad(stdscr, TRUE);
}


game::~game(){
	if(p1 != nullptr){  
		delete p1;
	}
	if(p2 != nullptr){  
		delete p2;
	}
	if(a1 != nullptr){  
		delete a1;
	}		
	if(a2 != nullptr){  
		delete a2;
	}
	endwin();
}



