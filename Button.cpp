#include "Button.h"

Button::Button(int nType, sf::Texture* nTex, sf::Vector2f nPos, sf::Vector2f nSize) : m_type(nType), m_box(nPos, nSize), m_state(0)
{
	m_sprite.setTexture(*nTex);
	m_sprite.setTextureRect(sf::IntRect(0, m_type*70, 220, 70));

	m_sprite.setPosition(nPos);
}