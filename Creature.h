#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"

class Creature
{
	private:
		//Pozycja
		sf::FloatRect box;
		Animation* m_anim;
		sf::Sprite m_sprite;

		//Predkosc
		sf::Vector2f m_vel;

		int m_type;
		int HP;
		
		float vel;

		bool playerAround;
		bool canJump;
		bool goLeft, goRight;
		bool isDead;

	public:
		Creature();
		Creature(sf::Vector2f pos, int type, sf::Texture* nTex, bool left = true);
		
		//Aktualizacja danych
		void Update(sf::Int32 dt);
		void UpdateSprite();
		sf::Sprite GetSprite() {return m_sprite;}

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

		void PlayerAround() { playerAround = true; }
		void PlayerNotAround() { playerAround = false; }
		void SetVel(int v) { vel = v; }

		void Hurt();
		void Die() { isDead = true; }
};