#include <SFML\Graphics.hpp>

class Log
{
	private:
		sf::Text m_showText;

	public:
		Log();

		void AddLine(sf::String newLine);

		sf::Text getText(){return m_showText;}
};