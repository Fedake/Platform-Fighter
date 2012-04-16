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

		int m_height, m_width;

		int m_state;
		int m_prevState;
	public:
		Animation(sf::Texture* nTex, int nFrames, float nFTime, int height = 16, int width = 16);
		void Update();

		sf::Sprite getSprite(){return m_sprite;}

		void Stop(){m_prevState = m_state; m_state = 0;}
		void PlayLeft(){m_prevState = m_state; m_state = 1;}
		void PlayRight(){m_prevState = m_state; m_state = 2;}
		void PlayAll() { m_prevState = m_state; m_state = 3; }
		void restart(){m_clock.restart();}
};