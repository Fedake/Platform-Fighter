#pragma once
#include <SFML\Graphics.hpp>
#include "Button.h"

class Menu
{
	private:
		Button* m_buttons[3];
		sf::Vector2f m_mPos;

		bool m_clicked;

	public:
		Menu(sf::Texture* nGuiTex);

		void SetMousePosition(sf::Vector2f nPos){m_mPos = nPos;}
		void Click() { m_clicked = true; }
		void Unclick() { m_clicked = false; }

		int Update();
		void Draw(sf::RenderWindow* win);
};