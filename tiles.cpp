#include "tile.hpp"
#include "tiles.hpp"
#include "tileData.hpp"
#include "tileMaps.hpp"
#include "tileMap.hpp"

void
Tiles::addTileByID(const TileData& tileData, int id, const sf::Vector2f& mousePosition, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, TileMaps& tileMaps, int tileMapID)
{
	const std::string& texturePath = tileData.getTexturePath(id);
	if (texturePath.empty()) {
		std::cout << "Invalid tile ID: " << id << std::endl;
		return;
	}

	std::shared_ptr<sf::Texture> tileTexture = std::make_shared<sf::Texture>();
	if (!tileTexture->loadFromFile(texturePath)) {
		std::cout << "Failed to load texture: " << texturePath << std::endl;
		return;
	}

	std::shared_ptr<sf::Sprite> tileSprite = std::make_shared<sf::Sprite>(*tileTexture);
	sf::RectangleShape tileShape(sf::Vector2f(tileTexture->getSize().x, tileTexture->getSize().y));
	sf::Vector2f mousePos = sf::Vector2f(mousePosition.x, mousePosition.y);
	Tile* tile = new Tile(*tileSprite, tileShape, mousePos, id);

	sf::Texture* l_texture = new sf::Texture;
	l_texture->setSmooth(true);
	l_texture->setRepeated(true);
	if (!l_texture->loadFromFile(texturePath)) {
		delete l_texture;
		std::cout << "Failed to load texture: " << texturePath << std::endl;
		return;
	}
	tile->m_sprite.setTexture(*l_texture);
	tile->m_sprite.setPosition(tile->m_shape.getPosition().x, tile->m_shape.getPosition().y);
	tile->m_sprite.setTextureRect(sf::IntRect(0, 0, tile->m_shape.getSize().x, tile->m_shape.getSize().y));

	if (tileMapID == -1)
	{
		sf::Vector2u textureSize = l_texture->getSize();
		float scaleX = gridSize.x / textureSize.x;
		float scaleY = gridSize.y / textureSize.y;
		tile->m_sprite.setScale(scaleX, scaleY);

		float snappedX = std::floor(tile->m_position.x / gridSize.x) * gridSize.x;
		float snappedY = std::floor(tile->m_position.y / gridSize.y) * gridSize.y;
		tile->m_position = sf::Vector2f(snappedX, snappedY);
	}

	sf::Vector2f maxGrids = sf::Vector2f(levelSize.x / gridSize.x, levelSize.y / gridSize.y);
	if (tile->m_position.x < 0 || tile->m_position.y < 0 || tile->m_position.x >= maxGrids.x * gridSize.x || tile->m_position.y >= maxGrids.y * gridSize.y) {
		return;
	}

	if (tileMapID == -1) {
		tileMaps.getCurrentTileMap()->addTile(tile, *this);
		tile->m_onTileMapID = tileMaps.getCurrentTileMapIndex();
	}

	else {
		int tileMapIndex = tileMaps.getCurrentTileMapIndex();
		if (tileMapIndex == -1) {
			std::cout << "Invalid tile map index: " << tileMapIndex << std::endl;
			return;
		}
		sf::Vector2u textureSize = l_texture->getSize();
		float scaleX = tileMaps.m_tileMaps[tileMapIndex]->m_gridSize.x / textureSize.x;
		float scaleY = tileMaps.m_tileMaps[tileMapIndex]->m_gridSize.y / textureSize.y;
		tile->m_sprite.setScale(scaleX, scaleY);

		float snappedX = std::floor(tile->m_position.x / tileMaps.m_tileMaps[tileMapIndex]->m_gridSize.x) * tileMaps.m_tileMaps[tileMapIndex]->m_gridSize.x;
		float snappedY = std::floor(tile->m_position.y / tileMaps.m_tileMaps[tileMapIndex]->m_gridSize.y) * tileMaps.m_tileMaps[tileMapIndex]->m_gridSize.y;
		tile->m_position = sf::Vector2f(snappedX, snappedY);

		tile->m_onTileMapID = tileMapIndex;
		tileMaps.m_tileMaps[tileMapIndex]->addTile(tile, *this);
	}

	m_tiles.push_back(tile);
}

void
Tiles::addTileToTileMap(const TileData& tileData, int id, const sf::Vector2f& mousePosition, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, TileMaps& tileMaps, int tileMapID)
{
	const std::string& texturePath = tileData.getTexturePath(id);
	if (texturePath.empty()) {
		std::cout << "Invalid tile ID: " << id << std::endl;
		return;
	}

	std::shared_ptr<sf::Texture> tileTexture = std::make_shared<sf::Texture>();
	if (!tileTexture->loadFromFile(texturePath)) {
		std::cout << "Failed to load texture: " << texturePath << std::endl;
		return;
	}

	std::shared_ptr<sf::Sprite> tileSprite = std::make_shared<sf::Sprite>(*tileTexture);
	sf::RectangleShape tileShape(sf::Vector2f(tileTexture->getSize().x, tileTexture->getSize().y));
	sf::Vector2f mousePos = sf::Vector2f(mousePosition.x, mousePosition.y);
	Tile* tile = new Tile(*tileSprite, tileShape, mousePos, id);

	sf::Texture* l_texture = new sf::Texture;
	l_texture->setSmooth(true);
	l_texture->setRepeated(true);
	if (!l_texture->loadFromFile(texturePath)) {
		delete l_texture;
		std::cout << "Failed to load texture: " << texturePath << std::endl;
		return;
	}
	tile->m_sprite.setTexture(*l_texture);
	tile->m_sprite.setPosition(tile->m_shape.getPosition().x, tile->m_shape.getPosition().y);
	tile->m_sprite.setTextureRect(sf::IntRect(0, 0, tile->m_shape.getSize().x, tile->m_shape.getSize().y));

	sf::Vector2u textureSize = l_texture->getSize();
	float scaleX = gridSize.x / textureSize.x;
	float scaleY = gridSize.y / textureSize.y;
	tile->m_sprite.setScale(scaleX, scaleY);

	float snappedX = std::floor(tile->m_position.x / gridSize.x) * gridSize.x;
	float snappedY = std::floor(tile->m_position.y / gridSize.y) * gridSize.y;
	tile->m_position = sf::Vector2f(snappedX, snappedY);

	sf::Vector2f maxGrids = sf::Vector2f(levelSize.x / gridSize.x, levelSize.y / gridSize.y);
	if (tile->m_position.x < 0 || tile->m_position.y < 0 || tile->m_position.x >= maxGrids.x * gridSize.x || tile->m_position.y >= maxGrids.y * gridSize.y) {
		return;
	}

	tile->m_onTileMapID = tileMapID;
	tileMaps.m_tileMaps[tile->m_onTileMapID]->addTile(tile, *this);

	m_tiles.push_back(tile);
}

void 
Tiles::removeTile(const sf::Vector2f& position)
{
	for (auto it = m_tiles.begin(); it != m_tiles.end(); ++it) {
		if ((*it)->m_position == position) {
			delete* it;
			m_tiles.erase(it);
			break;
		}
	}
}

void
Tiles::snapAllTilesToGrid(const sf::Vector2f& gridSize) {
	for (Tile*& tile : m_tiles) {
		float snappedX = std::floor(tile->m_position.x / gridSize.x) * gridSize.x;
		float snappedY = std::floor(tile->m_position.y / gridSize.y) * gridSize.y;

		tile->m_position = sf::Vector2f(snappedX, snappedY);
		tile->m_sprite.setPosition(tile->m_position);
	}
}

bool
Tiles::isPositionOccupied(const sf::Vector2f& position) const
{
	for (const Tile* tile : m_tiles) {
		if (tile->m_position == position) {
			return true;
		}
	}
	return false;
}