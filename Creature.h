#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Creature
{
	private:
		//Pozycja
		sf::FloatRect box;
		sf::RectangleShape shape;

		//Predkosc
		sf::Vector2f m_vel;

		int m_type;
		int HP;

		bool canJump;
		bool goLeft, goRight;
		bool isDead;

	public:
		Creature();
		Creature(sf::Vector2f pos, int type);
		
		//Aktualizacja danych
		void Update(sf::Int32 dt);
		void UpdateShape();
		sf::RectangleShape GetShape() {return shape;}

		sf::FloatRect GetBox(){return box;}
		sf::Vector2f getVel() {return m_vel;}

		//Poruszanie
		void GoLeft() {goLeft = true;}
		void GoRight() {goRight = true;}

		bool IsGoingLeft() { return goLeft; }
		bool IsGoingRight() { return goRight; }

		bool IsDead() { return isDead; }

		int GetType() { return m_type; }

		int GetHP() { return HP; }

		void StopLeft() {goLeft = false;}
		void StopRight() {goRight = false;}

		void Jump();
		void LockJump()				   {canJump = false;}

		void SolidCollision(sf::FloatRect A);
		void HalfSolidCollision(sf::FloatRect A);

		void Hurt();
		void Die() { isDead = true; }
};