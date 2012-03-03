#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Creature
{
	protected:
		//Pozycja
		sf::FloatRect box;
		sf::RectangleShape shape;

		//Predkosc
		sf::Vector2f m_vel;

		bool canJump;
		bool goLeft, goRight;

	public:
		Creature();
		Creature(sf::Vector2f pos);
		
		//Aktualizacja danych
		void Update(sf::Int32 dt);
		void UpdateShape();
		sf::RectangleShape GetShape() {return shape;}

		sf::FloatRect GetBox(){return box;}
		sf::Vector2f getVel() {return m_vel;}

		//Poruszanie
		void GoLeft() {goLeft = true;}
		void GoRight() {goRight = true;}

		void StopLeft() {goLeft = false;}
		void StopRight() {goRight = false;}

		void Jump();
		void LockJump()				   {canJump = false;}

		void SolidCollision(sf::FloatRect A);
		void HalfSolidCollision(sf::FloatRect A);
};