#include "board.hpp"
#include "tree.hpp"
#include "piece.hpp"
#include "pmove.hpp"


#include <stdexcept>
#include <vector>
using std::vector;
#include <ncurses.h>

board::board(): pieces(){
	for(int i = 0; i < 8; i += 1){
		for(int j = 7 - (i%2); j > 4; j -= 2 ){
			pieces.insert( piece(7-i,j,red));
		}
		for(int j = i%2; j < 3; j += 2){
			pieces.insert( piece(i,j,black));
		}
	}
}

board::~board(){
	for(int i = 0; i < 8; i += 1){
		for(int j = 0; j < 8; j += 1){
			dNode<piece> * cur = pieces.getItem(i,j);
			if(cur != nullptr){
				pieces.remove(*cur->getValue());
			}
		}
	}
	prevStart.clear();
	prevEnd.clear();
}


bool board::occupied(piece p, int offset_x, int offset_y){
	int pos_x = p.primary() + offset_x;
	int pos_y = p.secondary() + offset_y;
	
	if(0 > pos_x || pos_x > 7 || 0 > pos_y || pos_y > 7){
		return true;
	}
	dNode<piece> *other = pieces.getItem(pos_x, pos_y);

	if(nullptr == other){
		return false;
	}
	return true;
}


bool board::opposing(piece p, int x, int y){
	dNode<piece> *pce = pieces.getItem(p.primary() + x, p.secondary() + y);
	if(pce == nullptr){
		return false;
	}
	piece other = pce->getValue();
	return p.getTeam() != other.getTeam();
}


bool board::inbounds(piece p, int x, int y){
	int pos_x = p.primary() + x;
	int pos_y = p.secondary() + y;

	return 0 <= pos_x && pos_x < 8 && 0 <= pos_y && pos_y < 8;
}


bool board::canMoveForwardLeft(piece p){
	int forward = (p.getTeam() == black) - (p.getTeam() == red);
	int left = (p.getTeam() == red) - (p.getTeam() == black);
	return !occupied(p, left,  forward) && inbounds(p, left, forward);
}


bool board::canMoveForwardRight(piece p){
	int forward = (p.getTeam() == black) - (p.getTeam() == red);
	int right = (p.getTeam() == black) - (p.getTeam() == red);
	return !occupied(p, right, forward) && inbounds(p, right, forward);
}


bool board::canMoveBackLeft(piece p){
	if(p.getType() != king){
		return false;
	}
	int back = (p.getTeam() == red) - (p.getTeam() == black);
	int left = (p.getTeam() == red) - (p.getTeam() == black);
	return !occupied(p, left, back) && inbounds(p, left, back);
}


bool board::canMoveBackRight(piece p){
	if(p.getType() != king){
		return false;
	}
	int back = (p.getTeam() == red) - (p.getTeam() == black);
	int right = (p.getTeam() == black) - (p.getTeam() == red);
	return !occupied(p, right, back) && inbounds(p, right, back);
}


bool board::canJumpForwardLeft(piece p){
	int forward = (p.getTeam() == black) - (p.getTeam() == red);
	int left = (p.getTeam() == red) - (p.getTeam() == black);
	return occupied(p, left,  forward) && 
			opposing(p, left, forward) &&
			!occupied(p, 2 * left, 2 * forward) &&
			inbounds(p, 2 * left, 2 * forward);
}


bool board::canJumpForwardRight(piece p){
	int forward = (p.getTeam() == black) - (p.getTeam() == red);
	int right = (p.getTeam() == black) - (p.getTeam() == red);
	return occupied(p, right, forward)&&
		opposing(p, right, forward) &&
		!occupied(p, right * 2, forward * 2) &&
		inbounds(p, right * 2, forward * 2);
}


bool board::canJumpBackLeft(piece p){
	int back = (p.getTeam() == red) - (p.getTeam() == black);
	int left = (p.getTeam() == red) - (p.getTeam() == black);
	return occupied(p, left, back)&&
		opposing(p, left, back) &&
		inbounds(p, left * 2, back * 2) &&
		!occupied(p, left * 2, back * 2);
}


bool board::canJumpBackRight(piece p){
	int back = (p.getTeam() == red) - (p.getTeam() == black);
	int right = (p.getTeam() == black) - (p.getTeam() == red);
	return occupied(p, right, back)&&
		opposing(p, right, back) &&
		inbounds(p, right * 2, back * 2) &&
		!occupied(p, right * 2, back * 2);
}


void board::jumpPiece(int sx, int sy, int nx, int ny){
	dNode<piece> *p1 = pieces.getItem(sx, sy);
	int dirx = (nx - sx)/2;
	int diry = (ny - sy)/2;
	dNode<piece> *p2 = pieces.getItem(sx + dirx, sy + diry);
	if(nullptr == p1 || nullptr == p2 || p1->getValue()->getTeam() == p2->getValue()->getTeam()){
		return;
	}
	pieces.remove(p2->getValue());
	movePiece(p1->getValue(), nx, ny);
}


void board::movePiece(int sx, int sy, int nx, int ny){
	dNode<piece>* p = pieces.getItem(sx, sy);
	if(p == nullptr){
		return;
	}
	piece pce(p->getValue());
	movePiece(pce, nx, ny);
}


void board::movePiece(piece sp, int x, int y){
	pieces.remove(sp);
	int dx = x-sp.primary();
	int dy = y-sp.secondary();
	switch(sp.getTeam()){
		case red:
			if(dx == -1){
				if(dy == -1){
					sp.rMoveRight(8);
				}
				else if(dy == 1){
					sp.kMoveRight(8);
				}
				else{
					throw std::runtime_error("movePiece(" + sp.to_string() + ", " + std::to_string(x) + " " + std::to_string(y) + ")Invalid move: red. dx = " + std::to_string(dx) + "; dy = " + std::to_string(dy));
				}
			}
			else if(dx == 1){
				if(dy == -1){
					sp.rMoveLeft(8);
				}
				else if(dy == 1){
					sp.kMoveLeft(8);
				}
				else{
					throw std::runtime_error("movePiece(" + sp.to_string() + ", " + std::to_string(x) + " " + std::to_string(y) + ")Invalid move: red. dx = " + std::to_string(dx) + "; dy = " + std::to_string(dy));
				}
			}
			else if(dx == -2){
				if(dy == -2){
					sp.rJumpRight(8);
				}
				else if(dy == 2){
					sp.kJumpRight(8);
				}
				else{
					throw std::runtime_error("movePiece(" + sp.to_string() + ", " + std::to_string(x) + " " + std::to_string(y) + ")Invalid move: red. dx = " + std::to_string(dx) + "; dy = " + std::to_string(dy));
				}
			}
			else if(dx == 2){
				if(dy == -2){
					sp.rJumpLeft(8);
				}
				else if(dy == 2){
					sp.kJumpLeft(8);
				}
				else{
					throw std::runtime_error("movePiece(" + sp.to_string() + ", " + std::to_string(x) + " " + std::to_string(y) + ")Invalid move: red. dx = " + std::to_string(dx) + "; dy = " + std::to_string(dy));
				}
			}
			else{
				throw std::runtime_error("movePiece(" + sp.to_string() + ", " + std::to_string(x) + " " + std::to_string(y) + ")Invalid move: red. dx = " + std::to_string(dx) + "; dy = " + std::to_string(dy));
			}
			if(sp.secondary() == 0){
				sp.promote();
			}
			break;
		case black:
			if(dx == -1){
				if(dy == -1){
					sp.kMoveLeft(8);
				}
				else if(dy == 1){
					sp.rMoveLeft(8);
				}
				else{
					throw std::runtime_error("movePiece(" + sp.to_string() + ", " + std::to_string(x) + " " + std::to_string(y) + ")Invalid move: red. dx = " + std::to_string(dx) + "; dy = " + std::to_string(dy));
				}
			}
			else if(dx == 1){
				if(dy == -1){
					sp.kMoveRight(8);
				}
				else if(dy == 1){
					sp.rMoveRight(8);
				}
				else{
					throw std::runtime_error("movePiece(" + sp.to_string() + ", " + std::to_string(x) + " " + std::to_string(y) + ")Invalid move: black. dx = " + std::to_string(dx) + "; dy = " + std::to_string(dy));
				}
			}
			else if(dx == -2){
				if(dy == -2){
					sp.kJumpLeft(8);
				}
				else if(dy == 2){
					sp.rJumpLeft(8);
				}
				else{
					throw std::runtime_error("movePiece(" + sp.to_string() + ", " + std::to_string(x) + " " + std::to_string(y) + ")Invalid move: black. dx = " + std::to_string(dx) + "; dy = " + std::to_string(dy));
				}
			}
			else if(dx == 2){
				if(dy == -2){
					sp.kJumpRight(8);
				}
				else if(dy == 2){
					sp.rJumpRight(8);
				}
				else{
					throw std::runtime_error("movePiece(" + sp.to_string() + ", " + std::to_string(x) + " " + std::to_string(y) + ")Invalid move: black. dx = " + std::to_string(dx) + "; dy = " + std::to_string(dy));
				}
			}
			else{
				throw std::runtime_error("movePiece(" + sp.to_string() + ", " + std::to_string(x) + " " + std::to_string(y) + ")Invalid move: black. dx = " + std::to_string(dx) + "; dy = " + std::to_string(dy));
			}
			if(sp.secondary() == 7){
				sp.promote();
			}
			break;
		default:
			return;
	}
	pieces.insert(sp);
}


vector<pmove> board::getValidMoves(){
	vector<dNode<piece>> current = pieces.inorder();
	vector<pmove> moves;
	team t;
	int forward = 0;
	int right = 0;
	for(int i = 0; i < current.size(); i += 1){
		vector<pair<int>> moveset;
		piece p = *current[i].getValue();
		t = p.getTeam();
		pair<int> start{p.primary(), p.secondary()};
		forward = (t==black)-(t==red);
		right = (t==black)-(t==red);
		if(canMoveForwardLeft(p)){
			moveset.push_back(pair<int>{-right + p.primary(), forward + p.secondary()});
		}
		if(canMoveForwardRight(p)){

			moveset.push_back(pair<int>{right + p.primary(), forward + p.secondary()});
		}
		if(canMoveBackLeft(p)){
			moveset.push_back(pair<int>{-right + p.primary(), -forward + p.secondary()});

		}
		if(canMoveBackRight(p)){
			moveset.push_back(pair<int>{right + p.primary(), -forward + p.secondary()});

		}
		if(canJumpForwardLeft(p)){
			moveset.push_back(pair<int>{(-2*right) + p.primary(), (2*forward) + p.secondary()});

		}
		if(canJumpForwardRight(p)){
			moveset.push_back(pair<int>{(2*right) + p.primary(), (2*forward) + p.secondary()});

		}
		if(canJumpBackLeft(p)){
			moveset.push_back(pair<int>{(-2*right) + p.primary(), (-2*forward) + p.secondary()});

		}
		if(canJumpBackRight(p)){
			moveset.push_back(pair<int>{(2*right) + p.primary(), (-2*forward) + p.secondary()});

		}
		if(moveset.size() > 0){  
			for(int i = 0; i < moveset.size(); i += 1){
				pmove m(start, moveset[i]);
				moves.push_back(m);
			}
		}
	}
	return moves;
}


vector<pmove> board::getValidMoves(team t){
	vector<dNode<piece>> current = pieces.inorder();
	vector<pmove> moves;
	int forward = 0;
	int right = 0;
	forward = (t==black)-(t==red);
	right = (t==black)-(t==red);
	for(int i = 0; i < current.size(); i += 1){
		vector<pair<int>> moveset;
		piece p = *current[i].getValue();
		pair<int> start{p.primary(), p.secondary()};
		if(p.getTeam() != t){
			continue;
		}
		if(canMoveForwardLeft(p)){
			moveset.push_back(pair<int>{-right + p.primary(), forward + p.secondary()});
		}
		if(canMoveForwardRight(p)){

			moveset.push_back(pair<int>{right + p.primary(), forward + p.secondary()});
		}
		if(canMoveBackLeft(p)){
			moveset.push_back(pair<int>{-right + p.primary(), -forward + p.secondary()});

		}
		if(canMoveBackRight(p)){
			moveset.push_back(pair<int>{right + p.primary(), -forward + p.secondary()});

		}
		if(canJumpForwardLeft(p)){
			moveset.push_back(pair<int>{(-2*right) + p.primary(), (2*forward) + p.secondary()});

		}
		if(canJumpForwardRight(p)){
			moveset.push_back(pair<int>{(2*right) + p.primary(), (2*forward) + p.secondary()});

		}
		if(canJumpBackLeft(p)){
			moveset.push_back(pair<int>{(-2*right) + p.primary(), (-2*forward) + p.secondary()});

		}
		if(canJumpBackRight(p)){
			moveset.push_back(pair<int>{(2*right) + p.primary(), (-2*forward) + p.secondary()});

		}
		if(moveset.size() > 0){  
			for(int i = 0; i < moveset.size(); i += 1){
				pmove m(start, moveset[i]);
				moves.push_back(m);
			}
		}
	}
	return moves;
}


void board::showBoard(WINDOW * win){

	wprintw(win,"  +");
	for(int i = 0; i < 8; i += 1){
		wprintw(win,"---+");
	}
	for(int i = 0; i < 8; i += 1){
		wprintw(win, "\n%s | ", std::to_string(7-i).c_str());
		for(int j = 0; j < 8; j += 1){
			dNode<piece>* cur = pieces.getItem(j,7-i);
			if(nullptr == cur){
				wprintw(win,"  | ");
			}

			else{
				switch(cur->getValue()->getTeam()){
						case red:
							switch(cur->getValue()->getType()){
								case regular:
									wprintw(win,"r | ");
									break;
								case king:
									wprintw(win,"R | ");
									break;
								default:
									wprintw(win,"  | ");
									break;
							}
							break;
						case black:
							switch(cur->getValue()->getType()){
								case regular:
									wprintw(win,"b | ");
									break;
								case king:
									wprintw(win,"B | ");
									break;
								default:
									wprintw(win,"  | ");
									break;
							}
							break;
						default:
							wprintw(win,"  | ");
							break;
						}
			}
		}
		wprintw(win,"\n  .");
		for(int j = 0; j < 8; j += 1){
			wprintw(win,"---.");
		}
	}
	wprintw(win,"\n");
	wprintw(win,"  ");
	for(int i = 0; i < 8; i += 1){
		wprintw(win,"  %s ", std::to_string(i).c_str());
	}
	wprintw(win,"\n");
	refresh();
}


