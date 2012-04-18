#include "App.h"
bool App::Init()
{
	m_window.create(sf::VideoMode(m_screenWidth, m_screenHeight, 32), "Platform Fighter v0.6.0", sf::Style::Titlebar);

	m_window.setKeyRepeatEnabled(false);

	m_resMgr = new ResourceManager();

	m_hud = new HUD(m_resMgr->getHudTexture());

	m_map = new Map(m_resMgr);

	m_hp = 10;

	m_currentLevel = 1;
	m_clean = true;

	m_menu = new Menu(m_window.getSize().x, m_window.getSize().y, m_resMgr, SaveExist());

	m_cam = new Camera(sf::Vector2i(m_window.getSize().x, m_window.getSize().y), sf::Vector2i(m_map->getMapWidth(), m_map->getMapHeight()));

	std::cout << "sizeof(Map): " << sizeof(Map) << std::endl;
	bg.setTexture(*m_resMgr->getBgTexture());

	sf::ContextSettings settings = m_window.getSettings();
	std::cout << "OpenGL v" << settings.majorVersion << "." << settings.minorVersion << std::endl;
	return true;
}

bool App::loadLevel()
{
	creature.clear();
	entity.clear();
	
	m_map = new Map(m_resMgr);
	std::stringstream level;
	level << "data/maps/" << m_currentLevel << ".map";
	std::cout << level.str() << std::endl;
	std::cout << "Level: " << level.str() << std::endl;
	if(!m_map->loadNextLevel(level.str()))
	{
		std::cout << "Level: " << level.str() << std::endl;
		std::cout << "No such level";
		return false;
	}

	m_hp = 10;

	m_player = new Player(m_map->getPlayerPos(), m_resMgr->getPlayerTexture(), m_hp);
	m_cam = new Camera(sf::Vector2i(m_window.getSize().x, m_window.getSize().y), sf::Vector2i(m_map->getMapWidth(), m_map->getMapHeight()));
	m_gun = new Gun();

	for(int j = 0; j < m_map->getMapHeight(); j++)
	{
		for(int i = 0; i < m_map->getMapWidth(); i++)
		{
			int type = m_map->getEntity(i, j);
			if (type > 0 && type < 8)
			{
				creature.push_back(new Creature(sf::Vector2f(static_cast<float>(i*16), static_cast<float>(j*16)), type, m_resMgr->getEntityTexture(type)));
			}
			else if (type >= 8 && type < 10)
			{
				creature.push_back(new Creature(sf::Vector2f(static_cast<float>(i*16), static_cast<float>(j*16)), type, m_resMgr->getBossTexture(1)));
			}
			else if (type >= 10 && type < 21)
			{
				entity.push_back(new Entity(sf::Vector2f(static_cast<float>(i*16), static_cast<float>(j*16)), type, m_resMgr->getEntityTexture(type)));
			}
		}
	}
	m_clean = false;
	return true;
}

void App::CleanUp()
{
	if (!m_clean)
	{
		std::cout << "CleanUp() started" << std::endl;
		if (m_player != NULL)
		{
			std::cout << std::endl;
			delete m_player;
			m_player = NULL;
			std::cout << "m_player deleted" << std::endl;
			std::cout << std::endl;
		}

		if (m_gun != NULL)
		{
			std::cout << std::endl;
			delete m_gun;
			m_gun = NULL;
			std::cout << "m_gun deleted" << std::endl;
			std::cout << std::endl;
		}

		delete m_map;
		m_map = NULL;
		
		for (unsigned i = 0; i < creature.size(); ++i)
		{
			delete creature[i];
		}

		for (unsigned i = 0; i < entity.size(); ++i)
		{
			delete entity[i];
		}
		
		creature.clear();
		entity.clear();

		m_clean = true;
		std::cout << "CleanUp() ended" << std::endl;
	}
}

void App::Run()
{
	if(!Init()) m_done = true;
	sf::Clock dt;
	sf::Clock fpsCap;

	dt.restart();
	// pêtla g³ówna
	m_done = false;
	while (!m_done)
	{
		fpsCap.restart();

		ProcessEvents();
		if(dt.getElapsedTime().asSeconds() < 0.1f)
			Update(dt.getElapsedTime());
		
		dt.restart();
		
		draw();
		if(fpsCap.getElapsedTime().asMilliseconds() != 0)
		{
			if(1000/fpsCap.getElapsedTime().asMilliseconds() > 40)
			{
				sf::Time sleepTime = sf::milliseconds((1000/40) - fpsCap.getElapsedTime().asMilliseconds());
				sf::sleep(sleepTime);
			}
		}
	}
	m_window.close();
}

void App::draw()
{
	m_window.clear(sf::Color::White);
	if(!m_menu->isActive() || (m_menu->getType() != 2 && m_menu->getType() != 0))
	{
		m_window.setView(m_window.getDefaultView());
		m_window.draw(bg);
	}
    //RYSOWANIE UWZGLEDNIAJAC KAMERE
	m_window.setView(m_cam->getView());
	//m_window.Clear(sf::Color(255, 255, 255));
	if(!m_menu->isActive() || (m_menu->getType() != 2 && m_menu->getType() != 0))
	{
		for(int i = 0; i < m_gun->getBullets(); i++)
		{
			m_window.draw(m_gun->getBulletShape(i));
		}

		m_window.draw(m_player->getSprite());

		for (unsigned i = 0; i < creature.size(); ++i)
		{
			creature[i]->Render(&m_window);
		}

		for (unsigned i = 0; i < entity.size(); ++i)
		{
			m_window.draw(entity[i]->getSprite());
		}

		//Render mapy
		m_map->draw(&m_window);
	}

	//RYSOWANIE STALYCH ELEMENTOW EKRANU
	m_window.setView(m_window.getDefaultView());
	if(!m_menu->isActive() || (m_menu->getType() != 2 && m_menu->getType() != 0))
	{
		m_hud->draw(&m_window);
	}
	if(m_menu->isActive()) m_menu->draw(&m_window);

	m_window.display();
}

void App::ProcessEvents()
{
	if (m_done)
	{ // je¿eli mamy zakoñczyæ, to pomijamy obs³ugê zdarzeñ
		return;
	}
 
	// przejrzymy kolejne zdarzenia z kolejki
	sf::Event Event;
	while (m_window.pollEvent(Event))
	{
		if(Event.type == sf::Event::TextEntered && !m_menu->isActive())
		{
			m_textInput += Event.text.unicode;

			if(m_textInput.find("ghost") != std::string::npos)
			{
				m_textInput.clear();
				m_player->ToggleGhost();
			}
		}
		else if(Event.type == sf::Event::MouseMoved)
		{
			m_mPos = sf::Vector2f(static_cast<float>(Event.mouseMove.x), static_cast<float>(Event.mouseMove.y));
			m_menu->setMousePosition(m_mPos);
		}

		else if(Event.type == sf::Event::MouseButtonPressed)
		{
			if(Event.key.code == sf::Mouse::Left)
			{
				if(!m_menu->isActive())	m_gun->Shoot(m_window.convertCoords(static_cast<sf::Vector2i>(m_mPos),
													 m_cam->getView()), sf::Vector2f(m_player->getBox().left + 8, m_player->getBox().top + 8));
				else m_menu->Click(m_done, m_state);

				if(m_state == 1) 
				{
					m_currentLevel = 1;
					loadLevel();
				}
				if(m_state == 2) loadGame();
				if(m_state == 3) loadLevel();

				m_state = 0;
			}
		}
		else if(Event.type == sf::Event::KeyPressed)
		{
			if(Event.key.code == sf::Keyboard::Escape)
			{
				m_menu->Toggle();
			}
		}
		else if(Event.type == sf::Event::LostFocus) m_menu->OpenMenu();
	}

	if(!m_menu->isActive())
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) m_player->Jump();
		else m_player->StopUp();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) m_player->GoLeft();
		else m_player->StopLeft();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) m_player->GoRight();
		else m_player->StopRight();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) m_player->GoDown();
		else m_player->StopDown();
	}
}

void App::Update(sf::Time dt)
{
	if(m_menu->isActive())
	{
		if (m_menu->getType() == 0)
		{
			m_menu->setContinue(SaveExist());
			CleanUp();
		}
		m_menu->Update();
	}

	if(!m_menu->isActive())
	{
		m_player->Update(dt.asMilliseconds(), m_map);

		for (unsigned i = 0; i < creature.size(); ++i)
		{
			creature[i]->Update(dt.asMilliseconds());
			m_player->CheckCreaturesAround(creature[i]);
		}
		for (unsigned i = 0; i < entity.size(); ++i)
		{
			entity[i]->UpdateSprite(dt.asMilliseconds());
		}
		// MAP MOB
		for (unsigned curr = 0; curr < creature.size(); ++curr)
		{
			for(int j = creature[curr]->getBox().top/16 - 1; j < creature[curr]->getBox().top/16 + 1; j++)
			{
				for(int i = creature[curr]->getBox().left/16 - 1; i < creature[curr]->getBox().left/16 + 1; i++)
				{
					if(m_map->isSolid(i, j))
					{
						if (CheckCollision(creature[curr]->getBox(), m_map->getBox(static_cast<float>(i), static_cast<float>(j))))
						{
							creature[curr]->SolidCollision(m_map->getBox(static_cast<float>(i), static_cast<float>(j)));
						}
					}
				}
			}
		}

		for (unsigned b = 0; b < m_gun->getBullets(); b++)
		{
			bool killed = false;
			for(int j = m_gun->getBulletBox(b).top/16 - 1; j < m_gun->getBulletBox(b).top/16 + 1; j++)
			{
				for(int i = m_gun->getBulletBox(b).left/16 - 1; i < m_gun->getBulletBox(b).left/16 + 1; i++)
				{
					if(m_map->isSolid(i, j))
					{
						// MAP BULLET
						if(CheckCollision(m_gun->getBulletBox(b), m_map->getBox(static_cast<float>(i), static_cast<float>(j))))
						{
							m_gun->KillBullet(b);
							killed = true;
						}
					}
					if (killed) break;
				}
				if (killed) break;
			}
		}

		// ENTITY GRACZ
		for (unsigned current = 0; current < entity.size(); ++current)
		{
			if (CheckCollision(entity[current]->getBox(), m_player->getBox()))
			{
				if (m_player->EntityCollision(entity[current]) == 0)
					entity.erase(entity.begin() + current);
				else if (m_player->EntityCollision(entity[current]) == 2)
				{
					m_menu->Next(m_currentLevel);
					m_currentLevel += 1;
				}
				else if (m_player->EntityCollision(entity[current]) == 3)
				{
					SaveGame();
					entity.erase(entity.begin() + current);
				}
			}
		}
		// MOB GRACZ
		for (unsigned current = 0; current < creature.size(); ++current)
		{
			if (CheckCollision(creature[current]->getBox(), m_player->getBox()))
			{
				m_player->CreatureCollision(creature[current]);
			}
		}
		// MOB BULLET
		for (int b = 0; b < m_gun->getBullets(); b++)
		{
			for (unsigned current = 0; current < creature.size(); ++current)
			{
				if (CheckCollision(m_gun->getBulletBox(b), creature[current]->getBox()))
				{
					m_gun->KillBullet(b);
					creature[current]->Hurt();
					if (creature[current]->isDead())
						creature.erase(creature.begin() + current);
					break;
				}
			}
		}

		m_gun->Update(dt.asMilliseconds());

		m_hud->Update(m_player->getHP(), m_player->getScore());
		if(m_player->getHP() <= 0) m_menu->Die(m_player->getScore());
		m_cam->set(m_player->getBox());
	}
}

bool App::CheckCollision(sf::FloatRect A, sf::FloatRect B)
{
	if(A.intersects(B)) return true;
	else return false;
}

void App::SaveGame()
{
	std::cout << "Zapis gry." << std::endl;

	Save* save = new Save();
	
	save->level = m_currentLevel;
	save->hp = m_player->getHP();

	save->posX = m_player->getBox().left;
	save->posY = m_player->getBox().top;

	save->ht = m_player->getHitTime();
	
	ZeroMemory(save->creatureData, sizeof(save->creatureData));
	ZeroMemory(save->entityData, sizeof(save->entityData));

	for (unsigned i = 0; i < creature.size(); ++i)
	{
		save->creatureData[i].x = creature[i]->getBox().left;
		save->creatureData[i].y = creature[i]->getBox().top;
		save->creatureData[i].type = creature[i]->getType();
		save->creatureData[i].left = creature[i]->isGoingLeft();
	}

	for (unsigned i = 0; i < entity.size(); ++i)
	{
		save->entityData[i].x = entity[i]->getBox().left;
		save->entityData[i].y = entity[i]->getBox().top;
		save->entityData[i].type = entity[i]->getType();
	}

	std::ofstream file("save.dat", std::ios::binary);
	file.write((char*)(save), sizeof(Save));
	file.close();

	delete save;
}

bool App::loadGame()
{
	std::ifstream file("save.dat", std::ios::binary);

	char* temp = new char[sizeof(Save)];
	file.read(temp, sizeof(Save));
	Save* save = (Save*)(temp);

	m_currentLevel = save->level;

	m_map = new Map(m_resMgr);

	std::stringstream level;
	level << "data/maps/" << save->level << ".map";
	if(!m_map->loadNextLevel(level.str())) 
	{
		std::cout << "Level: " << level << std::endl;
		std::cout << "No such level";
		return false;
	}

	m_player = new Player(sf::Vector2f(save->posX, save->posY), m_resMgr->getPlayerTexture(), save->hp, save->ht);
	m_cam = new Camera(sf::Vector2i(m_window.getSize().x, m_window.getSize().y), sf::Vector2i(m_map->getMapWidth(), m_map->getMapHeight()));
	m_gun = new Gun();

	for (unsigned i = 0; i < ENT_MAX_SIZE; ++i)
	{
		if (save->creatureData[i].x == NULL) break;
		
			float x = save->creatureData[i].x;
			float y = save->creatureData[i].y;
			int type = save->creatureData[i].type;
			bool left = save->creatureData[i].left;
			if (type > 0 && type < 7)
			{
				creature.push_back(new Creature(sf::Vector2f(x, y), type, m_resMgr->getEntityTexture(type), left));
			}
			else if (type >=7 && type < 9)
			{
				creature.push_back(new Creature(sf::Vector2f(x, y), type, m_resMgr->getBossTexture(1), left));
			}
			
	}

	for (unsigned i = 0; i < ENT_MAX_SIZE; ++i)
	{
		if (save->entityData[i].x == NULL) break;

			float x = save->entityData[i].x;
			float y = save->entityData[i].y;
			int type = save->entityData[i].type;
			entity.push_back(new Entity(sf::Vector2f(x, y), type, m_resMgr->getEntityTexture(type)));
		
	}

	m_clean = false;
	return true;
}

bool App::SaveExist()
{
        FILE* plik;
        plik = fopen("save.dat", "r");
        if ( plik )
        {
            fclose(plik);
            return true;
        }
        //fclose(plik);
        return false;
}