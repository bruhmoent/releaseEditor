//  LevelEditor
//  Copyright (C) 2024 bruhmoent
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
    void draw(sf::RenderWindow& window, sf::Vector2u levelSize);

};

#endif