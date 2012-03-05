#include "Map.h"

Map::Map(ResourceManager* resMgr) : m_mapWidth(0), m_mapHeight(0), m_startPos(32, 32)
{
	m_resMgr = resMgr;
}

bool Map::LoadNextLevel(std::string name)
{
	std::ifstream map("data/maps/new.map");
	if(map == NULL) return false;

	std::cout << "Map loaded successfully\n";

	map >> m_mapWidth;
	if(map.eof()) return false;
	std::cout << "Map witdh " << m_mapWidth << std::endl;

	map >> m_mapHeight;
	if(map.eof()) return false;
	std::cout << "Map height " << m_mapHeight << std::endl;

	for(int j = 0; j < m_mapHeight; j++)
	{
		for(int i = 0; i < m_mapWidth; i++)
		{
			int buffer;
			map >> buffer;
			m_tiles[i][j] = new Tile(sf::Vector2f(static_cast<float>(i*16), static_cast<float>(j*16)), m_resMgr->getTexture(buffer));
		}
	}

	for(int j = 0; j < m_mapHeight; j++)
	{
		for(int i = 0; i < m_mapWidth; i++)
		{
			int buffer;
			map >> buffer;
			m_solidMap[i][j] = buffer;
		}
	}

	for(int j = 0; j < m_mapHeight; j++)
	{
		for(int i = 0; i < m_mapWidth; i++)
		{
			int buffer;
			map >> buffer;
			m_entities[i][j] = buffer;
		}
	}
	std::cout << "Map initialized successfully" <<  std::endl;
	return true;
}

void Map::Draw(sf::RenderWindow* win)
{
	for(int j = 0; j < m_mapHeight; j++)
	{
		for(int i = 0; i < m_mapWidth; i++)
		{
			m_tiles[i][j]->Render(win);
		}
	}
}