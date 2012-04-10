#pragma once
#include <SFML\Graphics.hpp>

class Tile
{
	private:
		sf::Vector2f m_pos;

		sf::Texture m_tex;
		sf::Sprite m_spr;

	public:
		Tile(sf::Vector2f nPos, sf::Texture newTexture);
		~Tile();

		void Render(sf::RenderWindow* win){win->Draw(m_spr);}

		void setPos(sf::Vector2f nPos);
};