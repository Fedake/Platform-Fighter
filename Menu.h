#pragma once
#include <SFML\Graphics.hpp>
#include "Button.h"

class Menu
{
	private:
		sf::Sprite m_title;
		Button* m_buttons[5];
		sf::RectangleShape m_pauseShape;

		sf::Vector2f m_mPos;
		bool m_active;

		int m_type;

		int m_screenWidth, m_screenHeight;
	public:
		Menu(int winW, int winH, sf::Texture* nTitleTex, sf::Texture* nGuiTex);

		void SetMousePosition(sf::Vector2f nPos){m_mPos = nPos;}
		void Click(bool& quit, int& state);
		void Toggle() {if(m_type > 0)m_active = !m_active;}
		void OpenMenu() {if(m_type > 0)m_active = true;}

		bool IsActive(){return m_active;}
		int GetType(){return m_type;}

		void Update();
		void Draw(sf::RenderWindow* win);
};