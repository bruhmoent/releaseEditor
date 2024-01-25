// TILE_DATA_HPP

#ifndef TILE_DATA_HPP
#define TILE_DATA_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

struct
TileData 
{

    std::unordered_map<int, std::string> m_texturePaths;
    std::unordered_map<int, sf::Texture> m_textures;

    //Bind a path to an ID
    void addTexturePath(int id, const std::string& texturePath);

    //Get path by ID
    const std::string& getTexturePath(int id) const;

    //Get IDs of the tiles
    std::vector<int> getTileIDs() const;

    //Returns the refernce to a texture by the id parameter.
    const sf::Texture& getTexture(int id) const;

};

#endif