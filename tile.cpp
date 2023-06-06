#include "tile.hpp"

void
Tile::setSize(const sf::Vector2f& size)
{
	m_shape.setSize(size);
	m_sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}

void
Tile::tint(const sf::Color& tintColour)
{
	m_sprite.setColor(tintColour);
}