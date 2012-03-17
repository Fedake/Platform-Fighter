#include "Menu.h"

Menu::Menu(int winW, int winH, sf::Texture* nTitleTex, sf::Texture* nTex) : m_active(true), m_type(0), m_screenWidth(winW),
																			m_screenHeight(winH)
{
	m_title.SetTexture(*nTitleTex);

	for(int i = 0; i < 3; i++)
	{
		m_buttons[i] = new Button(i, nTex, sf::Vector2f(280, 200+i*150), sf::Vector2f(220, 70));
	}

	for(int i = 3; i < 5; i++)
	{
		m_buttons[i] = new Button(i, nTex, sf::Vector2f(280, 200+(i-3)*150), sf::Vector2f(220, 70));
	}

	m_pauseShape.SetFillColor(sf::Color(0, 0, 0, 192));
	m_pauseShape.SetSize(sf::Vector2f(static_cast<float>(m_screenWidth), static_cast<float>(m_screenHeight)));
}

void Menu::Click(bool& quit, int& state)
{
	if(m_type == 0)
	{
		for(int i = 0; i < 3; i++)
		{
			if(m_buttons[i]->Contains(m_mPos)) 
			{
				if(i == 0) {state = 1; m_type = 1; m_active = false;}
				if(i == 2) quit = true;
			}
		}
	}

	if(m_type == 1)
	{
		for(int i = 3; i < 5; i++)
		{
			if(m_buttons[i]->Contains(m_mPos)) 
			{
				if(i == 3) m_active = false;
				if(i == 4) m_type = 0;
			}
		}
	}
}

void Menu::Update()
{
	if(m_type == 0)
	{
		for(int i = 0; i < 3; i++)
		{
			if(m_buttons[i]->Contains(m_mPos)) 
			{
				if(i != 1) m_buttons[i]->SetState(1);
			}
			else m_buttons[i]->SetState(0);
		}
	}

	if(m_type == 1)
	{
		for(int i = 3; i < 5; i++)
		{
			if(m_buttons[i]->Contains(m_mPos)) 
			{
				m_buttons[i]->SetState(1);
			}
			else m_buttons[i]->SetState(0);
		}
	}
}

void Menu::Draw(sf::RenderWindow* win)
{
	if(m_type == 0)
	{
		win->Draw(m_title);
		for(int i = 0; i < 3; i++)
		{
			win->Draw(m_buttons[i]->GetSprite());
		}
	}

	if(m_type == 1)
	{
		win->Draw(m_pauseShape);
		for(int i = 3; i < 5; i++)
		{
			win->Draw(m_buttons[i]->GetSprite());
		}
	}
}