#include "Tile.h"

Tile::Tile(sf::Vector2f nPos, sf::Texture tex) : m_pos(nPos)
{	
	m_tex = tex;
	m_spr.setTexture(m_tex);
	m_spr.setPosition(m_pos);

}

void Tile::setPos(sf::Vector2f nPos)
{
	m_pos = nPos;
	m_spr.setPosition(nPos);
}