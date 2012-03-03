#include "Bullet.h"

void Bullet::Reset(sf::Vector2f pos, float velX, float velY)
{
	m_pos = pos;
	m_vel.x = velX;
	m_vel.y = velY;
	m_isAlive = true;

	m_shape.SetRadius(3);
	m_shape.SetFillColor(sf::Color::Red);	
}

void Bullet::Update(int dt)
{
	if(m_isAlive)
	{
		m_pos.x += m_vel.x*(dt/1000.f);
		m_pos.y += m_vel.y*(dt/1000.f);

		m_shape.SetPosition(m_pos);
	}
}