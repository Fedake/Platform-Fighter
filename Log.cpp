#include "Log.h"

Log::Log() : m_showText("")
{
	sf::Font fnt(sf::Font::getDefaultFont());
	m_showText.setFont(fnt);
	m_showText.setCharacterSize(10);
	m_showText.setColor(sf::Color::Red);
}

void Log::AddLine(sf::String str)
{
	m_showText.setString(str);
}