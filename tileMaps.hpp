#include "directives.hpp"

#ifndef TILEMAPS_HPP
#define TILEMAPS_HPP

struct TileMap;

struct 
TileMaps    
{

    std::vector<TileMap*> m_tileMaps;
    int m_activeTileMapIndex = 0;

    //Add a tilemap to the tilemaps' struct
    void
    addTileMap(const TileMap& tileMap);

    //Set the current active tilemap
    void
    setActive(int index);

    //Display layering effect
    void
    displayLayering(sf::RenderWindow& window);

    //Displays all tiles
    void
    displayAllTiles(sf::RenderWindow& window);

    //Get current active tilemap
    TileMap*
    getCurrentTileMap();

    //Get current active grid size
    const sf::Vector2f&
    getCurrentGridSize();

    //Get current active index
    int 
    getCurrentTileMapIndex();

};

#endif