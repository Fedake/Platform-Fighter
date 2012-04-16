#pragma once
#include <SFML\Graphics.hpp>

class Button
{
	private:
		sf::FloatRect m_box;
		sf::Sprite m_sprite;

		int m_type;
		int m_state;
	public:
		Button(int nType, sf::Texture* nTex, sf::Vector2f nPos, sf::Vector2f nSize);

		void setState(int nState){m_sprite.setTextureRect(sf::IntRect(nState*220, m_type*70, 220, 70));}

		bool Contains(sf::Vector2f pos){return m_box.contains(pos);}
		sf::Sprite getSprite(){return m_sprite;}
};