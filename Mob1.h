#pragma once
#include "Creature.h"

class Mob1 : public Creature
{
	public:
		Mob1(sf::Vector2f pos);

		void UpdateShape();
};