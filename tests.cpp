#include <catch2/catch_test_macros.hpp>

#include "tree.hpp"
#include "piece.hpp"

#include <vector>
using std::vector;

TEST_CASE("Testing tree and piece construction"){
	dTree<piece> t;
	vector<piece> pieces;
	for(int i = 0; i < (100 + (rand() % 1000)); i += 1){
		int x = i;
		int y = i+1;
		pieces.push_back(piece(x,y));
		t.insert(pieces[pieces.size() - 1]);
	}

	for(int i = 0; i < pieces.size() ; i += 1){
		int x = pieces[i].primary();
		int y = pieces[i].secondary();
		REQUIRE(t.getItem(x,y) != nullptr);
		REQUIRE(t.getItem(x,y)->primarySortVal() == x);
		REQUIRE(t.getItem(x,y)->secondarySortVal() == y);
	
		dNode<piece> * dp1 = t.getItem(x,y);
		dNode<piece> * dp2 = t.getItem(x,y);
		REQUIRE(dp1 == dp2);
		REQUIRE(dp1->primarySortVal() == x);
		REQUIRE(dp2->primarySortVal() == x);
		REQUIRE(dp1->secondarySortVal() == y);
		REQUIRE(dp2->secondarySortVal() == y);
	}

	for(int i = 0; i < pieces.size(); i += 1){
		int idx = rand() % pieces.size();
		int s1 = 0;
		piece p = pieces[idx];
		vector<dNode<piece>> ordering1 = t.inorder();
		s1 = t.size();
		t.remove(p);
		REQUIRE(t.getItem(p.primary(), p.secondary()) == nullptr);
		REQUIRE(t.size() < s1);
		REQUIRE(t.size() == s1 - 1);
	}

	for(int i = 0; i < pieces.size(); i += 1){
		t.insert(pieces[i]);
	}

	for(int i = 0; i < pieces.size(); i += 1){
		int idx = rand() % pieces.size();
		piece p1 = pieces[idx];
		int x = p1.primary();
		int y = p1.secondary();
		int s1 = t.size();
		t.remove(p1);
		t.insert(p1);
		REQUIRE(t.getItem(x, y) != nullptr);
		piece p2 = t.getItem(x,y)->getValue();
		REQUIRE(p1 == p2);
		REQUIRE(t.size() == s1);
	}

}

TEST_CASE("Testing board move issues"){
	dTree<piece> t;

	int count = 0;
	for(int i = 0; i < 8; i += 1){
		for(int j = i%2; j < 3; j += 2){
			t.insert( piece(i,j,black));
			count += 1;
		}
		for(int j = 7 - (i%2); j > 4; j -= 2 ){
			t.insert( piece(7-i,j,red));
			count += 1;
		}
	}
	
	SECTION("Disappearing pieces"){
		dNode<piece> * pp = t.getItem(0,2);
		piece pce = pp->getValue();
		t.remove(pce);
		pce.rMoveRight(8);
		t.insert(pce);
		REQUIRE(t.size() == count);

		pp = t.getItem(5,5);
		pce = pp->getValue();
		t.remove(pce);
		pce.rMoveRight(8);
		t.insert(pce);
		REQUIRE(t.size() == count);
	}
}
