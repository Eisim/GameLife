#include <SFML/Graphics.hpp>

#include<string>
#include<iostream>
#include<vector>
#include"UI.h"
#include"GameLife.h"


int main()
{
    int step = 0;
    //change random seed
    std::srand(std::time(0));
    
    float fps = 50.f;
    sf::Clock looptimer;

    bool start = false;
    int startscreensize[2] = { 1000,800 };
    int standartscreensize[2] = { startscreensize[0],startscreensize[1]};
    int cellnum = 40;
    GameLife Gl(cellnum);
    int cellsize=(int)standartscreensize[1]/cellnum;
   
    standartscreensize[1] = cellsize * cellnum;

    sf::RenderWindow window(sf::VideoMode(standartscreensize[0], standartscreensize[1]), "Game life", sf::Style::Close);
    std::vector<sf::RectangleShape> cells;
    std::vector<sf::RectangleShape> grid;

    ActionWindow game(standartscreensize[0]-standartscreensize[1], 0, standartscreensize[1], standartscreensize[1]);
    Button btn("start", 20, 10, 10, "stop",start);
    sf::Font font; font.loadFromFile("arial.ttf");
    sf::Text counter(("step:"+std::to_string(step)),font,20);
    counter.setPosition(sf::Vector2f(0,standartscreensize[1]-25));


    game.createField(Gl.actionlist, cellnum, cellsize);
    std::vector<std::vector<int>> actionlist;
    
    //creating grid
    grid = game.createGrid(standartscreensize, cellsize,cellnum);
    
    //actionlist random filling APPENDED IN THE CLASS
    Gl.createGrid();
   

    //filling cells array;
    cells = game.createField(Gl.actionlist,cellsize,cellnum);
    
    while (window.isOpen())
    {
        //save after resize
       
        sf::Vector2u size = window.getSize();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && sf::Keyboard::Space)start = !start;

            if (event.type == sf::Event::MouseButtonPressed) {
                int Gx = sf::Mouse::getPosition(window).x;
                int Gy = sf::Mouse::getPosition(window).y;
                btn.pressed(Gx, Gy);

                int Dx = Gx - game.getX();
                int Dy = Gy - game.getY();
                if (Dx >= 0 && Dy >= 0) {
                    int x = (int)(Dx) / cellsize, y = (int)(Dy) / cellsize;
                    //change cellmode;
                    Gl.actionlist[x][y] = (Gl.actionlist[x][y] + 1) % 2;
                }
            }
        }
        
        
        if (start) {
                actionlist =Gl.nextStep();
                step++;
                counter.setString("step:" + std::to_string(step));
        }
        cells = game.createField(Gl.actionlist, cellsize, cellnum);
        window.clear();
       
        //DRAW mb tmp but I dk how do it better.
        for (int i = 0; i < cells.size(); i++) window.draw(cells[i]);
        for (int i = 0; i < grid.size(); i++) window.draw(grid[i]);
        window.draw(game.getCurrentWindow());
        

        window.draw(btn);
        window.draw(counter);
        
        
        sf::Int32 frame_duration = looptimer.getElapsedTime().asMilliseconds();
        sf::Int32 time_to_sleep = int(1000.f / fps) - frame_duration;
        if (time_to_sleep > 0) {
            sf::sleep(sf::milliseconds(time_to_sleep));
        }
        looptimer.restart();

        window.display();
    
    
    }

    return 0;

}