#include <SFML\Graphics.hpp>

class HUD
{
	private:
		sf::Sprite m_hearthSpr[10];

		sf::Text m_scoreText;
		//int m_score;
		int m_hp;

	public:
		HUD(sf::Texture* hudTex);

		void Update(int hp, int score);

		void draw(sf::RenderWindow* wnd);
};