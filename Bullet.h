#pragma once
#include <SFML\Graphics.hpp>

class Bullet
{
	private:
		sf::Vector2f		m_pos;
		sf::Vector2f		m_vel;

		sf::FloatRect		m_box;
		sf::CircleShape		m_shape;

		bool				m_isAlive;

	public:
		Bullet(sf::Vector2f pos, float velX, float velY) : m_pos(pos), m_vel(velX, velY), m_isAlive(false){}

		void Reset(sf::Vector2f pos, float velX, float velY);
		void Update(int dt);
		void Kill() {m_isAlive = false;}

		sf::CircleShape getShape() {return m_shape;}
		sf::FloatRect getBox() {return sf::FloatRect(m_pos.x - 1.5f, m_pos.y - 1.5f, 6, 6);}

		bool isAlive() {return m_isAlive;}
};