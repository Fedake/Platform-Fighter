#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Creature.h"
#include "Entity.h"
#include "Map.h"
#include <iostream>

class Player
{
	private:
		//Pozycja
		sf::FloatRect box;

		sf::Sprite m_sprite;
		Animation* m_anim;

		sf::Sound m_jumpSnd;

		int m_frame;
		float m_xVel;

		//Predkosc
		sf::Vector2f m_vel;

		sf::Clock hitTime, PHTime, SBTime;

		int HP;
		int coins;

		bool canJump;
		bool speedBoost;
		bool goLeft, goRight, goDown, goUp;

		bool m_ghost;

	public:

		Player(sf::Vector2f pos, ResourceManager* nRes, int hp, sf::Clock ht, bool sB, sf::Clock sbtime);
		
		//Aktualizacja danych
		void Update(sf::Int32 dt, Map* map);
		void UpdateSprite();
		sf::Sprite getSprite() {return m_sprite;}

		sf::FloatRect getBox(){return box;}
		sf::Vector2f getVel() {return m_vel;}

		sf::Clock getHitTime() { return hitTime; }

		//Poruszanie
		void GoLeft() { goLeft = true; }
		void GoRight() { goRight = true; }
		void GoDown() { goDown = true; }

		bool isGoingLeft() { return goLeft; }
		bool isGoingRight() { return goRight; }

		int getHP() { return HP; }
		int getScore() {return coins; }

		sf::Clock getSpeedBoostTime() { return SBTime; }
		bool getSpeedBoost() { return speedBoost; }

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