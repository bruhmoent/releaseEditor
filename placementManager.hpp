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

#ifndef PLACEMENT_MANAGER_HPP
#define PLACEMENT_MANAGER_HPP

struct TileData;
struct TileMaps;

struct PlacementManager
{
    // Erase object by ID
    void activeErase(const sf::Vector2f& mousePosition, TileMaps& tileMaps);

    // Fill with tiles based on shapes formed by the tiles.
    // Active fill tool using flood fill algorithm https://www.geeksforgeeks.org
    void activeFill(TileData _t, int ID, TileMaps& tileMaps, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, const sf::Vector2f& mousePosition);
    // Fill selected area
    void activeArea(TileData _t, int ID, TileMaps& tileMaps, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, const sf::FloatRect& selectionRect);

    // Individual tile placement
    void activeSingular(TileData _t, int ID, TileMaps& tileMaps, const sf::Vector2f& mousePosition, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize);
};


#endif //PLACEMENT_MANAGER_HPP