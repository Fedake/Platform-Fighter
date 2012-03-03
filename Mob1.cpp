#include "Mob1.h"

Mob1::Mob1(sf::Vector2f pos)
{
	m_vel = sf::Vector2f(0, 0);
	canJump = false;
	goLeft = true;
	goRight = false;

	box.Left = pos.x;
	box.Top = pos.y;
	box.Width = 8;
	box.Height = 8;

	shape.SetFillColor(sf::Color::Green);	
}

void Mob1::UpdateShape()
{
	shape.SetPosition(box.Left, box.Top);
	shape.SetSize(sf::Vector2f(box.Width, box.Height));
}