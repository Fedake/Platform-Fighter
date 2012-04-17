#include "Entity.h"
#include <iostream>

Entity::Entity()
{
	box.left = 0;
	box.top = 0;
	box.width = 16;
	box.height = 16;

	m_type = 25;
}

Entity::Entity(sf::Vector2f pos, int type, sf::Texture* nTex)
{
	box.left = pos.x;
	box.top = pos.y;
	box.width = 16;
	box.height = 16;

	m_type = type;

	switch (type)
	{
		case 11: m_animFrames = 5; break;
		//case 12: m_animFrames = 2; break;
		case 15: m_animFrames = 5; break;
	}
	m_anim = new Animation(nTex, m_animFrames, 100);
}

void Entity::UpdateSprite(int dt)
{
	m_anim->PlayAll();
	m_anim->Update();
	m_sprite = m_anim->getSprite();
	m_sprite.setPosition(box.left, box.top);
}