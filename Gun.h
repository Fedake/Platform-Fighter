#pragma once
#include "Bullet.h"
#include <iostream>

#define BULLET_ARRAY_SIZE 64

class Gun
{
	private:
		//Bullet* m_bulletArr[BULLET_ARRAY_SIZE];

		std::vector<Bullet*> m_bulletVec;

		int m_currentBull;

		int m_bulletShooted;
	public:
		Gun();

		void Shoot(sf::Vector2f mousePos, sf::Vector2f playerPos);
		void Update(int dt);
		//void KillBullet(int number) {m_bulletArr[number]->Kill();}
		
		//sf::CircleShape getBulletShape(int number) {return m_bulletArr[number]->getShape();}
		//sf::FloatRect getBulletBox(int number) {return m_bulletArr[number]->getBox();}
		//bool getBulletAlive(int number) { return m_bulletArr[number]->isAlive(); }
};