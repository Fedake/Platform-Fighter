#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	sf::Image sheet;
	sheet.LoadFromFile("data/gfx/sheet.png");

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

	sheet.LoadFromFile("data/gfx/player.png");
	m_playerTex = new sf::Texture();
	m_playerTex->LoadFromImage(sheet);

	sheet.LoadFromFile("data/gfx/entSheet.png");

	for(int i = 1; i < TOTAL_ENTITIES; i++)
	{
		m_entTex[i] = new sf::Texture();
		m_entTex[i]->LoadFromImage(sheet, sf::IntRect(0, (i-1)*16, sheet.GetWidth(), 16));
	}

	sheet.LoadFromFile("data/gfx/bossSheet.png");

	for (int i = 1; i < 5; i++)
	{
		m_bossTex[i] = new sf::Texture();
		m_bossTex[i]->LoadFromImage(sheet, sf::IntRect(0, (i-1)*32, sheet.GetWidth(), 32));
	}

	sheet.LoadFromFile("data/gfx/hudSheet.png");
	m_hudTex = new sf::Texture();
	m_hudTex->LoadFromImage(sheet);

	sheet.LoadFromFile("data/gfx/guiSheet.png");
	m_guiTex = new sf::Texture();
	m_guiTex->LoadFromImage(sheet);

	sheet.LoadFromFile("data/gfx/title.png");
	m_titleTex = new sf::Texture();
	m_titleTex->LoadFromImage(sheet);

	sheet.LoadFromFile("data/gfx/bg.png");
	m_bgTex = new sf::Texture();
	m_bgTex->LoadFromImage(sheet);
}