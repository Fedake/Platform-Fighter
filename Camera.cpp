#include "Camera.h"

void Camera::Set(sf::FloatRect box)
{
	view.SetSize(static_cast<sf::Vector2f>(m_winSize));
	sf::Vector2f vCenter(box.Left + (box.Width)/2, box.Top + (box.Height)/2);

	if(vCenter.x < m_winSize.x/2) vCenter.x = static_cast<float>(m_winSize.x/2);
	else if(vCenter.x > m_lvlSize.x*32 - m_winSize.x/2) vCenter.x = m_lvlSize.x*32 - static_cast<float>(m_winSize.x/2);

	if(vCenter.y < m_winSize.y/2) vCenter.y = static_cast<float>(m_winSize.y/2);
	else if(vCenter.y > m_lvlSize.y*32 - m_winSize.y/2) vCenter.y = m_lvlSize.y*32 - static_cast<float>(m_winSize.y/2);

	m_vPos = vCenter - static_cast<sf::Vector2f>(m_winSize/2);
	view.SetCenter(vCenter);
}