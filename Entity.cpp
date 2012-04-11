#include "Entity.h"
#include <iostream>

Entity::Entity()
{
	box.Left = 0;
	box.Top = 0;
	box.Width = 16;
	box.Height = 16;

	m_type = 20;
}

Entity::Entity(sf::Vector2f pos, int type, sf::Texture* nTex)
{
	box.Left = pos.x;
	box.Top = pos.y;
	box.Width = 16;
	box.Height = 16;

	m_type = type;

	switch (type)
	{
		case 11: m_animFrames = 5; break;
		case 12: m_animFrames = 2; break;
		case 15: m_animFrames = 5; break;
	}
	m_anim = new Animation(nTex, m_animFrames, 100);
}

void Entity::UpdateSprite(int dt)
{
	m_anim->PlayAll();
	m_anim->Update();
	m_sprite = m_anim->GetSprite();
	m_sprite.SetPosition(box.Left, box.Top);
}