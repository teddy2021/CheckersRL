
#include "piece.hpp"
#include <stdexcept>

#include <string>
using std::string;

void piece::rMoveLeft(int width){
	switch(color){
		case red:
			if(x + 1< width && 0 <= y - 1){
				x += 1;
				y -= 1;
			}
			else{
				throw std::runtime_error(this->to_string() + "->rMoveLeft(" +std::to_string(width) + "): Move causes piece to be outside board.");
			}
			break;
		case black:
			if(0 <= x - 1 && y + 1 < width){
				x -= 1;
				y += 1;
			}
			else{
				throw std::runtime_error(this->to_string() + "->rMoveLeft(" +std::to_string(width) + "): Move causes piece to be outside board.");
			}
			break;
		case none:
		default:
			break;
	}
}

void piece::rMoveRight(int width){
	switch(color){
		case red:
			if(x > 0 && y > 0){
				x -= 1; 
				y -= 1;
			}
			else{
				throw std::runtime_error(this->to_string() + "->rMoveRight(" + std::to_string(width) + ")Move causes piece to be outside board.");
			}
			break;
		case black:
			if(x <= width - 2 && y <= width - 2){
				x += 1;
				y += 1;
			}
			else{
				throw std::runtime_error(this->to_string() + "->rMoveRigh(" + std::to_string(width) + ")tMove causes piece to be outside board.");
			}
			break;
		case none:
		default:
			break;
	}
}


void piece::kMoveLeft(int width){
	switch(color){
		case red:
			if(x + 1 < width && y + 1 < width){
				x += 1;
				y += 1;
			}
			else{
				throw std::runtime_error(this->to_string() + "->kMoveLeft(" + std::to_string(width) + ") Move causes piece to be outside board.");
			}
			break;
		case black:
			if(0 <= x - 1 && 0 <= y - 1){
				x -= 1;
				y -= 1;
			}
			else{
				throw std::runtime_error(this->to_string() + "->kMoveLeft(" + std::to_string(width) + ") Move causes piece to be outside board.");
			}
			break;
		default:
			break;
	}
}

void piece::kMoveRight(int width){
	switch(color){
		case red:
			if(0 <= x - 1 && y + 1 < width){
				x -= 1;
				y += 1;
			}
			else{
				throw std::runtime_error(this->to_string() + "->kMoveRight(" + std::to_string(width) + ") Move causes piece to be outside board.");
			}
			break;
		case black:
			if(x + 1 <= width && 0 <= y - 1){
				x += 1;
				y -= 1;
			}
			else{
				throw std::runtime_error(this->to_string() + "->kMoveRight(" + std::to_string(width) + ") Move causes piece to be outside board.");
			}
			break;
		default:
			break;
	}
}


void piece::rJumpLeft(int width){
	switch(color){
		case red:
			if(x + 2 < width && 0 <= y - 2){
				x += 2;
				y -= 2;
			}
			else{
				throw std::runtime_error(this->to_string() + "->rJumpLeft(" + std::to_string(width) + ") Move causes piece to be outside board.");
			}
			break;
		case black:
			if(0 <= x - 2 && y + 2 < width){
				x -= 2;
				y += 2;
			}
			else{
				throw std::runtime_error(this->to_string() + "->rJumpLeft(" + std::to_string(width) + ") Move causes piece to be outside board.");
			}
			break;
		default:
			break;
	}
}

void piece::rJumpRight(int width){
	switch(color){
		case red:
			if(0 <= x - 2 && 0 <= y - 2){
				x -= 2;
				y -= 2;
			}
			else{
				throw std::runtime_error(this->to_string() + "->rJumpRight(" + std::to_string(width) + ") Move causes piece to be outside board.");
			}
			break;
		case black:
			if(x + 2 < width && y + 2 < width ){
				x += 2;
				y += 2;
			}
			else{
				throw std::runtime_error(this->to_string() + "->rJumpRight(" + std::to_string(width) + ") Move causes piece to be outside board.");
			}
			break;
		default:
			break;
	}
};


void piece::kJumpLeft(int width){
	switch(color){
		case red:
			if(x + 2 < width && y + 2 <= width){
				x += 2;
				y += 2;
			}
			else{
				throw std::runtime_error(this->to_string() + "->kJumpLeft(" + std::to_string(width) + ") Move causes piece to be outside board.");
			}
			break;
		case black:
			if(0 <= x - 2 && 0 <= y - 2){
				x -= 2;
				y -= 2;
			}
			else{
				throw std::runtime_error(this->to_string() + "->kJumpLeft(" + std::to_string(width) + ") Move causes piece to be outside board.");
			}
			break;
		default:
			break;
	}
}

void piece::kJumpRight(int width){

	switch(color){
		case red:
			if(0 <= x - 2 && y + 2 < width){
				x -= 2;
				y += 2;
			}
			else{
				throw std::runtime_error(this->to_string() + "->kJumpRight(" + std::to_string(width) + ") Move causes piece to be outside board.");
			}
			break;
		case black:
			if(x + 2 < width && 0 <= y - 2){
				x += 2;
				y -= 2;
			}
			else{
				throw std::runtime_error(this->to_string() + "->kJumpRight(" + std::to_string(width) + ") Move causes piece to be outside board.");
			}
			break;
		default:
			break;
	}
}


void piece::promote(){
	if (type == regular){
		type = king;
	}
}

int piece::primary(){
	return x;
}

int piece::secondary(){
	return y;
}


bool piece::operator==(piece other){
	return x == other.x && y == other.y && type == other.type && color == other.color;
}


bool piece::operator!=(piece other){
	return x != other.x || y != other.y || type != other.type || color != other.color;
}


string piece::to_string(){
	string res = "< ";
	switch(color){
		case red:
			res += "red, ";
			break;
		case black:
			res += "black, ";
			break;
		default:
			return " ";
			
	}
	res += std::to_string(x);
	res += ", ";
	res += std::to_string(y);
	res += " >";
	return res;
}


