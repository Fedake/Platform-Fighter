#pragma once
#include <SFML\Graphics.hpp>

#define TOTAL_SPRITES 64

class ResourceManager
{
	private:
		std::string m_tileName;
		sf::Texture* m_tileTex[TOTAL_SPRITES];
		sf::Texture* m_playerTex;

	public:
		ResourceManager(std::string tileSheet, std::string playerSheet);

		sf::Texture& getTexture(int nr){return *m_tileTex[nr];}
		sf::Texture* getPlayerTexture(){return m_playerTex;}
};