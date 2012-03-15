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

	m_anim = new Animation(nTex, 2, 300);
}

void Entity::UpdateSprite()
{
	m_sprite = m_anim->GetSprite();
	m_sprite.SetPosition(box.Left, box.Top);
}