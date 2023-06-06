#include "grid.hpp"

void
Grid::draw(sf::RenderWindow& window, sf::Vector2u levelSize)
{
	sf::VertexArray lines(sf::Lines);

	sf::Vector2u windowSize = window.getSize();

	for (float y = 0; y < levelSize.y; y += gridSize.y)
	{
		lines.append(sf::Vertex(sf::Vector2f(0, y), gridColor));
		lines.append(sf::Vertex(sf::Vector2f(levelSize.x, y), gridColor));
	}

	for (float x = 0; x < levelSize.x; x += gridSize.x)
	{
		lines.append(sf::Vertex(sf::Vector2f(x, 0), gridColor));
		lines.append(sf::Vertex(sf::Vector2f(x, levelSize.y), gridColor));
	}

	window.draw(lines);
}

