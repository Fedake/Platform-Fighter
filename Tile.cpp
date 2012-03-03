#include "Tile.h"

Tile::Tile(sf::Vector2f nPos, sf::Texture tex) : m_pos(nPos)
{	
	m_tex = tex;
	m_spr.SetTexture(m_tex);
	m_spr.SetPosition(m_pos);

}

void Tile::setPos(sf::Vector2f nPos)
{
	m_pos = nPos;
	m_spr.SetPosition(nPos);
}