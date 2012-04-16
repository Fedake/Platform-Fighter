#include "Camera.h"

void Camera::set(sf::FloatRect box)
{
	view.setSize(static_cast<sf::Vector2f>(m_winSize));
	sf::Vector2f vCenter(box.left + (box.width)/2, box.top + (box.height)/2);

	if(vCenter.x < m_winSize.x/2) vCenter.x = static_cast<float>(m_winSize.x/2);
	else if(vCenter.x > m_lvlSize.x*16 - m_winSize.x/2) vCenter.x = m_lvlSize.x*16 - static_cast<float>(m_winSize.x/2);

	if(vCenter.y < m_winSize.y/2) vCenter.y = static_cast<float>(m_winSize.y/2);
	else if(vCenter.y > m_lvlSize.y*16 - m_winSize.y/2) vCenter.y = m_lvlSize.y*16 - static_cast<float>(m_winSize.y/2);

	m_vPos = vCenter - static_cast<sf::Vector2f>(m_winSize/2);
	view.setCenter(vCenter);
}