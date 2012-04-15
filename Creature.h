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
		sf::RectangleShape m_hpBar;

		//Predkosc
		sf::Vector2f m_vel;

		sf::Clock PATimer;

		int m_type;
		
		float m_hp;
		float m_hpMax;
		
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
		void Render(sf::RenderWindow* window);

		void UpdateSprite();
		sf::Sprite GetSprite() {return m_sprite;}

		sf::FloatRect GetBox(){return box;}
		sf::Vector2f getVel() {return m_vel;}

		//Poruszanie
		void GoLeft() {goLeft = true;}
		void GoRight() {goRight = true;}

		bool IsGoingLeft() { return goLeft; }
		bool IsGoingRight() { return goRight; }

		int GetPATime() { return PATimer.GetElapsedTime().AsMilliseconds(); }

		bool IsDead() { return isDead; }

		int GetType() { return m_type; }

		float GetHP() { return m_hp; }

		void StopLeft() {goLeft = false;}
		void StopRight() {goRight = false;}

		void Jump();
		void LockJump()				   {canJump = false;}

		void SolidCollision(sf::FloatRect A);
		void HalfSolidCollision(sf::FloatRect A);

		void PlayerAround() { playerAround = true; }
		void PlayerNotAround() { playerAround = false; }
		void SetVel(float v) { vel = v; }

		void Hurt();
		void Die() { isDead = true; }
};