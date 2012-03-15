#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"

class Entity
{
	private:
		//Pozycja
		sf::FloatRect box;
		Animation* m_anim;
		sf::Sprite m_sprite;

		//Predkosc
		sf::Vector2f m_vel;

		int m_type;

		bool isTaken;

	public:
		// Konstruktor
		Entity();
		// To te¿
		Entity(sf::Vector2f pos, int type, sf::Texture* nTex);

		void UpdateSprite();

		sf::FloatRect GetBox() { return box; }
		sf::Sprite GetSprite() {return m_sprite;}
		int GetType() { return m_type; }
};