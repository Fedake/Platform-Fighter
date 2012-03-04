#pragma once
#include <SFML\Graphics.hpp>

#define TOTAL_SPRITES 64
#define TOTAL_ENTITIES 16

class ResourceManager
{
	private:
		sf::Texture* m_tileTex[TOTAL_SPRITES];
		sf::Texture* m_playerTex;
		sf::Texture* m_entTex[TOTAL_ENTITIES];

	public:
		ResourceManager(std::string tileSheet, std::string playerSheet, std::string entitySheet);

		sf::Texture& getTexture(int nr){return *m_tileTex[nr];}
		sf::Texture* getPlayerTexture(){return m_playerTex;}
		sf::Texture* GetEntityTexture(int nr){return m_entTex[nr];} 
};