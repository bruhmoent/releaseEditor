#include "directives.hpp"

#ifndef TILEDATA_HPP
#define TILEDATA_HPP

struct Tile;

struct 
TileData {

    std::unordered_map<int, std::string> m_texturePaths;

    //Bind a path to an ID
    void
    addTexturePath(int id, const std::string& texturePath);

    //Get path by ID
    const std::string&
    getTexturePath(int id) const;

    //Get IDs of the tiles
    std::vector<int>
    getTileIDs() const;

};

#endif