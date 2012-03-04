#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f pos, sf::Texture* nTex) : m_vel(0, 0), canJump(false), goLeft(false), goRight(false), noclip(false)
{
	box.Left = pos.x;
	box.Top = pos.y;
	box.Width = 16;
	box.Height = 16;

	HP = 10;

	m_tex = nTex;
	m_anim = new Animation(m_tex, 3, 100);
}

void Player::UpdateShape()
{	
	m_sprite = m_anim->GetSprite();
	m_sprite.SetPosition(box.Left, box.Top);
}

void Player::Update(int dt)
{
	if(goLeft && goRight)
	{
		m_vel.x = 0;
		m_anim->Stop();
	}
	else if(goLeft)
	{
		m_vel.x = -150;
		m_anim->Play();
	}
	else if(goRight)
	{
		m_vel.x = 150;
		m_anim->Play();
	}
	else
	{
		m_vel.x = 0;
		m_anim->Stop();
	}

	//Update pozycji
	box.Left += m_vel.x*(dt/1000.f);
	box.Top += m_vel.y*(dt/1000.f);

	//Nalozenie grawitejszyn
	if(!noclip)
		m_vel.y += 800*(dt/1000.f);
	//Predkosc graniczna 300pix/s
	if(m_vel.y > 500) m_vel.y = 500;
	//Warunek spadania by Dani hehe
	if(m_vel.y > 10) LockJump();

	m_anim->Update();
	UpdateShape();
}

void Player::SolidCollision(sf::FloatRect A)
{
	//Jesli predkosc pionowa jest zerowa
	if(m_vel.y == 0)
	{
		//Jesli obiekt porusza sie w prawo
		if(m_vel.x > 0)
			//Resetowanie pozycji do stycznej lewostronnie
			box.Left = A.Left - box.Width;
		else if(m_vel.x < 0)
			//Resetowanie pozycji do stycznej prawostronnie 
			box.Left = A.Left + A.Width;
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
		if(m_vel.x > 0)//PRAWO
		{
			if(m_vel.y > 0)//DOL
			{
				float xD = box.Left + box.Width - A.Left;
				float yD = box.Top + box.Height - A.Top;

				if(xD > yD)
				{
					//Resetowanie pozycji do stycznej od gory
					box.Top = A.Top - box.Height;
					m_vel.y = 0;
					canJump = true;
				}
				else box.Left = A.Left - box.Width;
			}
			else if(m_vel.y < 0)//GORA
			{
				float xD = box.Left + box.Width - A.Left;
				float yD = A.Top + A.Height - box.Top;

				if(xD > yD+3)
				{
					box.Top = A.Top + A.Height;
					m_vel.y = 0;
				}
				else box.Left = A.Left - box.Width;	
			}
		}
		else if(m_vel.x < 0) //Lewo
		{
			if(m_vel.y > 0)//Dol
			{
				float xD = A.Left + A.Width - box.Left;
				float yD = box.Top + box.Height - A.Top;

				if(xD+3 > yD)
				{
					//Resetowanie pozycji do stycznej od gory
					box.Top = A.Top - box.Height;
					m_vel.y = 0;
					canJump = true;
				}
				else box.Left = A.Left + A.Width;
			}
			else if(m_vel.y < 0)//Gora
			{
				float xD = A.Left + A.Width - box.Left;
				float yD = A.Top + A.Height - box.Top;

				if(xD+3 > yD)
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

void Player::CreatureCollision(Creature* creature)
{

}

void Player::Jump()
{
	if(canJump)
	{
		m_vel.y = -350;
		LockJump();
	}
}