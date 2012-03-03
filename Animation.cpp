#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Texture* nTex, int nFrames, float nFTime) : m_tex(nTex), m_frames(nFrames), m_frameTime(nFTime)
{
	m_sprite.SetTexture(*m_tex);
	m_frame = 0;
	m_clock.Restart();
}
void Animation::Update()
{
	if(!m_animate) m_sprite.SetTextureRect(sf::IntRect(0, 0, 16, 16));
	else if(m_clock.GetElapsedTime().AsMilliseconds() > m_frameTime)
	{
		m_frame++;

		if(m_frame >= m_frames) m_frame = 0;
		m_sprite.SetTextureRect(sf::IntRect(m_frame*16, 0, 16, 16));

		m_clock.Restart();
	}
}