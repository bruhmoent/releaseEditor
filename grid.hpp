#include "directives.hpp"

#ifndef GRID_HPP
#define GRID_HPP

struct 
Grid
{
    sf::Vector2f gridSize;
    sf::Color gridColor;

    Grid(sf::Vector2f tempSize, sf::Color tempColor) : gridSize(tempSize), gridColor(tempColor) {}

    //Create a grid in active window depending on the level size
    void
    draw(sf::RenderWindow& window, sf::Vector2u levelSize);

};

#endif