#pragma once
#include "Bullet.h"
#include <iostream>

class Gun
{
	private:
		std::vector<Bullet*> m_bulletVec;

		int m_currentBull;

		int m_bulletShooted;
	public:
		Gun();

		void Shoot(sf::Vector2f mousePos, sf::Vector2f playerPos);
		void Update(int dt);
		void KillBullet(int number) {m_bulletVec.erase(m_bulletVec.begin() + number);}
		
		sf::CircleShape getBulletShape(int number) {return m_bulletVec[number]->getShape();}
		sf::FloatRect getBulletBox(int number) {return m_bulletVec[number]->getBox();}

		int GetBullets(){return m_bulletVec.size();}
};