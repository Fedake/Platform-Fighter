#include "Menu.h"

Menu::Menu(sf::Texture* nTex) : m_clicked(false)
{
	for(int i = 0; i < 3; i++)
	{
		m_buttons[i] = new Button(i, nTex, sf::Vector2f(280, i*75), sf::Vector2f(220, 70));
	}
}

int Menu::Update()
{
	for(int i = 0; i < 3; i++)
	{
		if(m_buttons[i]->Contains(m_mPos)) 
		{
			m_buttons[i]->SetState(1);
			if(m_clicked)
			{
				m_clicked = false;
				if(i == 0) return 1;
				if(i == 2) return -1;
			}
		}
		else m_buttons[i]->SetState(0);
	}

	return 0;
}

void Menu::Draw(sf::RenderWindow* win)
{
	for(int i = 0; i < 3; i++)
	{
		win->Draw(m_buttons[i]->GetSprite());
	}
}