#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include <functional>
class ActionWindow {
private:
	const int thickness = 2;

	unsigned int x, y;
	unsigned int sizex, sizey;
	sf::RectangleShape currentwindow;
	
public:
	unsigned int getX() { return x; }
	unsigned int getY() { return y; }
	sf::RectangleShape getCurrentWindow() { return currentwindow; }
	std::vector<std::vector<sf::Drawable*>> objects;
	ActionWindow(int x, int y, int sizex, int sizey) :x(x), y(y), sizex(sizex), sizey(sizey) {
		objects.resize(1);
		currentwindow=sf::RectangleShape(sf::Vector2f(x+1, y+1));
		currentwindow.setSize(sf::Vector2f(sizex-2, sizey-2));
		currentwindow.setPosition(sf::Vector2f(x + 1, y + 1));
		currentwindow.setOutlineThickness(2);
		currentwindow.setFillColor(sf::Color(0, 0, 0, 0));
		currentwindow.setOutlineColor(sf::Color(122,122,122));
		
	}
	ActionWindow(int x, int y, int* size) :ActionWindow(x, y, size[0], size[1]) {};
	std::vector<sf::RectangleShape> createField(std::vector<std::vector<int>> actionlist, int cellsize, int cellnum) {
		std::vector<sf::RectangleShape> cells;

		for (int y = 0; y < cellnum; y++) {
			for (int x = 0; x < cellnum; x++) {
				//appending new cell
				cells.push_back(sf::RectangleShape(sf::Vector2f(this->x+cellsize * x,this->y+ cellsize * y)));
				//setting settings for last appended cell
				cells[cells.size() - 1].setSize(sf::Vector2f(cellsize, cellsize));
				//connecting actionlist and cells. 1=>Life ;0=>Dead
				(actionlist[x][y] == 1) ? cells[cells.size() - 1].setFillColor(sf::Color::Green) : cells[cells.size() - 1].setFillColor(sf::Color::Black);
				cells[cells.size() - 1].setPosition(this->x+cellsize * x,this->y+ cellsize * y);
			}
		}
		return cells;
	};
	std::vector<sf::RectangleShape> createGrid(int* standartscreensize,int cellsize,int cellnum){
		std::vector<sf::RectangleShape> grid;
		for (int x = 0; x <= cellnum; x++) {
			sf::RectangleShape line1(sf::Vector2f(standartscreensize[1], 5));//vertical line
			line1.setPosition(sf::Vector2f(this->x + cellsize * x, this->y + 0));
			line1.setFillColor(sf::Color::Black);
			sf::RectangleShape line2(sf::Vector2f(standartscreensize[0], 5));//horizontal line
			line2.setPosition(sf::Vector2f(this->x + 0, this->y + cellsize * x));
			line2.setFillColor(sf::Color::Black);
			line1.rotate(90);
			grid.push_back(line1);
			grid.push_back(line2);

		}
		return grid;
	}
};

class Button:public sf::Drawable {
private:
	sf::Text text;
	sf::Font font;
	std::string stext, sactivetext;
	int size;
	int x, y;
	sf::RectangleShape contour;
	float thickness=1;
	int indent = 2;
	bool ispressed;
	bool& func;
public:
	Button(std::string str, int size, int x, int y, std::string activetext, bool& func, std::string font = "arial.ttf") :ispressed(false), x(x), y(y), size(size), stext(str), sactivetext(activetext),func(func) {
		text.setString(str); this->font.loadFromFile(font);
		text.setFont(this->font);
		text.setCharacterSize(size);
		text.setPosition(sf::Vector2f(x,y));

		contour.setPosition(text.getPosition().x,text.getPosition().y);
		contour.setSize(sf::Vector2f(text.getLocalBounds().width,text.getCharacterSize()+indent));
		contour.setFillColor(sf::Color::Transparent);
		contour.setOutlineThickness(thickness);
		contour.setOutlineColor(sf::Color::White);
	};
	void pressed(int x,int y) {
		if (x > this->x && x<(this->x + contour.getSize().x) && y>this->y && y < (this->y + contour.getSize().y))
			ispressed = !ispressed;
		if (ispressed) { 
			text.setString(sactivetext);
			func = true;
		}
		else { text.setString(stext); func = false;
		}
		
	}


	 void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		 target.draw(text,states);
		 target.draw(contour,states);

	}
};
