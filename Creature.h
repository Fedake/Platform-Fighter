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
		bool m_isDead;

	public:
		Creature();
		Creature(sf::Vector2f pos, int type, sf::Texture* nTex, bool left = true);
		
		//Aktualizacja danych
		void Update(sf::Int32 dt);
		void Render(sf::RenderWindow* window);

		void UpdateSprite();
		sf::Sprite getSprite() {return m_sprite;}

		sf::FloatRect getBox(){return box;}
		sf::Vector2f getVel() {return m_vel;}

		//Poruszanie
		void GoLeft() {goLeft = true;}
		void GoRight() {goRight = true;}

		bool isGoingLeft() { return goLeft; }
		bool isGoingRight() { return goRight; }

		int getPATime() { return PATimer.getElapsedTime().asMilliseconds(); }

		bool isDead() { return m_isDead; }

		int getType() { return m_type; }

		float getHP() { return m_hp; }

		void StopLeft() {goLeft = false;}
		void StopRight() {goRight = false;}

		void Jump();
		void LockJump()				   {canJump = false;}

		void SolidCollision(sf::FloatRect A);
		void HalfSolidCollision(sf::FloatRect A);

		void PlayerAround() { playerAround = true; }
		void PlayerNotAround() { playerAround = false; }
		void setVel(float v) { vel = v; }

		void Hurt();
		void Die() { m_isDead = true; }
};