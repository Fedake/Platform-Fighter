#include "Gun.h"


Gun::Gun() : m_currentBull(0), m_bulletShooted(0)
{
	for(int i = 0; i < BULLET_ARRAY_SIZE; i++)
	{
		m_bulletArr[i] = new Bullet();
	}
}

void Gun::Shoot(sf::Vector2f mPos, sf::Vector2f pPos)
{
	mPos -= pPos;
	float L = sqrt(pow(mPos.x, 2) + pow(mPos.y, 2));
	//Normalizacja
	sf::Vector2f posN((mPos.x/L)*1000, (mPos.y/L)*1000);

	m_bulletArr[m_currentBull]->Reset(pPos, posN.x, posN.y);

	m_currentBull++;
	m_bulletShooted++;

	if(m_currentBull >= BULLET_ARRAY_SIZE) m_currentBull = 0;
}

void Gun::Update(int dt)
{
	for(int i = 0; i < BULLET_ARRAY_SIZE; i++)
	{
		if(m_bulletArr[i]->isAlive())
		{
			m_bulletArr[i]->Update(dt);
		}
	}
}