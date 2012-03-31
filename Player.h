#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Creature.h"
#include "Entity.h"
#include <iostream>

class Player
{
	private:
		//Pozycja
		sf::FloatRect box;

		sf::Sprite m_sprite;
		Animation* m_anim;

		int m_frame;

		//Predkosc
		sf::Vector2f m_vel;

		sf::Clock hitTime;

		int HP;
		int coins;

		bool canJump;
		bool goLeft, goRight, goDown, goUp;

		bool m_ghost;

	public:
		Player(sf::Vector2f pos, sf::Texture* nTex, int hp, sf::Clock ht = *new sf::Clock);
		
		//Aktualizacja danych
		void Update(sf::Int32 dt);
		void UpdateSprite();
		sf::Sprite GetSprite() {return m_sprite;}

		sf::FloatRect GetBox(){return box;}
		sf::Vector2f getVel() {return m_vel;}

		sf::Clock GetHitTime() { return hitTime; }

		//Poruszanie
		void GoLeft() { goLeft = true; }
		void GoRight() { goRight = true; }
		void GoDown() { goDown = true; }

		bool IsGoingLeft() { return goLeft; }
		bool IsGoingRight() { return goRight; }

		int GetHP() { return HP; }

		void Hurt(int value) { HP -= value; }
		void Heal(int value) { HP += value; }

		void StopLeft() {goLeft = false;}
		void StopRight() {goRight = false;}
		void StopDown() { goDown = false; }
		void StopUp() { goUp = false; }

		void ToggleGhost();

		void Jump();
		void LockJump()				   {canJump = false;}

		void CheckCreaturesAround(Creature* creature);

		void SolidCollision(sf::FloatRect A);
		void CreatureCollision(Creature* creature);
		int EntityCollision(Entity* entity);
};