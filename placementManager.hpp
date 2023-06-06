#include "directives.hpp"

#ifndef PLACEMENT_MANAGER_HPP
#define PLACEMENT_MANAGER_HPP

struct TileData;
struct Tiles;
struct TileMaps;

struct 
PlacementManager
{

    // Erase object by ID 
    void
    activeErase(const sf::Vector2f& mousePosition, Tiles& tiles);

    // Fill with tiles based on tile "shapes"
    // Active fill tool using flood fill algorithm https://www.geeksforgeeks.org
    void
    activeFill(TileData _t, int ID, Tiles& tiles, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, const sf::Vector2f& mousePosition, TileMaps& tileMaps);
    // Fill selected area
    void
    activeArea(TileData _t, int ID, Tiles& tiles, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, const sf::FloatRect& selectionRect, TileMaps& tileMaps);

    // Individual tile placement
    void
    activeSingular(TileData _t, int ID, Tiles& tiles, const sf::Vector2f& mousePosition, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, TileMaps& tileMaps);

};

#endif