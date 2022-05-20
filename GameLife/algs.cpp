#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
std::vector<sf::RectangleShape> createField(std::vector<std::vector<int>> actionlist, int cellsize, int cellnum) {
    std::vector<sf::RectangleShape> cells;

    for (int y = 0; y < cellnum; y++) {
        for (int x = 0; x < cellnum; x++) {
            //appending new cell
            cells.push_back(sf::RectangleShape(sf::Vector2f(cellsize * x, cellsize * y)));
            //setting settings for last appended cell
            cells[cells.size() - 1].setSize(sf::Vector2f(cellsize, cellsize));
            //connecting actionlist and cells. 1=>Life ;0=>Dead
            (actionlist[x][y] == 1) ? cells[cells.size() - 1].setFillColor(sf::Color::Green) : cells[cells.size() - 1].setFillColor(sf::Color::Black);
            cells[cells.size() - 1].setPosition(cellsize * x, cellsize * y);
        }
    }
    return cells;
}
int checkPositive(int num, int module) {
    if (num < 0) return num + module;
    return num;
}

int getNeighbour(int Cx,int Cy, std::vector<std::vector<int>> actionlist) { 
    int counter=0;
    int cellnum = actionlist.size();
    for (int y = Cy - 1; y < Cy + 2; y++) {
        for (int x = Cx - 1; x < Cx + 2; x++) {
            int ym = checkPositive(y % cellnum, cellnum);
            int xm = checkPositive(x % cellnum, cellnum);
            //std::cout << "x:" << xm << "  y:" << ym <<" ";
            //std::cout << "cell:" << actionlist[xm][ym] << std::endl;
            counter += actionlist[xm][ym];
        }
    }
    counter -= actionlist[Cx][Cy];
    return counter;
}


std::vector<std::vector<int>> nextStep(std::vector<std::vector<int>> actionlist) {
    std::vector<std::vector<int>> newactionlist;
    int cellnum = actionlist.size();
    newactionlist.resize(cellnum);
    for (int i = 0; i < cellnum; i++) newactionlist[i].resize(cellnum);
    for (int y = 0; y < cellnum; y++) {
        for (int x = 0; x < cellnum; x++) {

            int currentcell = actionlist[x][y];
            int neighcount =getNeighbour(x,y, actionlist);
            
            if (currentcell == 0) {
                if (neighcount == 3)
                    newactionlist[x][y]=1;
                else { newactionlist[x][y]=0; }
            }
            else if (currentcell == 1) {

                if (neighcount == 2 || neighcount == 3) { newactionlist[x][y]=1; }
                else newactionlist[x][y]=0;
            }

        }
    }
    return newactionlist;
}