#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"

class Camera
{
	private:
		sf::Vector2i m_winSize;
		sf::Vector2i m_lvlSize;

		sf::Vector2f m_vPos;
		

		sf::View view;
	public:
		Camera(sf::Vector2i winSize, sf::Vector2i lvlSize) : m_winSize(winSize), m_lvlSize(lvlSize){}

		void set(sf::FloatRect centerRect);

		sf::View getView(){return view;}
		sf::Vector2f getPos() {return m_vPos;}
};