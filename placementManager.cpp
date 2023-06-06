#include "placementManager.hpp"
#include "tiles.hpp"
#include "tileData.hpp"

void
PlacementManager::activeErase(const sf::Vector2f& mousePosition, Tiles& tiles)
{
	tiles.removeTile(mousePosition);
}

void
PlacementManager::activeFill(TileData _t, int ID, Tiles& tiles, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, const sf::Vector2f& mousePosition, TileMaps& tileMaps)
{
	sf::Vector2f startPoint = sf::Vector2f(std::floor(mousePosition.x / gridSize.x) * gridSize.x,
		std::floor(mousePosition.y / gridSize.y) * gridSize.y);

	if (tiles.isPositionOccupied(startPoint)) {
		return;
	}

	std::stack<sf::Vector2f> fillStack;
	fillStack.push(startPoint);

	while (!fillStack.empty()) {
		sf::Vector2f position = fillStack.top();
		fillStack.pop();

		if (!tiles.isPositionOccupied(position)) {
			tiles.addTileByID(_t, ID, position, gridSize, levelSize, tileMaps, -1);

			sf::Vector2f leftPos(position.x - gridSize.x, position.y);
			sf::Vector2f rightPos(position.x + gridSize.x, position.y);
			sf::Vector2f upPos(position.x, position.y - gridSize.y);
			sf::Vector2f downPos(position.x, position.y + gridSize.y);

			if (leftPos.x >= 0 && !tiles.isPositionOccupied(leftPos)) {
				fillStack.push(leftPos);
			}
			if (rightPos.x < levelSize.x && !tiles.isPositionOccupied(rightPos)) {
				fillStack.push(rightPos);
			}
			if (upPos.y >= 0 && !tiles.isPositionOccupied(upPos)) {
				fillStack.push(upPos);
			}
			if (downPos.y < levelSize.y && !tiles.isPositionOccupied(downPos)) {
				fillStack.push(downPos);
			}
		}
	}
}

void
PlacementManager::activeArea(TileData _t, int ID, Tiles& tiles, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, const sf::FloatRect& selectionRect, TileMaps& tileMaps)
{
	for (float y = selectionRect.top; y < selectionRect.top + selectionRect.height; y += gridSize.y)
	{
		for (float x = selectionRect.left; x < selectionRect.left + selectionRect.width; x += gridSize.x)
		{
			sf::Vector2f position(x, y);
			tiles.addTileByID(_t, ID, position, gridSize, levelSize, tileMaps, -1);
		}
	}
}

void
PlacementManager::activeSingular(TileData _t, int ID, Tiles& tiles, const sf::Vector2f& mousePosition, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, TileMaps& tileMaps)
{
	tiles.addTileByID(_t, ID, mousePosition, gridSize, levelSize, tileMaps, -1);
}