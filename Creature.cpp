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

	shape.SetFillColor(sf::Color::Black);
}

Creature::Creature(sf::Vector2f pos, int type) : m_vel(0, 0), canJump(false), goLeft(true), goRight(false)
{
	box.Left = pos.x;
	box.Top = pos.y;
	box.Width = 16;
	box.Height = 16;

	m_type = type;

	switch(m_type)
	{
		case 1:
			shape.SetFillColor(sf::Color::Green);
			HP = 10;
			break;
		case 2:
			shape.SetFillColor(sf::Color::Blue);
			HP = 20;
			break;
		case 3:
			shape.SetFillColor(sf::Color::Red);
			HP = 30;
			break;
		default:
			shape.SetFillColor(sf::Color::Black);;
	}
}

void Creature::UpdateShape()
{
	shape.SetPosition(box.Left, box.Top);
	shape.SetSize(sf::Vector2f(box.Width, box.Height));
}

void Creature::Update(int dt)
{
	if(goLeft && goRight)  m_vel.x = 0;
	else if(goLeft) m_vel.x = -150;
	else if(goRight) m_vel.x = 150;
	else m_vel.x = 0;

	//Update pozycji
	box.Left += m_vel.x*(dt/1000.f);
	box.Top += m_vel.y*(dt/1000.f);

	//Nalozenie grawitejszyn
	m_vel.y += 800*(dt/1000.f);
	//Predkosc graniczna 300pix/s
	if(m_vel.y > 500) m_vel.y = 500;
	//Warunek spadania by Dani hehe
	if(m_vel.y > 10) LockJump();
	//SMIERC
	if (HP <= 0) Die();

	UpdateShape();

	// std::cout << m_vel.y << std::endl;
	// std::cout << m_vel.y << " ----- " << m_vel.x <<  std::endl;
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
					/* std::cout << "DOL" << std::endl;
					std::cout << "-->W LEWO<-- xD: " << xD << " ---- yD: " << yD << std::endl; */
					StopLeft();
					GoRight();
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
	UpdateShape();
}


void Creature::Jump()
{
	if(canJump)
	{
		m_vel.y = -150;
		LockJump();
	}
}