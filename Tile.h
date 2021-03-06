#pragma once
#include <SFML\Graphics.hpp>

class Tile
{
	private:
		sf::Vector2f m_pos;
		sf::Sprite m_spr;

	public:
		Tile(sf::Vector2f nPos, sf::Texture* newTexture);

		void Render(sf::RenderWindow* win){win->draw(m_spr);}

		void setPos(sf::Vector2f nPos);
};