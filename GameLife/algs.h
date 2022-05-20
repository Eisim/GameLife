#pragma once


std::vector<sf::RectangleShape> createField(std::vector<std::vector<int>> actionlist, int cellsize, int cellnum);
int getNeighbour(int Cx, int Cy, std::vector<std::vector<int>> actionlist);
std::vector<std::vector<int>> nextStep(std::vector<std::vector<int>> actionlist);