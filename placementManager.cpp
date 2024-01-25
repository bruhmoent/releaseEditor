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

#include "placementManager.hpp"
#include "tileData.hpp"
#include "tileMaps.hpp"

void PlacementManager::activeErase(const sf::Vector2f& mousePosition, TileMaps& tileMaps)
{
    tileMaps.getCurrentTileMap()->removeTile(mousePosition);
}

void PlacementManager::activeFill(TileData _t, int ID, TileMaps& tileMaps, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, const sf::Vector2f& mousePosition)
{
    TileMap* currentTileMap = tileMaps.getCurrentTileMap();

    if (!currentTileMap)
        return;

    sf::Vector2f startPoint = sf::Vector2f(std::floor(mousePosition.x / gridSize.x) * gridSize.x,
        std::floor(mousePosition.y / gridSize.y) * gridSize.y);

    if (currentTileMap->isPositionOccupied(startPoint)) {
        return;
    }

    std::stack<sf::Vector2f> fillStack;
    fillStack.push(startPoint);

    while (!fillStack.empty()) {
        sf::Vector2f position = fillStack.top();
        fillStack.pop();

        if (!currentTileMap->isPositionOccupied(position)) {
            currentTileMap->addTile(ID, position);
            tileMaps.snapTileMapTiles();
            sf::Vector2f leftPos(position.x - gridSize.x, position.y);
            sf::Vector2f rightPos(position.x + gridSize.x, position.y);
            sf::Vector2f upPos(position.x, position.y - gridSize.y);
            sf::Vector2f downPos(position.x, position.y + gridSize.y);

            if (leftPos.x >= 0 && !currentTileMap->isPositionOccupied(leftPos)) {
                fillStack.push(leftPos);
            }
            if (rightPos.x < levelSize.x && !currentTileMap->isPositionOccupied(rightPos)) {
                fillStack.push(rightPos);
            }
            if (upPos.y >= 0 && !currentTileMap->isPositionOccupied(upPos)) {
                fillStack.push(upPos);
            }
            if (downPos.y < levelSize.y && !currentTileMap->isPositionOccupied(downPos)) {
                fillStack.push(downPos);
            }
        }
    }
}

void PlacementManager::activeArea(TileData _t, int ID, TileMaps& tileMaps, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, const sf::FloatRect& selectionRect)
{
    TileMap* currentTileMap = tileMaps.getCurrentTileMap();

    if (!currentTileMap)
        return;

    for (float y = selectionRect.top; y < selectionRect.top + selectionRect.height; y += gridSize.y)
    {
        for (float x = selectionRect.left; x < selectionRect.left + selectionRect.width; x += gridSize.x)
        {
            sf::Vector2f position(x, y);
            currentTileMap->addTile(ID, position);
        }
    }

}

void PlacementManager::activeSingular(TileData _t, int ID, TileMaps& tileMaps, const sf::Vector2f& mousePosition, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize)
{
    //FIXFORLATER: The placing is a little strange.

    TileMap* currentTileMap = tileMaps.getCurrentTileMap();

    if (!currentTileMap)
        return;

    currentTileMap->addTile(ID, mousePosition);
}
