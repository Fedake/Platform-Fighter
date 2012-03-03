#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Creature.h"
#include <iostream>

class Player
{
	private:
		//Pozycja
		sf::FloatRect box;
		sf::RectangleShape shape;

		sf::Texture* m_tex;
		sf::Sprite m_sprite;
		Animation* m_anim;

		int m_frame;

		//Predkosc
		sf::Vector2f m_vel;

		bool canJump;
		bool goLeft, goRight;

		bool noclip;

	public:
		Player(sf::Vector2f pos, sf::Texture* nTex);
		
		//Aktualizacja danych
		void Update(sf::Int32 dt);
		void UpdateShape();
		sf::Sprite GetShape() {return m_sprite;}

		sf::FloatRect GetBox(){return box;}
		sf::Vector2f getVel() {return m_vel;}

		//Poruszanie
		void GoLeft() {goLeft = true;}
		void GoRight() {goRight = true;}

		void StopLeft() {goLeft = false;}
		void StopRight() {goRight = false;}

		void ToggleNoclip() {noclip = !noclip;}

		void Jump();
		void LockJump()				   {canJump = false;}

		void SolidCollision(sf::FloatRect A);
		void CreatureCollision(Creature* creature);
};