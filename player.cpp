#include "player.hpp"

void player::incrScore(){
	score += 1;
}

int player::getScore(){
	return score;
}

team player::getTeam(){
	return t;
}

p_type player::getType(){
	return type;
}

