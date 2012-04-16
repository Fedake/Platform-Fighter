#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	sf::Image sheet;
	sheet.loadFromFile("data/gfx/sheet.png");

	int x = 0, y = 0;
	for(int i = 0; i < TOTAL_SPRITES; i++)
	{
		m_tileTex[i] = new sf::Texture();
		m_tileTex[i]->loadFromImage(sheet, sf::IntRect(x, y, 16, 16));

		x += 16;
		
		if(x >= 128)
		{
			x = 0;
			y += 16;
		}
	}

	sheet.loadFromFile("data/gfx/player.png");
	m_playerTex = new sf::Texture();
	m_playerTex->loadFromImage(sheet);

	sheet.loadFromFile("data/gfx/entSheet.png");

	for(int i = 1; i < TOTAL_ENTITIES; i++)
	{
		m_entTex[i] = new sf::Texture();
		m_entTex[i]->loadFromImage(sheet, sf::IntRect(0, (i-1)*16, sheet.getSize().x, 16));
	}

	sheet.loadFromFile("data/gfx/bossSheet.png");

	for (int i = 1; i < 2; i++)
	{
		m_bossTex[i] = new sf::Texture();
		m_bossTex[i]->loadFromImage(sheet, sf::IntRect(0, (i-1)*32, sheet.getSize().x, 32));
	}

	sheet.loadFromFile("data/gfx/hudSheet.png");
	m_hudTex = new sf::Texture();
	m_hudTex->loadFromImage(sheet);

	sheet.loadFromFile("data/gfx/guisheet.png");
	m_guiTex = new sf::Texture();
	m_guiTex->loadFromImage(sheet);

	sheet.loadFromFile("data/gfx/title.png");
	m_titleTex = new sf::Texture();
	m_titleTex->loadFromImage(sheet);

	sheet.loadFromFile("data/gfx/bg.png");
	m_bgTex = new sf::Texture();
	m_bgTex->loadFromImage(sheet);

	sheet.loadFromFile("data/gfx/credits.png");
	m_creditsTex = new sf::Texture();
	m_creditsTex->loadFromImage(sheet);
}