#pragma once
#include <SFML/Graphics.hpp>
#include<vector>


class GameLife {
private:
	bool iscreated;
	int cellnum;

public:
	std::vector<std::vector<int>> actionlist;
	GameLife() :cellnum(0), iscreated(false) {};
	GameLife(int Cnum) :iscreated(true) { cellnum = Cnum; actionlist.resize(cellnum); for (int i = 0; i < cellnum; i++)actionlist[i].resize(cellnum); };
	void createGrid();
	int getNeighbour(int Cx, int Cy);
	std::vector<std::vector<int>> nextStep();
};