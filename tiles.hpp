#include "directives.hpp"

#ifndef TILES_HPP
#define TILES_HPP

struct TileMaps;
struct TileData;
struct Tile;

struct
Tiles {

    std::vector<Tile*> m_tiles;

    //Add a tile by ID
    void
    addTileByID(const TileData& tileData, int id, const sf::Vector2f& mousePosition, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, TileMaps& tileMaps, int tileMapID);

    //Add a tile to a tilemap
    void
    addTileToTileMap(const TileData& tileData, int id, const sf::Vector2f& mousePosition, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, TileMaps& tileMaps, int tileMapID);

    //Remove tile
    void
    removeTile(const sf::Vector2f& position);

    //Snaps tiles to a grid
    void
    snapAllTilesToGrid(const sf::Vector2f& gridSize);

    //Iterate though the tiles vector and check for position overlap
    bool
    isPositionOccupied(const sf::Vector2f& position) const;

};

#endif