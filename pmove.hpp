#include <string>

#pragma once
template <typename t>
struct pair{
	t x;
	t y;
};

class pmove{
	private:
		int start_x;
		int start_y;
		int end_x;
		int end_y;

	public:
		pmove(pair<int> start, pair<int> end): start_x(start.x), start_y(start.y),
		end_x(end.x), end_y(end.y){};
		pmove(int x1, int y1, int x2, int y2): start_x(x1), start_y(y1), 
		end_x(x2), end_y(y2){};

		pair<int> getStart();
		pair<int> getEnd();

		std::string to_string();
};

		
