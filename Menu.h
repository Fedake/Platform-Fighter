#pragma once
#include <SFML\Graphics.hpp>
#include "Button.h"

#include "ResourceManager.h"

#define NEW_GAME	0
#define CONTINUE	1
#define CREDITS		2
#define QUIT		3
#define RESUME		4
#define MAIN_MENU	5
#define MAIN_MENU2	6

class Menu
{
	private:
		sf::Sprite m_title;
		sf::Sprite m_credits;

		Button* m_buttons[7];
		sf::RectangleShape m_pauseShape;

		sf::Vector2f m_mPos;
		bool m_active;
		bool m_continue;

		int m_type;

		int m_screenWidth, m_screenHeight;
	public:
		Menu(int winW, int winH, ResourceManager* resMgr, bool nContinue);

		void SetMousePosition(sf::Vector2f nPos){m_mPos = nPos;}
		void Click(bool& quit, int& state);
		void Toggle() {if(m_type > 0)m_active = !m_active;}
		void OpenMenu() {if(m_type > 0)m_active = true;}
		void SetContinue(bool n){m_continue = n;}

		bool IsActive(){return m_active;}
		int GetType(){return m_type;}

		void Update();
		void Draw(sf::RenderWindow* win);
};