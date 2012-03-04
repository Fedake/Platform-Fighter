#include "Gun.h"


Gun::Gun() : m_currentBull(0), m_bulletShooted(0)
{
}

void Gun::Shoot(sf::Vector2f mPos, sf::Vector2f pPos)
{
	mPos -= pPos;
	float L = sqrt(pow(mPos.x, 2) + pow(mPos.y, 2));
	//Normalizacja
	sf::Vector2f posN((mPos.x/L)*1000, (mPos.y/L)*1000);

	m_bulletVec.push_back(new Bullet(pPos, posN.x, posN.y));

	std::cout << "Bullets alive: " << m_bulletVec.size() << std::endl;

	m_bulletShooted++;
}

void Gun::Update(int dt)
{
	for(unsigned i = 0; i < m_bulletVec.size(); i++)
	{
		m_bulletVec[i]->Update(dt);
	}
}