#pragma once
#include <SFML\Graphics.hpp>
#include "Button.h"

class Menu
{
	private:
		sf::Sprite m_title;
		Button* m_buttons[3];
		sf::Vector2f m_mPos;

		bool m_clicked;
		bool m_active;

	public:
		Menu(sf::Texture* nTitleTex, sf::Texture* nGuiTex);

		void SetMousePosition(sf::Vector2f nPos){m_mPos = nPos;}
		void Click() { m_clicked = true; }
		void Unclick() { m_clicked = false; }
		void Toggle() {m_active = !m_active;}

		bool IsActive(){return m_active;}

		void Update(bool& quit, int& state);
		void Draw(sf::RenderWindow* win);
};