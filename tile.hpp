#include "directives.hpp"

#ifndef TILE_HPP
#define TILE_HPP

struct 
Tile {

    sf::Sprite m_sprite;
    sf::RectangleShape m_shape;
    sf::Vector2f m_position;
    int m_onTileMapID = 0;
    int m_ID;

    Tile(sf::Sprite sprite = sf::Sprite(), sf::RectangleShape shape = sf::RectangleShape(), sf::Vector2f position = sf::Vector2f(), int ID = 0)
        : m_sprite(sprite), m_shape(shape), m_position(position), m_ID(ID)
    {
        m_sprite.setPosition(m_position);
    }

    //Set the size of the tile
    void
    setSize(const sf::Vector2f& size);

    //Tint a tile
    void
    tint(const sf::Color& tintColour);

};

#endif