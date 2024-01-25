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

