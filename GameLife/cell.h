#pragma once
#include <SFML/Graphics.hpp>
class Cell {
private:
	sf::RectangleShape figure;
public:
	int x, y;
	bool status;

	Cell() :x(0), y(0),status(0) {};
	Cell(int x, int y,bool status,int cellsize) :x(x), y(y),status(status) {
		figure=sf::RectangleShape(sf::Vector2f(cellsize * x, cellsize * y));
	};
	Cell(const Cell& c) { x = c.x; y = c.y; status = c.status; figure = c.figure; };

	sf::RectangleShape draw() { return figure; };


};