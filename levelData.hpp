#include "directives.hpp"

#ifndef LEVEL_DATA_HPP
#define LEVEL_DATA_HPP

struct TileMap;
struct TileMaps;
struct EditorLog;
struct TileData;
struct Tiles;

struct 
LevelData {

    EditorLog& m_editorLog;

    LevelData(EditorLog& editorLog) : m_editorLog(editorLog) {}

    //Save level to a .json file
    void
    saveLevel(const std::string& levelName, const sf::Vector2u& levelSize, const sf::Vector2f& gridSize, TileData& tileData, Tiles& tiles, TileMaps& tileMaps);

    // Load level from a .json file
    void
    loadLevel(const std::string& filePath, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, Tiles& tiles, TileData& tileData, TileMaps& tileMaps);
    
    //Truncate a .json level file
    void
    truncateLevel(const std::string& filePath);

};

#endif