#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#define TOTAL_SPRITES 64
#define TOTAL_ENTITIES 21

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

		sf::SoundBuffer* m_jumpSnd;

	public:
		ResourceManager();

		sf::Texture* getTexture(int nr){return m_tileTex[nr];}
		sf::Texture* getPlayerTexture(){return m_playerTex;}
		sf::Texture* getEntityTexture(int nr){return m_entTex[nr];} 
		sf::Texture* getHudTexture(){return m_hudTex;}
		sf::Texture* getGuiTexture(){return m_guiTex;}
		sf::Texture* getTitleTexture(){return m_titleTex;}
		sf::Texture* getBossTexture(int nr){return m_bossTex[nr];}
		sf::Texture* getBgTexture(){return m_bgTex;}
		sf::Texture* getCreditsTexture(){return m_creditsTex;}

		sf::SoundBuffer* getJumpSnd(){return m_jumpSnd;}
};