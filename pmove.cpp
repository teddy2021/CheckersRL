
#include <string>
using std::string;

#include "pmove.hpp"

pair<int> pmove::getStart(){
	return pair<int>{start_x, start_y};
}

pair<int> pmove::getEnd(){
	return pair<int>{end_x, end_y};
}

string pmove::to_string(){
	return "[" + std::to_string(start_x) + ", " + std::to_string(start_y) + " => " + std::to_string(end_x) + ", " + std::to_string(end_y) + "]";
}
