#pragma once
#include "Tile.h"
#include "ResourceManager.h"

#include <string>
#include <fstream>
#include <iostream>

#define MAP_WIDTH	128
#define MAP_HEIGHT	128

class Map
{
	private:
		ResourceManager* m_resMgr;

		Tile* m_tiles[MAP_WIDTH][MAP_HEIGHT];
		int m_entities[MAP_WIDTH][MAP_HEIGHT];

		int m_solidMap[MAP_WIDTH][MAP_HEIGHT];

		int m_mapWidth, m_mapHeight;
		
		sf::Vector2f m_startPos;

	public:
		Map(ResourceManager* resMgr);
		~Map();

		int loadNextLevel(std::string levelName);

		void draw(sf::RenderWindow* win);

		int getEntity(int i, int j) {return m_entities[i][j];}
		int getMapWidth()	{return m_mapWidth;}
		int getMapHeight()	{return m_mapHeight;}
		sf::Vector2f getPlayerPos() {return m_startPos;} 
		bool isSolid(int x, int y) { if (m_solidMap[x][y] == 1) return true; else return false; }
		bool isHalfSolid(int x, int y) { if (m_solidMap[x][y] == 2) return true; else return false; }
		sf::FloatRect getBox(float x, float y){return sf::FloatRect(x*16, y*16, 16, 16);}

		Tile* getTile(int x, int y) {return m_tiles[x][y];}
};

struct MapFile
{	
	int nr;
	int w, h, x, y;

	char tiles[MAP_WIDTH][MAP_HEIGHT];
	int solid[MAP_WIDTH][MAP_HEIGHT];
	char ents[MAP_WIDTH][MAP_HEIGHT];
};