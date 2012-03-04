#include <SFML\Graphics.hpp>

class HUD
{
	private:
		sf::Sprite m_hearthSpr[10];
		int m_hp;

	public:
		HUD(sf::Texture* hudTex);

		void Update(int hp){m_hp = hp;}

		void Draw(sf::RenderWindow* wnd);
};