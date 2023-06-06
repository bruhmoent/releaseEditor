#include "directives.hpp"

#ifndef TILEMAP_HPP
#define TILEMAP_HPP

struct Tile;
struct Tiles;

struct 
TileMap
{

    int opacity = 255;
    std::vector<Tile*> m_tileMapTiles;
    std::vector<Tile*> m_helperMapTiles;
    sf::Vector2f m_gridSize = { 0.f, 0.f };

    TileMap(const sf::Vector2f& gridSize)
        : m_gridSize(gridSize) {
    }

    //Change size of tiles
    void
    setTileSize(const sf::Vector2f& tileSize);

    //Add a tile to a tilemap
    void
    addTile(Tile* tile, Tiles& tiles);

    //Tint a tilemap
    void
    tintTiles(sf::Color tintColour);

    //Set opacity of a tilemap
    void
    setOpacity(int value);

    //Draw the tilemap
    void
    draw(sf::RenderWindow& window);

    //Display the tiles
    void
    displayTiles(sf::RenderWindow& window);

    //Set the size of the grid on a tilemap
    void setGrid(const sf::Vector2f& gridSize);

    //Snap tiles to grid
    void snapTileMapTiles();

};


#endif