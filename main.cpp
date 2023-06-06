#include "horizontalMenu.hpp"
#include "levelData.hpp"
#include "placementManager.hpp"
#include "jsonParser.hpp"
#include "grid.hpp"
#include "editorLog.hpp"
#include "tileMap.hpp"
#include "tileData.hpp"
#include "tileMaps.hpp"
#include "tiles.hpp"
#include "camera.hpp"

//EXAMPLE BASIC IMPLEMENATION, NOT A GOOD PRACTICE TO USE SO MANY GLOBAL VARIABLES
sf::Vector2f gridSize(64, 64);
sf::RenderWindow g_window(sf::VideoMode(800, 600), "Level Editor");
Grid g_grid({ gridSize }, sf::Color(255, 255, 255, 128));
HorizontalMenu<std::string> g_taskbar(400, 50, 20, sf::Color(202, 164, 144, 125), sf::Color::Black);
Camera g_camera;
Tiles g_tileManager;
HorizontalMenu<std::string> g_toolbar(400, 50, 20, sf::Color(202, 164, 144, 125), sf::Color::Black);
TileData g_tileData;
PlacementManager g_placementManager;
EditorLog g_editorLog(g_window, "assets/font.ttf");
LevelData g_level(g_editorLog);
TileMaps g_tileMaps;
TileMap g_tileMap({ 64.f,64.f });

int main()
{
	sf::Image icon;
	if (!icon.loadFromFile("assets/icongear.png"))
	{
		std::cerr << "Couldn't load icon." << std::endl;
	}
	g_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	sf::Clock clock;
	bool isMouseHeld = false;
	bool isShiftHeld = false;
	bool isResizing = false;
	int tileID = 2; //Example index
	sf::Vector2u levelSize(1000, 500);
	sf::Event event;
	sf::FloatRect selectionRect;
	sf::Vector2f initialMousePos;
	sf::RectangleShape selectionShape;

	float toolbarWidth = 200.f;
	sf::Color backgroundColor(255, 255, 255, 125);
	sf::Color textColor = sf::Color::Black;
	float windowWidth = g_window.getSize().x;
	float windowHeight = g_window.getSize().y;

	std::string filePath = "tileSchema.json";
	TileData tileData = JsonParser::loadTileData(filePath);
	std::vector<int> tileIDs = tileData.getTileIDs();
	for (int id : tileIDs) {
		std::cout << "Tile ID: " << id << ", Path: " << tileData.getTexturePath(id) << std::endl;
		g_tileData.addTexturePath(id, tileData.getTexturePath(id));
	}

	g_toolbar.setPosition(500.f, 0.f);
	g_taskbar.addButton("Save", "assets/saveIcon.png", [&levelSize]() { g_level.saveLevel("test", levelSize, gridSize, g_tileData, g_tileManager, g_tileMaps); });
	g_taskbar.addButton("Load", "assets/loadIcon.png", [&levelSize]() { g_level.loadLevel("level.json", gridSize, levelSize, g_tileManager, g_tileData, g_tileMaps); });
	g_toolbar.addButton("Button 1", "tile.png", [&tileID]() { tileID = 1; std::cout << "1\n"; });
	g_toolbar.addButton("Button 2", "box.png", [&tileID]() { tileID = 2; std::cout << "2\n"; });
	g_window.setFramerateLimit(60);

	g_tileMap = TileMap({ 64.f, 64.f });
	g_tileMaps.addTileMap(g_tileMap);
	g_tileMaps.setActive(0);

	TileMap temporary({ 32.f, 32.f });
	g_tileMaps.addTileMap(temporary);
	temporary.setGrid({ 32.f, 32.f });

	while (g_window.isOpen())
	{
		g_window.clear(sf::Color(30, 30, 30));

		while (g_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				g_window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				g_camera.zoomIn(g_window, 0.9f);
				std::cout << g_camera.m_zoomLevel << std::endl;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				g_camera.zoomOut(g_window, 0.9f);
				std::cout << g_camera.m_zoomLevel << std::endl;
			}
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
			{
				isMouseHeld = true;
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				isMouseHeld = false;
			}
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				g_toolbar.handleButtons(g_window);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LShift) {
				if (!isShiftHeld) {
					isShiftHeld = true;
					initialMousePos = g_window.mapPixelToCoords(sf::Mouse::getPosition(g_window));
					selectionRect.left = initialMousePos.x;
					selectionRect.top = initialMousePos.y;
					selectionRect.width = 0.f;
					selectionRect.height = 0.f;
					isResizing = true;
				}
			}

			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LShift) {
				isShiftHeld = false;
				isResizing = false;
				g_placementManager.activeArea(g_tileData, tileID, g_tileManager, gridSize, levelSize, selectionRect, g_tileMaps);
				g_tileManager.snapAllTilesToGrid(gridSize);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
				sf::Vector2f initialPosition = g_window.mapPixelToCoords(sf::Mouse::getPosition(g_window));
				g_placementManager.activeErase({ 64.f, 64.f }, g_tileManager);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
				g_level.saveLevel("test", levelSize, gridSize, g_tileData, g_tileManager, g_tileMaps);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L) {
				g_tileMaps.setActive(1);
				gridSize = g_tileMaps.getCurrentGridSize();
				g_grid.gridSize = g_tileMaps.getCurrentGridSize();
				std::cout << g_tileMaps.m_activeTileMapIndex;
			}
			
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K) {
				g_tileMaps.setActive(0);
				gridSize = g_tileMaps.getCurrentGridSize();
				g_grid.gridSize = g_tileMaps.getCurrentGridSize();
				std::cout << g_tileMaps.m_activeTileMapIndex;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O) {
				g_level.loadLevel("level.json", gridSize, levelSize, g_tileManager, g_tileData, g_tileMaps);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
			{
				sf::Vector2f initialPosition = g_window.mapPixelToCoords(sf::Mouse::getPosition(g_window));
				g_placementManager.activeFill(g_tileData, tileID, g_tileManager, gridSize, levelSize, initialPosition, g_tileMaps);
			}

			if (isResizing) {
				sf::Vector2f currentMousePos = g_window.mapPixelToCoords(sf::Mouse::getPosition(g_window));
				selectionRect.width = currentMousePos.x - initialMousePos.x;
				selectionRect.height = currentMousePos.y - initialMousePos.y;
				selectionShape.setPosition(initialMousePos);
				selectionShape.setSize(sf::Vector2f(selectionRect.width, selectionRect.height));
				selectionShape.setFillColor(sf::Color(0, 255, 0, 128));
				g_window.draw(selectionShape);
			}

			else {
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !g_taskbar.isMouseInside(g_window) && !g_toolbar.isMouseInside(g_window)) {
					sf::Vector2f mousePosition = g_window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					g_placementManager.activeSingular(g_tileData, tileID, g_tileManager, mousePosition, gridSize, levelSize, g_tileMaps);
				}
			}
		}

		float deltaTime = clock.restart().asSeconds();

		if (isMouseHeld)
		{
			g_camera.viewFollow(g_window.mapPixelToCoords(sf::Mouse::getPosition(g_window)), g_window, 0.1f);
		}

		g_tileMaps.displayAllTiles(g_window);
		g_tileMaps.displayLayering(g_window);

		g_editorLog.update(deltaTime);
		g_window.draw(g_editorLog.m_message);

		g_toolbar.handleStaticHover(g_window);
		g_toolbar.staticDisplay(g_window);
		g_toolbar.handleButtons(g_window);

		for (TileMap* tm : g_tileMaps.m_tileMaps) {
			tm->snapTileMapTiles();
		}

		g_taskbar.handleStaticHover(g_window);
		g_taskbar.staticDisplay(g_window);
		g_taskbar.handleButtons(g_window);

		g_grid.draw(g_window, levelSize);

		g_window.display();
	}
	return 0;
}