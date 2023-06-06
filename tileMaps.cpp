#include "tileMaps.hpp"
#include "tileMap.hpp"

void
TileMaps::addTileMap(const TileMap& tileMap) {
	m_tileMaps.push_back(new TileMap(tileMap));
}

void
TileMaps::setActive(int index) {
	if (index >= 0 && index < m_tileMaps.size()) {
		m_activeTileMapIndex = index;
	}
}

void TileMaps::displayLayering(sf::RenderWindow& window) {
	for (TileMap* tileMap : m_tileMaps) {
		if (tileMap == m_tileMaps[m_activeTileMapIndex]) {
			tileMap->setOpacity(255);
		}
		else {
			tileMap->setOpacity(128);
		}
	}
}

void
TileMaps::displayAllTiles(sf::RenderWindow& window) {
	for (TileMap* tileMap : m_tileMaps) {
		tileMap->displayTiles(window);
	}
}

int
TileMaps::getCurrentTileMapIndex() {
	return m_activeTileMapIndex;
}

TileMap*
TileMaps::getCurrentTileMap() {
	return m_tileMaps[m_activeTileMapIndex];
}

const sf::Vector2f&
TileMaps::getCurrentGridSize() {
	return m_tileMaps[m_activeTileMapIndex]->m_gridSize;
}