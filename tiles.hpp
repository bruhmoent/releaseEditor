#ifndef TILES_HPP
#define TILES_HPP

#include <SFML/Graphics.hpp>
#include "tileData.hpp"
#include "tileMaps.hpp"

class Tiles {
public:
    void addTileByID(int id, const sf::Vector2f& mousePosition, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, TileMaps& tileMaps);
    void addTileToTileMap(int id, const sf::Vector2f& mousePosition, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, TileMaps& tileMaps, int tileMapID);
    void removeTile(const sf::Vector2f& position);
    void snapAllTilesToGrid(const sf::Vector2f& gridSize);
    bool isPositionOccupied(const sf::Vector2f& position) const;

private:
    std::vector<sf::Sprite> m_tiles;
};

#endif // TILES_HPP
