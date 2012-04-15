#include "Creature.h"
#include <iostream>

Creature::Creature()
{
	m_vel = sf::Vector2f(0, 0);
	canJump = false;

	goLeft = true;
	goRight = false;

	box.Left = 0;
	box.Top = 0;
	box.Width = 16;
	box.Height = 16;

	m_type = 20;
}

Creature::Creature(sf::Vector2f pos, int type, sf::Texture* nTex, bool left) : m_vel(0, 0), canJump(false), isDead(false)
{
	box.Left = pos.x;
	box.Top = pos.y;

	m_type = type;

	playerAround = false;

	if (type == 8)
		m_anim = new Animation(nTex, 2, 200, 32, 32);
	else
		m_anim = new Animation(nTex, 2, 300);

	if (left == true)
	{
		StopRight();
		GoLeft();
	}
	else
	{
		StopLeft();
		GoRight();
	}

	m_hpBar.SetPosition(pos.x, pos.y - 8);
	m_hpBar.SetSize(sf::Vector2f(16, 4));
	m_hpBar.SetFillColor(sf::Color::Red);

	switch(m_type)
	{
		case 1:
			box.Width = 16;
			box.Height = 16;
			m_hpMax = 3;
			m_hp = 3;
			vel = 40;
			break;
		case 2:
			box.Width = 16;
			box.Height = 16;
			m_hpMax = 5;
			m_hp = 5;
			vel = 50;
			break;
		case 3:
			box.Width = 16;
			box.Height = 16;
			m_hpMax = 8;
			m_hp = 8;
			vel = 60;
			break;
		case 8:
			box.Width = 32;
			box.Height = 32;
			m_hpMax = 25;
			m_hp = 25;
			vel = 30;
			break;
	}
}

void Creature::UpdateSprite()
{
	m_sprite = m_anim->GetSprite();
	m_sprite.SetPosition(box.Left, box.Top);
	m_hpBar.SetPosition(box.Left, box.Top - 8);
}

void Creature::Update(int dt)
{
	if(goLeft && goRight)
	{
		m_vel.x = 0;
		m_anim->Stop();
	}
	else if(goLeft)
	{
		m_vel.x = -vel;
		m_anim->PlayLeft();
	}
	else if(goRight)
	{
		m_vel.x = vel;
		m_anim->PlayRight();
	}
	else
	{
		m_vel.x = 0;
		m_anim->Stop();
	}

	if (playerAround && GetPATime() > 500)
	{		
		if (m_type == 8)
			SetVel(100);
	}
	else
	{
		if (m_type == 8)
			SetVel(30);
	}

	//Update pozycji
	box.Left += m_vel.x*(dt/1000.f);
	box.Top += m_vel.y*(dt/1000.f);

	//Nalozenie grawitejszyn
	m_vel.y += 800*(dt/1000.f);
	//Predkosc graniczna 300pix/s
	if(m_vel.y > 500) m_vel.y = 500;
	//Warunek spadania by Dani hehe
	if(m_vel.y > 10) LockJump();

	m_anim->Update();

	UpdateSprite();
}

void Creature::Render(sf::RenderWindow* win)
{
	win->Draw(m_sprite);
	if(m_hp/m_hpMax != 1) win->Draw(m_hpBar);
}

void Creature::SolidCollision(sf::FloatRect A)
{
	//Jesli predkosc pionowa jest zerowa
	if(m_vel.y == 0)
	{
		//Jesli obiekt porusza sie w prawo
		if(m_vel.x > 0)
		{
			//Resetowanie pozycji do stycznej lewostronnie
			box.Left = A.Left - box.Width;
			StopRight();
			GoLeft();
		}
		else if(m_vel.x < 0)
		{
			//Resetowanie pozycji do stycznej prawostronnie 
			box.Left = A.Left + A.Width;
			StopLeft();
			GoRight();
		}
	}
	else if(m_vel.x == 0)
	{
		//Jesli obiekt porusza sie w dol
		if(m_vel.y > 0)
		{
			//Resetowanie pozycji do stycznej od gory
			box.Top = A.Top - box.Height;
			m_vel.y = 0;
			canJump = true;
		}
		else if(m_vel.y < 0)
		{
			//Resetowanie pozycji do stycznej od dolu 
			box.Top = A.Top + A.Height;
			m_vel.y = 0;
		}
	}
	else
	{
		if(m_vel.x > 0) //PRAWO
		{
			if(m_vel.y > 0)//DOL
			{
				float xD = box.Left + box.Width - A.Left;
				float yD = box.Top + box.Height - A.Top;
				
				/* std::cout << "DOL" << std::endl;
				std::cout << "-->W PRAWO<-- xD: " << xD << " ---- yD: " << yD << std::endl; */

				if(xD > yD)
				{
					//Resetowanie pozycji do stycznej od gory
					box.Top = A.Top - box.Height;
					m_vel.y = 0;
					canJump = true;
				}
				else if (xD < yD+4)
				{
					box.Left = A.Left - box.Width;
					StopRight();
					GoLeft();

					if (playerAround == true)
					{
						playerAround = false;
						PATimer.Restart();
					}
				}
			}
			else if(m_vel.y < 0) //GORA
			{
				float xD = box.Left + box.Width - A.Left;
				float yD = A.Top + A.Height - box.Top;

				/* std::cout << "GORA" << std::endl;
				std::cout << "-->W PRAWO<-- xD: " << xD << " ---- yD: " << yD << std::endl; */

				if(xD > yD+4)
				{
					box.Top = A.Top + A.Height;
					m_vel.y = 0;
				}
				else box.Left = A.Left - box.Width;	
			}
		}
		else if(m_vel.x < 0) //Lewo
		{
			if(m_vel.y > 0) //Dol
			{
				float xD = A.Left + A.Width - box.Left;
				float yD = box.Top + box.Height - A.Top;
				
				

				if(xD+4 > yD)
				{
					//Resetowanie pozycji do stycznej od gory
					box.Top = A.Top - box.Height;
					m_vel.y = 0;
					canJump = true;
				}
				else if (xD+4 < yD)
				{
					box.Left = A.Left + A.Width;
					StopLeft();
					GoRight();

					if (playerAround == true)
					{
						playerAround = false;
						PATimer.Restart();
					}
				}

			}
			else if(m_vel.y < 0)//Gora
			{
				float xD = A.Left + A.Width - box.Left;
				float yD = A.Top + A.Height - box.Top;
				
				/* std::cout << "GORA" << std::endl;
				std::cout << "-->W LEWO<-- xD: " << xD << " ---- yD: " << yD << std::endl; */

				if(xD > yD+3)
				{
					box.Top = A.Top + A.Height;
					m_vel.y = 0;
				}
				else box.Left = A.Left + A.Width;
			}
		}
	}
	UpdateSprite();
}


void Creature::Jump()
{
	if(canJump)
	{
		m_vel.y = -150;
		LockJump();
	}
}

void Creature::Hurt()
{
	m_hp -= 1;
	m_hpBar.SetSize(sf::Vector2f(m_hp/m_hpMax*16, 4));

	//SMIERC
	if (m_hp <= 0) 
		Die();
}