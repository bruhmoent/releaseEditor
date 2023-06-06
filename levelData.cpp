#include "levelData.hpp"
#include "TileMaps.hpp"
#include "TileMap.hpp"
#include "editorLog.hpp"
#include "json.hpp"
#include "tileData.hpp"
#include "tiles.hpp"
#include "tile.hpp"

void
LevelData::saveLevel(const std::string& levelName, const sf::Vector2u& levelSize, const sf::Vector2f& gridSize, TileData& tileData, Tiles& tiles, TileMaps& tileMaps) {

	if (tiles.m_tiles.empty()) {
		m_editorLog.showMessage("Cannot save an empty level.");
		return;
	}

	nlohmann::json json;

	json["LevelName"] = levelName;
	json["LevelSize"]["x"] = levelSize.x;
	json["LevelSize"]["y"] = levelSize.y;

	std::vector<nlohmann::json> tileMapData;
	for (TileMap* tileMap : tileMaps.m_tileMaps) {
		nlohmann::json tileMapInfo;
		tileMapInfo["Opacity"] = tileMap->opacity;
		tileMapInfo["GridSize"]["x"] = tileMap->m_gridSize.x;
		tileMapInfo["GridSize"]["y"] = tileMap->m_gridSize.y;

		std::vector<nlohmann::json> tileInfoData;
		for (const Tile* tile : tiles.m_tiles) {
			nlohmann::json tileInfo;
			tileInfo["ID"] = tile->m_ID;
			tileInfo["tileMapID"] = tile->m_onTileMapID;
			tileInfo["Position"]["x"] = tile->m_position.x;
			tileInfo["Position"]["y"] = tile->m_position.y;
			tileInfoData.push_back(tileInfo);
		}

		std::vector<int> helperTileIDs;
		for (const Tile* tile : tileMap->m_helperMapTiles) {
			helperTileIDs.push_back(tile->m_ID);
		}
		tileMapInfo["HelperTiles"] = helperTileIDs;
		tileMapInfo["TileMapTiles"] = tileInfoData;

		tileMapData.push_back(tileMapInfo);
	}
	json["TileMaps"] = tileMapData;

	std::vector<nlohmann::json> tileInfoData;
	for (const Tile* tile : tiles.m_tiles) {
		nlohmann::json tileInfo;
		tileInfo["Position"]["x"] = tile->m_position.x;
		tileInfo["Position"]["y"] = tile->m_position.y;
		tileInfo["TileMapIndex"] = tile->m_onTileMapID;

		tileInfo["TextureID"] = tile->m_ID;

		tileInfoData.push_back(tileInfo);
	}
	json["Tiles"] = tileInfoData;

	m_editorLog.showMessage("Level saved succesfully.");
	std::ofstream outputFile("level.json");
	outputFile << json.dump(4);
	outputFile.close();
}

void 
LevelData::loadLevel(const std::string& filePath, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, Tiles& tiles, TileData& tileData, TileMaps& tileMaps)
{

	if (filePath.substr(filePath.find_last_of('.') + 1) != "json") {
		throw std::runtime_error("Invalid file format. Expected a JSON file.");
	}

	for (TileMap* tileMap : tileMaps.m_tileMaps) {
		for (Tile* tile : tileMap->m_helperMapTiles) {
			delete tile;
		}
		tileMap->m_helperMapTiles.clear();

		for (Tile* tile : tileMap->m_tileMapTiles) {
			delete tile;
		}
		tileMap->m_tileMapTiles.clear();
	}

	if (!tiles.m_tiles.empty() && !tileMaps.m_tileMaps.empty()) {
		tiles.m_tiles.clear();
		tileMaps.m_tileMaps.clear();
	}

	nlohmann::json json;
	std::ifstream inputFile(filePath);
	inputFile >> json;
	inputFile.close();

	for (const auto& tileMapInfo : json["TileMaps"]) {
		TileMap* tileMap = new TileMap({ tileMapInfo["GridSize"]["x"], tileMapInfo["GridSize"]["y"] });
		tileMap->m_gridSize.x = tileMapInfo["GridSize"]["x"];
		tileMap->m_gridSize.y = tileMapInfo["GridSize"]["y"];
		tileMap->opacity = tileMapInfo["Opacity"];

		tileMaps.m_tileMaps.push_back(tileMap);
	}

	std::vector<TileMap*> loadedTileMaps;
	std::map<int, int> tileMapIndexMap;

	for (const auto& tileMapInfo : json["TileMaps"]) {
		TileMap* tileMap = new TileMap({ tileMapInfo["GridSize"]["x"], tileMapInfo["GridSize"]["y"] });
		tileMap->m_gridSize.x = tileMapInfo["GridSize"]["x"];
		tileMap->m_gridSize.y = tileMapInfo["GridSize"]["y"];
		tileMap->opacity = tileMapInfo["Opacity"];

		loadedTileMaps.push_back(tileMap);
	}

	for (int i = 0; i < loadedTileMaps.size(); ++i) {
		tileMapIndexMap[i] = i;
	}

	for (const auto& tileMapInfo : json["TileMaps"]) {
		if (tileMapInfo.contains("TileMapTiles") && !tileMapInfo["TileMapTiles"].empty()) {
			for (const auto& tileInfo : tileMapInfo["TileMapTiles"]) {
				if (tileInfo.contains("tileMapID") && tileInfo["tileMapID"].is_number()) {
					int tileMapID = tileInfo["tileMapID"].get<int>();

					auto it = tileMapIndexMap.find(tileMapID);
					if (it != tileMapIndexMap.end()) {
						int tileMapIndex = it->second;

						float posX = tileInfo["Position"]["x"].get<float>();
						float posY = tileInfo["Position"]["y"].get<float>();
						int id = tileInfo["ID"];

						if (tileMapIndex >= 0 && tileMapIndex < loadedTileMaps.size()) {
							TileMap* currentTileMap = loadedTileMaps[tileMapIndex];
							tiles.addTileToTileMap(tileData, id, sf::Vector2f(posX, posY), currentTileMap->m_gridSize, levelSize, tileMaps, tileMapIndex);
						}
						else {
							std::cout << "Invalid tile map index: " << tileMapIndex << std::endl;
							std::cout << "loadedTileMaps.size(): " << loadedTileMaps.size() << std::endl;
						}
					}
					else {
						std::cout << "Invalid or missing tile map ID: " << tileMapID << std::endl;
					}
				}
				else {
					std::cout << "Invalid or missing 'tileMapID' value in tile info." << std::endl;
				}
			}
		}
		else {
			std::cout << "Empty or missing 'TileMapTiles' array in tile map." << std::endl;
		}
	}

	m_editorLog.showMessage("Level loaded successfully.");

}

void
LevelData::truncateLevel(const std::string& filePath) {
	if (filePath.substr(filePath.find_last_of('.') + 1) != "json") {
		throw std::runtime_error("Invalid file format. Expected a JSON file.");
	}

	std::ofstream saveFile(filePath, std::ios::trunc);
	saveFile.close();
	std::remove(filePath.c_str());
}