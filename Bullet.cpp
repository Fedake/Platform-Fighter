#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos, float velX, float velY) : m_pos(pos), m_vel(velX, velY)
{
	m_shape.setRadius(3);
	m_shape.setFillColor(sf::Color::Red);
}

void Bullet::Update(int dt)
{
	m_pos.x += m_vel.x*(dt/1000.f);
	m_pos.y += m_vel.y*(dt/1000.f);

	m_shape.setPosition(m_pos);
}