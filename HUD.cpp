#include "HUD.h"

HUD::HUD(sf::Texture* hudTex)
{
	m_scoreText.SetCharacterSize(16);
	m_scoreText.SetColor(sf::Color::White);
	m_scoreText.SetPosition(8, 24);
	for(int i = 0; i < 10; i++)
	{
		m_hearthSpr[i].SetTexture(*hudTex);
		m_hearthSpr[i].SetTextureRect(sf::IntRect(0, 0, 16, 16));
		m_hearthSpr[i].SetPosition(8 + i*16, 8);
	}
}

void HUD::Update(int hp, int score)
{
	m_hp = hp;

	char buffer[8];
	itoa(score, buffer, 10);
	m_scoreText.SetString(buffer);
}

void HUD::Draw(sf::RenderWindow* wnd)
{
	for(int i = 0; i < m_hp; i++)
	{
		wnd->Draw(m_hearthSpr[i]);
		wnd->Draw(m_scoreText);
	}
}