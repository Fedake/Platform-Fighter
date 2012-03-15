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

		void SetState(int nState){m_sprite.SetTextureRect(sf::IntRect(nState*220, m_type*70, 220, 70));}

		bool Contains(sf::Vector2f pos){return m_box.Contains(pos);}
		sf::Sprite GetSprite(){return m_sprite;}
};