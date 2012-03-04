#include "HUD.h"

HUD::HUD(sf::Texture* hudTex)
{
	for(int i = 0; i < 10; i++)
	{
		m_hearthSpr[i].SetTexture(*hudTex);
		m_hearthSpr[i].SetTextureRect(sf::IntRect(0, 0, 16, 16));
		m_hearthSpr[i].SetPosition(8 + i*16, 8);
	}
}

void HUD::Draw(sf::RenderWindow* wnd)
{
	for(int i = 0; i < m_hp; i++)
	{
		wnd->Draw(m_hearthSpr[i]);
	}
}