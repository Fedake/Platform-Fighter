#include "Menu.h"

Menu::Menu(sf::Texture* nTitleTex, sf::Texture* nTex) : m_clicked(false), m_active(true)
{
	m_title.SetTexture(*nTitleTex);

	for(int i = 0; i < 3; i++)
	{
		m_buttons[i] = new Button(i, nTex, sf::Vector2f(280, 200+i*150), sf::Vector2f(220, 70));
	}
}

void Menu::Update(bool& quit, int& state)
{
	for(int i = 0; i < 3; i++)
	{
		if(m_buttons[i]->Contains(m_mPos)) 
		{
			m_buttons[i]->SetState(1);
			if(m_clicked)
			{
				m_clicked = false;
				if(i == 0) state = 1; m_active = false;
				if(i == 2) quit = true;
			}
		}
		else m_buttons[i]->SetState(0);
	}
}

void Menu::Draw(sf::RenderWindow* win)
{
	win->Draw(m_title);

	for(int i = 0; i < 3; i++)
	{
		win->Draw(m_buttons[i]->GetSprite());
	}
}