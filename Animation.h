#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
	private:
		sf::Texture* m_tex;
		sf::Sprite m_sprite;

		sf::Clock m_clock;

		int m_frames;
		int m_frame;

		float m_frameTime;

		int m_state;
	public:
		Animation(sf::Texture* nTex, int nFrames, float nFTime);
		void Update();

		sf::Sprite GetSprite(){return m_sprite;}

		void Stop(){m_state = 0;}
		void PlayLeft(){m_state = 1;}
		void PlayRight(){m_state = 2;}
};