#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f pos, sf::Texture* nTex, int hp, sf::Clock ht) : m_vel(0, 0), canJump(false), goLeft(false), goRight(false), goUp(false),
															  goDown(false), m_ghost(false)
{
	box.Left = pos.x;
	box.Top = pos.y;
	box.Width = 16;
	box.Height = 16;

	HP = hp;
	coins = 0;
	
	hitTime.Restart();
	hitTime = ht;

	m_anim = new Animation(nTex, 2, 100);
}

void Player::UpdateSprite()
{	
	m_sprite = m_anim->GetSprite();
	m_sprite.SetPosition(box.Left, box.Top);
}

void Player::Update(int dt)
{
	if(goLeft && goRight)
	{
		m_vel.x = 0;
		if(!m_ghost) m_anim->Stop();
	}
	else if(goLeft)
	{
		m_vel.x = -150;
		if(!m_ghost) m_anim->PlayLeft();
	}
	else if(goRight)
	{
		m_vel.x = 150;
		if(!m_ghost) m_anim->PlayRight();
	}
	else
	{
		m_vel.x = 0;
		if(!m_ghost) m_anim->Stop();
	}

	if(m_ghost)
	{
		if(goUp && goDown) m_vel.y = 0;
		else if(goUp) m_vel.y = -150;
		else if(goDown) m_vel.y = 150;
		else m_vel.y = 0;
	}

	//Update pozycji
	box.Left += m_vel.x*(dt/1000.f);
	box.Top += m_vel.y*(dt/1000.f);

	//Nalozenie grawitejszyn
	if(!m_ghost)
		m_vel.y += 800*(dt/1000.f);
	//Predkosc graniczna 300pix/s
	if(m_vel.y > 500) m_vel.y = 500;
	//Warunek spadania by Dani hehe
	if(m_vel.y > 10) LockJump();

	m_anim->Update();
	UpdateSprite();
}

void Player::CheckCreaturesAround(Creature* creature)
{
	if ((creature->GetBox().Top < box.Top+box.Height+10) && (creature->GetBox().Top+creature->GetBox().Height > box.Top-10) &&
			PHTime.GetElapsedTime().AsMilliseconds() > 500)
	{
		creature->PlayerAround();

		if (creature->GetBox().Left < box.Left && creature->GetBox().Left+creature->GetBox().Width+ (creature->GetType() == 8 ? 256 : 64) > box.Left && creature->GetPATime() > 500)
		{
			creature->StopLeft();
			creature->GoRight();
		}
		else if (creature->GetBox().Left > box.Left && creature->GetBox().Left < box.Left+box.Width+ (creature->GetType() == 8 ? 256 : 64) && creature->GetPATime() > 500)
		{
			creature->StopRight();
			creature->GoLeft();
		}
		else
		{
			creature->PlayerNotAround();
		}
	}
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

				if(xD > yD+5)
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

void Player::CreatureCollision(Creature* creature)
{
	if (hitTime.GetElapsedTime().AsSeconds() > 3)
	{
		switch(creature->GetType())
		{
		case 1:
			Hurt(1);
			std::cout << "Player stracil 1 serduszko" << std::endl;
			hitTime.Restart();
			break;
		case 2:
			Hurt(2);
			std::cout << "Player stracil 2 serduszka" << std::endl;
			hitTime.Restart();
			break;
		case 3:
			Hurt(3);
			std::cout << "Player stracil 3 serduszka" << std::endl;
			hitTime.Restart();
			break;
		case 8:
			Hurt(5);
			std::cout << "Player stracil 5 serduszek" << std::endl;
			hitTime.Restart();
			break;
		default: 
			break;
		}
		if (HP <= 0)
			std::cout << "Player padl" << std::endl;
	}
	PHTime.Restart();
}

int Player::EntityCollision(Entity* entity)
{
	switch(entity->GetType())
	{
		case 11:
			if (!(GetHP() >= 10))
			{
				std::cout << "Player zdobyl serduszko" << std::endl;
				Heal(1);
				return 0;
			}
			else return 1;
		case 12:
			std::cout << "Player zdobyl pienionszka" << std::endl;
			coins += 10;
			return 0;
		case 13:
			std::cout << "Player zdobyl pienionszka" << std::endl;
			coins += 20;
			return 0;
		case 14:
			std::cout << "Player zdobyl pienionszka" << std::endl;
			coins += 50;
			return 0;
		case 15:
			std::cout << "Nastepny level." << std::endl;
			return 2;
		default: 
			return 1;
	}
}
void Player::ToggleGhost()
{
	m_ghost = !m_ghost;
	
	std::cout << "Ghost mode ";
	if(m_ghost) std::cout << "enabled\n";
	else		std::cout << "disabled\n";
}

void Player::Jump()
{
	if(canJump)
	{
		m_vel.y = -350;
		LockJump();
	}

	goUp = true;
}