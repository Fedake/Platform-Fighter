#include "ResourceManager.h"

ResourceManager::ResourceManager(std::string tileSheet, std::string playerSheet, std::string entitySheet, std::string hudSheet)
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

	sheet.LoadFromFile(entitySheet);

	for(int i = 1; i < TOTAL_ENTITIES; i++)
	{
		m_entTex[i] = new sf::Texture();
		m_entTex[i]->LoadFromImage(sheet, sf::IntRect(0, (i-1)*16, sheet.GetWidth(), 16));
	}

	sheet.LoadFromFile(hudSheet);
	m_hudTex = new sf::Texture();
	m_hudTex->LoadFromImage(sheet);
}