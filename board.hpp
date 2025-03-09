#pragma once
#include "piece.hpp"
#include "tree.hpp"
#include "pmove.hpp"

#include <vector>
using std::vector;
#include <string>
using std::string;

#include <curses.h>
class board{
	private:
		string prevStart;
		string prevEnd;
		dTree<piece> pieces;
		void removePiece(int x, int y);
		void removePiece(piece p);

		bool inbounds(piece p, int x, int y);
		bool occupied(piece p, int offset_x, int offset_y);
		bool opposing(piece p, int x, int y);

		bool canMoveForwardLeft(piece p);
		bool canMoveForwardRight(piece p);
		bool canMoveBackLeft(piece p);
		bool canMoveBackRight(piece p);
		
		bool canJumpForwardLeft(piece p);
		bool canJumpForwardRight(piece p);
		bool canJumpBackLeft(piece p);
		bool canJumpBackRight(piece p);

	public:
		board();
		~board();
		vector<pmove> getValidMoves();
		vector<pmove> getValidMoves(team t);
		
		void movePiece(int sx, int sy, int ex, int ey);
		void movePiece(piece sp, int x, int y);
		void jumpPiece(int sx, int sy, int ex, int ey);
		string moveString();


		void showBoard(WINDOW * win);
};
