#include "Menu.h"
#include <iostream>

Menu::Menu(int winW, int winH, ResourceManager* resMgr, bool nContinue)
	 : m_active(true), m_type(0), m_screenWidth(winW),	m_screenHeight(winH), m_continue(nContinue)
{
	m_title.SetTexture(*resMgr->GetTitleTexture());
	m_credits.SetTexture(*resMgr->GetCreditsTexture());

	sf::Texture* nTex = resMgr->GetGuiTexture(); 
	m_buttons[NEW_GAME] = new Button(NEW_GAME, nTex, sf::Vector2f(280, 140), sf::Vector2f(220, 70));
	m_buttons[CONTINUE] = new Button(CONTINUE, nTex, sf::Vector2f(280, 260), sf::Vector2f(220, 70));
	m_buttons[CREDITS] = new Button(CREDITS, nTex, sf::Vector2f(280, 380), sf::Vector2f(220, 70));
	m_buttons[QUIT] = new Button(QUIT, nTex, sf::Vector2f(280, 500), sf::Vector2f(220, 70));

	m_buttons[RESUME] = new Button(RESUME, nTex, sf::Vector2f(280, 200), sf::Vector2f(220, 70));
	m_buttons[MAIN_MENU] = new Button(MAIN_MENU, nTex, sf::Vector2f(280, 350), sf::Vector2f(220, 70));

	m_buttons[MAIN_MENU2] = new Button(MAIN_MENU, nTex, sf::Vector2f(535, 500), sf::Vector2f(220, 70));

	m_buttons[MAIN_MENU3] = new Button(MAIN_MENU, nTex, sf::Vector2f(280, 500), sf::Vector2f(220, 70));

	m_pauseShape.SetFillColor(sf::Color(0, 0, 0, 192));
	m_pauseShape.SetSize(sf::Vector2f(static_cast<float>(m_screenWidth), static_cast<float>(m_screenHeight)));
}

void Menu::Click(bool& quit, int& state)
{
	if(m_type == 0)
	{
		for(int i = 0; i < 4; i++)
		{
			if(m_buttons[i]->Contains(m_mPos)) 
			{
				if(i == NEW_GAME) {m_type = 1; m_active = false; state = 1;}
				if(i == CONTINUE && m_continue) {m_type = 1; m_active = false; state = 2;}
				if(i == CREDITS) m_type = 2;
				if(i == QUIT) quit = true;
			}
		}
	}

	else if(m_type == 1)
	{
		for(int i = 4; i < 6; i++)
		{
			if(m_buttons[i]->Contains(m_mPos)) 
			{
				if(i == RESUME) m_active = false;
				if(i == MAIN_MENU) m_type = 0;
			}
		}
	}

	else if(m_type == 2)
	{
		if(m_buttons[MAIN_MENU2]->Contains(m_mPos)) m_type = 0;
	}

	else if(m_type == 3)
	{
		if(m_buttons[MAIN_MENU3]->Contains(m_mPos)) m_type = 0;
	}
}

void Menu::Die(int score)
{
	m_type = 3;
	m_active = true;

	char tmp[8];
	itoa(score, tmp, 10);

	std::string deadStr = "GAME OVER\n\nScore: " + (std::string)tmp;

	m_deadText.SetString(deadStr);
	m_deadText.SetPosition(290, 300);
}

void Menu::Update()
{
	if(m_type == 0)
	{
		for(int i = 0; i < 4; i++)
		{
			if(m_buttons[i]->Contains(m_mPos)) 
			{
				if(i != CONTINUE) m_buttons[i]->SetState(1);
				else if(m_continue) m_buttons[i]->SetState(1);
			}
			else m_buttons[i]->SetState(0);
		}
	}

	if(m_type == 1)
	{
		for(int i = 4; i < 6; i++)
		{
			if(m_buttons[i]->Contains(m_mPos)) 
			{
				m_buttons[i]->SetState(1);
			}
			else m_buttons[i]->SetState(0);
		}
	}

	if(m_type == 2)
	{
		if(m_buttons[MAIN_MENU2]->Contains(m_mPos)) 
		{
			m_buttons[MAIN_MENU2]->SetState(1);
		}
		else m_buttons[MAIN_MENU2]->SetState(0);
	}

	if(m_type == 3)
	{
		if(m_buttons[MAIN_MENU3]->Contains(m_mPos)) 
		{
			m_buttons[MAIN_MENU3]->SetState(1);
		}
		else m_buttons[MAIN_MENU3]->SetState(0);
	}
}

void Menu::Draw(sf::RenderWindow* win)
{
	if(m_type == 0)
	{
		win->Draw(m_title);
		for(int i = 0; i < 4; i++)
		{
			win->Draw(m_buttons[i]->GetSprite());
		}
	}

	if(m_type == 1)
	{
		win->Draw(m_pauseShape);
		for(int i = 4; i < 6; i++)
		{
			win->Draw(m_buttons[i]->GetSprite());
		}
	}

	if(m_type == 2)
	{
		win->Draw(m_credits);
		win->Draw(m_buttons[MAIN_MENU2]->GetSprite());
	}

	if(m_type == 3)
	{
		win->Draw(m_pauseShape);
		win->Draw(m_deadText);
		win->Draw(m_buttons[MAIN_MENU3]->GetSprite());
	}
}