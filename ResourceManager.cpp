#include "ResourceManager.h"

ResourceManager::ResourceManager(std::string tileSheet, std::string playerSheet)
{
	sf::Image sheet;
	sheet.LoadFromFile(tileSheet);

	int x = 0, y = 0;
	for(int i = 0; i < TOTAL_SPRITES; i++)
	{
		m_tileTex[i] = new sf::Texture();
		m_tileTex[i]->LoadFromImage(sheet, sf::IntRect(x, y, 16, 16));

		x += 16;

		if(x >= 128)
		{
			x = 0;
			y += 16;
		}
	}

	sheet.LoadFromFile(playerSheet);
	m_playerTex = new sf::Texture();
	m_playerTex->LoadFromImage(sheet);
}