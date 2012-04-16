#include "Creature.h"
#include <iostream>

Creature::Creature()
{
	m_vel = sf::Vector2f(0, 0);
	canJump = false;

	goLeft = true;
	goRight = false;

	box.left = 0;
	box.top = 0;
	box.width = 16;
	box.height = 16;

	m_type = 20;
}

Creature::Creature(sf::Vector2f pos, int type, sf::Texture* nTex, bool left) : m_vel(0, 0), canJump(false), m_isDead(false)
{
	box.left = pos.x;
	box.top = pos.y;

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

	m_hpBar.setPosition(pos.x, pos.y - 8);
	m_hpBar.setSize(sf::Vector2f(16, 4));
	m_hpBar.setFillColor(sf::Color::Red);

	switch(m_type)
	{
		case 1:
			box.width = 16;
			box.height = 16;
			m_hpMax = 3;
			m_hp = 3;
			vel = 40;
			break;
		case 2:
			box.width = 16;
			box.height = 16;
			m_hpMax = 5;
			m_hp = 5;
			vel = 50;
			break;
		case 3:
			box.width = 16;
			box.height = 16;
			m_hpMax = 8;
			m_hp = 8;
			vel = 60;
			break;
		case 8:
			box.width = 32;
			box.height = 32;
			m_hpMax = 25;
			m_hp = 25;
			vel = 30;
			break;
	}
}

void Creature::UpdateSprite()
{
	m_sprite = m_anim->getSprite();
	m_sprite.setPosition(box.left, box.top);
	m_hpBar.setPosition(box.left, box.top - 8);
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

	if (playerAround && getPATime() > 500)
	{		
		if (m_type == 8)
			setVel(100);
	}
	else
	{
		if (m_type == 8)
			setVel(30);
	}

	//Update pozycji
	box.left += m_vel.x*(dt/1000.f);
	box.top += m_vel.y*(dt/1000.f);

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
	win->draw(m_sprite);
	if(m_hp/m_hpMax != 1) win->draw(m_hpBar);
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
			box.left = A.left - box.width;
			StopRight();
			GoLeft();
		}
		else if(m_vel.x < 0)
		{
			//Resetowanie pozycji do stycznej prawostronnie 
			box.left = A.left + A.width;
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
			box.top = A.top - box.height;
			m_vel.y = 0;
			canJump = true;
		}
		else if(m_vel.y < 0)
		{
			//Resetowanie pozycji do stycznej od dolu 
			box.top = A.top + A.height;
			m_vel.y = 0;
		}
	}
	else
	{
		if(m_vel.x > 0) //PRAWO
		{
			if(m_vel.y > 0)//DOL
			{
				float xD = box.left + box.width - A.left;
				float yD = box.top + box.height - A.top;
				
				/* std::cout << "DOL" << std::endl;
				std::cout << "-->W PRAWO<-- xD: " << xD << " ---- yD: " << yD << std::endl; */

				if(xD > yD)
				{
					//Resetowanie pozycji do stycznej od gory
					box.top = A.top - box.height;
					m_vel.y = 0;
					canJump = true;
				}
				else if (xD < yD+4)
				{
					box.left = A.left - box.width;
					StopRight();
					GoLeft();

					if (playerAround == true)
					{
						playerAround = false;
						PATimer.restart();
					}
				}
			}
			else if(m_vel.y < 0) //GORA
			{
				float xD = box.left + box.width - A.left;
				float yD = A.top + A.height - box.top;

				/* std::cout << "GORA" << std::endl;
				std::cout << "-->W PRAWO<-- xD: " << xD << " ---- yD: " << yD << std::endl; */

				if(xD > yD+4)
				{
					box.top = A.top + A.height;
					m_vel.y = 0;
				}
				else box.left = A.left - box.width;	
			}
		}
		else if(m_vel.x < 0) //Lewo
		{
			if(m_vel.y > 0) //Dol
			{
				float xD = A.left + A.width - box.left;
				float yD = box.top + box.height - A.top;
				
				

				if(xD+4 > yD)
				{
					//Resetowanie pozycji do stycznej od gory
					box.top = A.top - box.height;
					m_vel.y = 0;
					canJump = true;
				}
				else if (xD+4 < yD)
				{
					box.left = A.left + A.width;
					StopLeft();
					GoRight();

					if (playerAround == true)
					{
						playerAround = false;
						PATimer.restart();
					}
				}

			}
			else if(m_vel.y < 0)//Gora
			{
				float xD = A.left + A.width - box.left;
				float yD = A.top + A.height - box.top;
				
				/* std::cout << "GORA" << std::endl;
				std::cout << "-->W LEWO<-- xD: " << xD << " ---- yD: " << yD << std::endl; */

				if(xD > yD+3)
				{
					box.top = A.top + A.height;
					m_vel.y = 0;
				}
				else box.left = A.left + A.width;
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
	m_hpBar.setSize(sf::Vector2f(m_hp/m_hpMax*16, 4));

	//SMIERC
	if (m_hp <= 0) 
		Die();
}