#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Texture* nTex, int nFrames, float nFTime, int width, int height) : m_tex(nTex), m_frames(nFrames), m_frameTime(nFTime)
{
	m_height = height;
	m_width = width;

	m_sprite.setTexture(*m_tex);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_height, m_width));

	m_frame = 1;
	m_clock.restart();

	m_state = 0;
	m_prevState = 0;
}
void Animation::Update()
{
	if(m_state == 0) m_sprite.setTextureRect(sf::IntRect(0, 0, m_width, m_height));

	else if(m_clock.getElapsedTime().asMilliseconds() > m_frameTime || m_state != m_prevState)
	{
		if(m_state == m_prevState) m_frame++;
		if(m_frame > m_frames) m_frame = 1;

		if (m_state == 1)
		{
			m_sprite.setTextureRect(sf::IntRect(m_frame*m_width, 0, m_width, m_height));
		}
		else if (m_state == 2) 
		{
			m_sprite.setTextureRect(sf::IntRect((m_frame+m_frames)*m_width, 0, m_width, m_height));
		}
		else if (m_state == 3)
		{
			m_sprite.setTextureRect(sf::IntRect((m_frame-1)*m_width, 0, m_width, m_height));
		}
		m_clock.restart();
	}
}