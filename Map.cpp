#include "Map.h"

Map::Map(ResourceManager* resMgr) : m_mapWidth(0), m_mapHeight(0), m_startPos(32, 32)
{
	m_resMgr = resMgr;
}

bool Map::loadNextLevel(std::string name)
{
	std::ifstream file(name, std::ios::binary);
	if(file == NULL) return false;

	char* temp = new char[sizeof(MapFile)];
	file.read(temp, sizeof(MapFile));
	MapFile* map = (MapFile*)(temp);

	std::cout << "Map loaded successfully\n";

	m_mapWidth = map->w;
	std::cout << "Map witdh " << m_mapWidth << std::endl;

	m_mapHeight = map->h;
	std::cout << "Map height " << m_mapHeight << std::endl;

	m_startPos.x = static_cast<float>(map->x);
	std::cout << "Player X: " << m_startPos.x << std::endl;

	m_startPos.y = static_cast<float>(map->y);
	std::cout << "Player Y: " << m_startPos.y << std::endl;


	for(int j = 0; j < m_mapHeight; j++)
	{
		for(int i = 0; i < m_mapWidth; i++)
		{
			m_tiles[i][j] = new Tile(sf::Vector2f(static_cast<float>(i*16), static_cast<float>(j*16)), m_resMgr->getTexture(map->tiles[i][j]));
			m_solidMap[i][j] = map->solid[i][j] ? true : false;
			m_entities[i][j] = map->ents[i][j];
		}
	}
	std::cout << "Map initialized successfully" <<  std::endl;
	return true;
}

void Map::draw(sf::RenderWindow* win)
{
	for(int j = 0; j < m_mapHeight; j++)
	{
		for(int i = 0; i < m_mapWidth; i++)
		{
			m_tiles[i][j]->Render(win);
		}
	}
}

Map::~Map()
{
	for (int j = 0; j < m_mapHeight; ++j)
	{
		for (int i = 0; i < m_mapWidth; ++i)
		{
			delete m_tiles[i][j];
			m_tiles[i][j] = NULL;

			m_solidMap[i][j] = NULL;
			m_entities[i][j] = NULL;
		}
	}
}