#pragma once
#include "Player.h"
#include "Map.h"
#include "Camera.h"
#include "Gun.h"
#include "Log.h"
#include "ResourceManager.h"
#include "HUD.h"
#include "Menu.h"

#include "Creature.h"
#include "Entity.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include <SFML/Graphics.hpp>

const int TILE_COUNT = 1024;
const int CREATURE_COUNT = 10;

class App
{
	private:
		int m_screenWidth;
		int m_screenHeight;

		bool m_fullscreen;
		bool m_done;

		int m_state;

		sf::RenderWindow m_window;

		std::string m_textInput;

		sf::Vector2f m_mPos;

		std::vector<Creature*> creature;
		std::vector<Entity*> entity;

		int m_currentLevel;

		Player* m_player;
		Gun* m_gun;
		Map* m_map;
		Camera* m_cam;
		Log* m_log;
		ResourceManager* m_resMgr;
		HUD* m_hud;
		Menu* m_menu;
	public:
		App(size_t win_width, size_t win_height, bool fullscreen_mode) 
				: m_screenWidth(win_width), m_screenHeight(win_height),
				m_fullscreen(fullscreen_mode), m_player(0), m_cam(0), 
				m_state(0) { };
 
		void Run();

	private:
		bool Init();
		bool LoadLevel();
		void Draw();                // rysowanie 
		void Update(sf::Time dt);	// aktualizacja
		void ProcessEvents();       // przetwarzanie zdarzeñ, które przysz³y	

		bool CheckCollision(sf::FloatRect A, sf::FloatRect B);

};