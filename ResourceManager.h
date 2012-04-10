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
		sf::Texture* m_bossTex[4];
		sf::Texture* m_hudTex;
		sf::Texture* m_guiTex;
		sf::Texture* m_titleTex;
		sf::Texture* m_bgTex;
		sf::Texture* m_creditsTex;

	public:
		ResourceManager();

		sf::Texture& getTexture(int nr){return *m_tileTex[nr];}
		sf::Texture* getPlayerTexture(){return m_playerTex;}
		sf::Texture* GetEntityTexture(int nr){return m_entTex[nr];} 
		sf::Texture* getHudTexture(){return m_hudTex;}
		sf::Texture* GetGuiTexture(){return m_guiTex;}
		sf::Texture* GetTitleTexture(){return m_titleTex;}
		sf::Texture* GetBossTexture(int nr){return m_bossTex[nr];}
		sf::Texture* GetBgTexture(){return m_bgTex;}
		sf::Texture* GetCreditsTexture(){return m_creditsTex;}
};