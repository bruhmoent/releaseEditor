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

#include "jsonParser.hpp"
#include "tileData.hpp"

TileData 
JsonParser::loadTileData(const std::string& filePath) {
	TileData tileData;

	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cout << "Failed to open JSON file: " << filePath << std::endl;
		return tileData;
	}

	try {
		nlohmann::json json;
		file >> json;

		if (json.contains("Tile")) {
			const auto& tileJson = json["Tile"];
			for (auto it = tileJson.begin(); it != tileJson.end(); ++it) {
				int id = std::stoi(it.key());
				std::string path = it.value();
				tileData.addTexturePath(id, path);
			}
		}
	}
	catch (const std::exception& e) {
		std::cout << "Failed to parse JSON file: " << e.what() << std::endl;
	}

	file.close();

	return tileData;
}