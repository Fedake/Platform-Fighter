#include "HUD.h"

HUD::HUD(sf::Texture* hudTex)
{
	m_scoreText.setCharacterSize(16);
	m_scoreText.setColor(sf::Color::White);
	m_scoreText.setPosition(8, 24);
	for(int i = 0; i < 10; i++)
	{
		m_hearthSpr[i].setTexture(*hudTex);
		m_hearthSpr[i].setTextureRect(sf::IntRect(0, 0, 16, 16));
		m_hearthSpr[i].setPosition(8 + i*16, 8);
	}
}

void HUD::Update(int hp, int score)
{
	m_hp = hp;

	char buffer[8];
	itoa(score, buffer, 10);
	m_scoreText.setString(buffer);
}

void HUD::draw(sf::RenderWindow* wnd)
{
	for(int i = 0; i < m_hp; i++)
	{
		wnd->draw(m_hearthSpr[i]);
		wnd->draw(m_scoreText);
	}
}