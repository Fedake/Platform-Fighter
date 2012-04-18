#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f pos, sf::Texture* nTex, int hp, sf::Clock ht) : m_vel(0, 0), canJump(false), goLeft(false), goRight(false), goUp(false),
															  goDown(false), m_ghost(false)
{
	box.left = pos.x;
	box.top = pos.y;
	box.width = 16;
	box.height = 16;

	HP = hp;
	coins = 0;
	
	m_xVel = 150;

	hitTime.restart();
	hitTime = ht;

	m_anim = new Animation(nTex, 2, 100);
}

void Player::UpdateSprite()
{	
	m_sprite = m_anim->getSprite();
	m_sprite.setPosition(box.left, box.top);
}

void Player::Update(int dt, Map* map)
{
	if(goLeft && goRight)
	{
		m_vel.x = 0;
		if(!m_ghost) m_anim->Stop();
	}
	else if(goLeft)
	{
		m_vel.x = -m_xVel;
		if(!m_ghost) m_anim->PlayLeft();
	}
	else if(goRight)
	{
		m_vel.x = m_xVel;
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
	box.left += m_vel.x*(dt/1000.f);
	for(int j = static_cast<int>(box.top)/16 - 1; j < box.top/16 + 1; j++)
	{
		for(int i = static_cast<int>(box.left)/16 - 1; i < box.left/16 + 1; i++)
		{
			if(map->isSolid(i, j))
			{
				if (box.intersects(map->getBox(static_cast<float>(i), static_cast<float>(j))))
				{
					if (m_vel.x < 0)
					{
						box.left = map->getBox(static_cast<float>(i), static_cast<float>(j)).left + map->getBox(static_cast<float>(i), static_cast<float>(j)).width;
					}

					if (m_vel.x > 0)
					{
						box.left = map->getBox(static_cast<float>(i), static_cast<float>(j)).left - box.width;
					}
				}
			}
		}
	}

	box.top += m_vel.y*(dt/1000.f);
	for(int j = static_cast<int>(box.top)/16 - 1; j < box.top/16 + 1; j++)
	{
		for(int i = static_cast<int>(box.left)/16 - 1; i < box.left/16 + 1; i++)
		{
			if(map->isSolid(i, j))
			{
				if (box.intersects(map->getBox(static_cast<float>(i), static_cast<float>(j))))
				{
					box.top -= m_vel.y * (dt / 1000.f);
					if (m_vel.y < 0)
					{
						box.top = map->getBox(static_cast<float>(i), static_cast<float>(j)).top + map->getBox(static_cast<float>(i), static_cast<float>(j)).height;
						m_vel.y = 0;
					}
					if (m_vel.y > 0)
					{
						box.top = map->getBox(static_cast<float>(i), static_cast<float>(j)).top - box.height;
						m_vel.y = 0;
						canJump = true;
					}
				}
			}
		}
	}

	// Predkosc 150pix/s
	if (speedBoost && SBTime.getElapsedTime().asSeconds() > 15)
	{
		m_xVel = 150;
		speedBoost = false;
	}

	//Nalozenie grawitejszyn
	if(!m_ghost)
		m_vel.y += 800*(dt/1000.f);
	//Predkosc graniczna 300pix/s
	if(m_vel.y > 500) m_vel.y = 500;
	//Warunek spadania by Dani hehe
	if(m_vel.y > 20) LockJump();

	m_anim->Update();
	UpdateSprite();
}

void Player::CheckCreaturesAround(Creature* creature)
{
	if ((creature->getBox().top < box.top+box.height+10) && (creature->getBox().top+creature->getBox().height > box.top-10) &&
			PHTime.getElapsedTime().asMilliseconds() > 500)
	{
		creature->PlayerAround();

		if (creature->getBox().left < box.left && creature->getBox().left+creature->getBox().width+ (creature->getType() == 8 ? 256 : 64) > box.left && creature->getPATime() > 500)
		{
			creature->StopLeft();
			creature->GoRight();
		}
		else if (creature->getBox().left > box.left && creature->getBox().left < box.left+box.width+ (creature->getType() == 8 ? 256 : 64) && creature->getPATime() > 500)
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
	
}

void Player::CreatureCollision(Creature* creature)
{
	if (hitTime.getElapsedTime().asSeconds() > 3)
	{
		switch(creature->getType())
		{
		case 1:
			Hurt(1);
			std::cout << "Player stracil 1 serduszko" << std::endl;
			hitTime.restart();
			break;
		case 2:
			Hurt(2);
			std::cout << "Player stracil 2 serduszka" << std::endl;
			hitTime.restart();
			break;
		case 3:
			Hurt(3);
			std::cout << "Player stracil 3 serduszka" << std::endl;
			hitTime.restart();
			break;
		case 8:
			Hurt(5);
			std::cout << "Player stracil 5 serduszek" << std::endl;
			hitTime.restart();
			break;
		default: 
			break;
		}
	}
	PHTime.restart();
}

int Player::EntityCollision(Entity* entity)
{
	switch(entity->getType())
	{
		// Serce
		case 11:
			if (!(getHP() >= 10))
			{
				Heal(1);
				return 0;
			}
			else return 1;
		// Srebrny diament
		case 12:
			coins += 10;
			return 0;
		// Niebieski diament
		case 13:
			coins += 20;
			return 0;
		// Fioletowy diament
		case 14:
			coins += 50;
			return 0;
		// Nastepny level
		case 15:
			return 2;
		// Speed boost
		case 16:
			m_xVel = 300;
			speedBoost = true;
			SBTime.restart();
			return 0;
		// Kolce
		case 17:
			HP = 0;
			return 1;
		// Save
		case 20:
			return 3;
		// DEFAULT
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