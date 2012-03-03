#include "Log.h"

Log::Log() : m_showText("")
{
	sf::Font fnt(sf::Font::GetDefaultFont());
	m_showText.SetFont(fnt);
	m_showText.SetCharacterSize(10);
	m_showText.SetColor(sf::Color::Red);
}

void Log::AddLine(sf::String str)
{
	m_showText.SetString(str);
}