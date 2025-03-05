#include <string>
using std::string;

#pragma once
enum symbol { regular, king, dead};
enum team {red, black, none};

class piece{

	private:
		symbol type;
		team color;
		int x;
		int y;
	public:
		piece(): x(0), y(0), color(red), type(regular){};
		piece(int x_coord, int y_coord):
			x(x_coord),
			y(y_coord),
			color(red),
			type(regular){};
		piece(int x_coord, int y_coord, team t): 
			x(x_coord), 
			y(y_coord), 
			color(t),
			type( regular ){};
		piece(int x_coord, int y_coord, team t, symbol symb): 
			x(x_coord),
		   	y(y_coord), 
			color(t), 
			type(symb){};

		piece(const piece& other):
			x  ( other.x ) ,
			y  ( other.y ) ,
			color ( other.color ) ,
			type ( other.type ) {};
		piece(const piece *other):
			x(other->x),
			y(other->y),
			color(other->color),
			type(other->type){};
		
		~piece(){
			x = -1;
			y = -1;
			color = none;
			type = dead;
		}

		team getTeam(){
			return color;
		};
		symbol getType(){
			return type;
		};
		void rMoveLeft(int width);
		void rMoveRight(int width);
		
		void kMoveLeft(int width);
		void kMoveRight(int width);

		void rJumpLeft(int width);
		void rJumpRight(int width);
		void kJumpLeft(int width);
		void kJumpRight(int width);

		void promote();

		int primary();
		int secondary();

		bool operator==(piece other);
		bool operator!=(piece other);	

		string to_string();
};
