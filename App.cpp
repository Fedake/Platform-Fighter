#include "App.h"
bool App::Init()
{
	m_window.Create(sf::VideoMode(m_screenWidth, m_screenHeight, 32), "Platform Fighter v0.5.3", sf::Style::Titlebar);

	m_window.SetFramerateLimit(60);
	m_window.EnableKeyRepeat(false);

	m_resMgr = new ResourceManager();

	m_hud = new HUD(m_resMgr->getHudTexture());

	m_map = new Map(m_resMgr);

	m_hp = 10;

	m_currentLevel = 1;
	m_clean = true;

	m_menu = new Menu(m_window.GetWidth(), m_window.GetHeight(), m_resMgr->GetTitleTexture(), m_resMgr->GetGuiTexture(), SaveExist());

	m_cam = new Camera(sf::Vector2i(m_window.GetWidth(), m_window.GetHeight()), sf::Vector2i(m_map->getMapWidth(), m_map->getMapHeight()));
	return true;
}

bool App::LoadLevel()
{
	creature.clear();
	entity.clear();

	std::stringstream level;
	level << "data/maps/" << m_currentLevel << ".map";
	if(!m_map->LoadNextLevel(level.str()))
	{
		std::cout << "Level: " << level << std::endl;
		std::cout << "No such level";
		return false;
	}

	m_player = new Player(m_map->getPlayerPos(), m_resMgr->getPlayerTexture(), m_hp);
	m_gun = new Gun();

	for(int j = 0; j < m_map->getMapHeight(); j++)
	{
		for(int i = 0; i < m_map->getMapWidth(); i++)
		{
			int type = m_map->getEntity(i, j);
			if (type > 0 && type < 10)
			{
				creature.push_back(new Creature(sf::Vector2f(static_cast<float>(i*16), static_cast<float>(j*16)), type, m_resMgr->GetEntityTexture(type)));
			}
			else if (type >= 10 && type < 16)
			{
				entity.push_back(new Entity(sf::Vector2f(static_cast<float>(i*16), static_cast<float>(j*16)), type, m_resMgr->GetEntityTexture(2)));
			}
		}
	}
	m_cam = new Camera(sf::Vector2i(m_window.GetWidth(), m_window.GetHeight()), sf::Vector2i(m_map->getMapWidth(), m_map->getMapHeight()));
	m_clean = false;
	return true;
}

void App::CleanUp()
{
	if (!m_clean)
	{
		std::cout << "CleanUp() started" << std::endl;
		SaveGame();
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

	dt.Restart();
	// pêtla g³ówna
	m_done = false;
	while (!m_done)
	{
		ProcessEvents();
		if(dt.GetElapsedTime().AsSeconds() < 0.1f)
			Update(dt.GetElapsedTime());
		
		dt.Restart();
		
		Draw();
	}
	m_window.Close();
}

void App::Draw()
{
    //RYSOWANIE UWZGLEDNIAJAC KAMERE
	m_window.SetView(m_cam->GetView());
	m_window.Clear(sf::Color(255, 255, 255));

	if(!m_menu->IsActive() || m_menu->GetType() == 1)
	{
		for(int i = 0; i < m_gun->GetBullets(); i++)
		{
			m_window.Draw(m_gun->getBulletShape(i));
		}

		m_window.Draw(m_player->GetSprite());

		for (unsigned i = 0; i < creature.size(); ++i)
		{
			m_window.Draw(creature[i]->GetSprite());
		}

		for (unsigned i = 0; i < entity.size(); ++i)
		{
			m_window.Draw(entity[i]->GetSprite());
		}

		//Render mapy
		m_map->Draw(&m_window);
	}

	//RYSOWANIE STALYCH ELEMENTOW EKRANU
	m_window.SetView(m_window.GetDefaultView());
	if(!m_menu->IsActive() || m_menu->GetType() == 1)
	{
		m_hud->Draw(&m_window);
	}
	if(m_menu->IsActive()) m_menu->Draw(&m_window);
	m_window.Display();
}

void App::ProcessEvents()
{
	if (m_done)
	{ // je¿eli mamy zakoñczyæ, to pomijamy obs³ugê zdarzeñ
		return;
	}
 
	// przejrzymy kolejne zdarzenia z kolejki
	sf::Event Event;
	while (m_window.PollEvent(Event))
	{
		if(Event.Type == sf::Event::TextEntered && !m_menu->IsActive())
		{
			m_textInput += Event.Text.Unicode;

			if(m_textInput.find("ghost") != std::string::npos)
			{
				m_textInput.clear();
				m_player->ToggleGhost();
			}
		}
		else if(Event.Type == sf::Event::MouseMoved)
		{
			m_mPos = sf::Vector2f(static_cast<float>(Event.MouseMove.X), static_cast<float>(Event.MouseMove.Y));
			m_menu->SetMousePosition(m_mPos);
		}

		else if(Event.Type == sf::Event::MouseButtonPressed)
		{
			if(Event.Key.Code == sf::Mouse::Left)
			{
				if(!m_menu->IsActive())	m_gun->Shoot(m_window.ConvertCoords(static_cast<unsigned int>(m_mPos.x), static_cast<unsigned int>(m_mPos.y), 
													 m_cam->GetView()), sf::Vector2f(m_player->GetBox().Left + 8, m_player->GetBox().Top + 8));
				else m_menu->Click(m_done, m_state);

				if(m_state == 1) 
				{
					m_currentLevel = 1;
					LoadLevel();
				}
				if(m_state == 2) LoadGame();

				m_state = 0;
			}
		}
		else if(Event.Type == sf::Event::KeyPressed)
		{
			if(Event.Key.Code == sf::Keyboard::Escape)
			{
				m_menu->Toggle();
			}
		}
		else if(Event.Type == sf::Event::LostFocus) m_menu->OpenMenu();
	}

	if(!m_menu->IsActive())
	{
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::W) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Up)) m_player->Jump();
		else m_player->StopUp();

		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::A) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Left)) m_player->GoLeft();
		else m_player->StopLeft();

		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::D) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Right)) m_player->GoRight();
		else m_player->StopRight();

		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::S) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Down)) m_player->GoDown();
		else m_player->StopDown();
	}
}

void App::Update(sf::Time dt)
{
	if(m_menu->IsActive())
	{
		if (m_menu->GetType() == 0)
		{
			m_menu->SetContinue(SaveExist());
			CleanUp();
		}
		m_menu->Update();
	}

	if(!m_menu->IsActive())
	{
		m_player->Update(dt.AsMilliseconds());
		for (unsigned i = 0; i < creature.size(); ++i)
		{
			creature[i]->Update(dt.AsMilliseconds());
			m_player->CheckCreaturesAround(creature[i]);
		}
		for (unsigned i = 0; i < entity.size(); ++i)
		{
			entity[i]->UpdateSprite();
		}

		// WSZYSTKIE KOLIZJI DOTYCZ¥CE MAPY
		for(int j = 0; j < m_map->getMapHeight(); j++)
		{
			for(int i = 0; i < m_map->getMapWidth(); i++)
			{
				if(m_map->isSolid(i, j))
				{
					// MAP PLAYER
					if(CheckCollision(m_player->GetBox(), m_map->getBox(static_cast<float>(i), static_cast<float>(j))))
					{
						m_player->SolidCollision(m_map->getBox(static_cast<float>(i), static_cast<float>(j)));
					}
					// MAP MOB
					for (unsigned current = 0; current < creature.size(); ++current)
					{
						if (CheckCollision(creature[current]->GetBox(), m_map->getBox(static_cast<float>(i), static_cast<float>(j))))
						{
							creature[current]->SolidCollision(m_map->getBox(static_cast<float>(i), static_cast<float>(j)));
						}
					}
					// MAP BULLET
					for(int b = 0; b < m_gun->GetBullets(); b++)
					{
						if(CheckCollision(m_gun->getBulletBox(b), m_map->getBox(static_cast<float>(i), static_cast<float>(j))))
						{
							m_gun->KillBullet(b);
						}
					}
				}
			}
		}

		// ENTITY GRACZ
		for (unsigned current = 0; current < entity.size(); ++current)
		{
			if (CheckCollision(entity[current]->GetBox(), m_player->GetBox()))
			{
				if (m_player->EntityCollision(entity[current]) == 0)
					entity.erase(entity.begin() + current);
				else if (m_player->EntityCollision(entity[current]) == 2)
				{
					m_hp = m_player->GetHP();
					m_currentLevel += 1;
					LoadLevel();
				}
			}
		}
		// MOB GRACZ
		for (unsigned current = 0; current < creature.size(); ++current)
		{
			if (CheckCollision(creature[current]->GetBox(), m_player->GetBox()))
			{
				m_player->CreatureCollision(creature[current]);
			}
		}
		// MOB BULLET
		for (int b = 0; b < m_gun->GetBullets(); b++)
		{
			for (unsigned current = 0; current < creature.size(); ++current)
			{
				if (CheckCollision(m_gun->getBulletBox(b), creature[current]->GetBox()))
				{
					m_gun->KillBullet(b);
					creature[current]->Hurt();
					if (creature[current]->IsDead())
						creature.erase(creature.begin() + current);
					break;
				}
			}
		}

		m_gun->Update(dt.AsMilliseconds());

		m_hud->Update(m_player->GetHP());
	
		m_cam->Set(m_player->GetBox());
	}
}

bool App::CheckCollision(sf::FloatRect A, sf::FloatRect B)
{
	if(A.Intersects(B)) return true;
	else return false;
}

void App::SaveGame()
{
	Save* save = new Save();
	
	save->level = m_currentLevel;
	save->hp = m_player->GetHP();

	save->posX = m_player->GetBox().Left;
	save->posY = m_player->GetBox().Top;
	
	ZeroMemory(save->creatureData, sizeof(save->creatureData));
	ZeroMemory(save->entityData, sizeof(save->entityData));

	for (unsigned i = 0; i < creature.size(); ++i)
	{
		save->creatureData[i].x = creature[i]->GetBox().Left;
		save->creatureData[i].y = creature[i]->GetBox().Top;
		save->creatureData[i].type = creature[i]->GetType();
	}

	for (unsigned i = 0; i < entity.size(); ++i)
	{
		save->entityData[i].x = entity[i]->GetBox().Left;
		save->entityData[i].y = entity[i]->GetBox().Top;
		save->entityData[i].type = entity[i]->GetType();
	}

	std::ofstream file("save.dat", std::ios::binary);
	file.write((char*)(save), sizeof(Save));
	file.close();

	delete save;
}

bool App::LoadGame()
{
	std::ifstream file("save.dat", std::ios::binary);

	char* temp = new char[sizeof(Save)];
	file.read(temp, sizeof(Save));
	Save* save = (Save*)(temp);

	std::stringstream level;
	level << "data/maps/" << save->level << ".map";
	if(!m_map->LoadNextLevel(level.str())) 
	{
		std::cout << "Level: " << level << std::endl;
		std::cout << "No such level";
		return false;
	}
	std::cout << "lala1" << std::endl;

	m_player = new Player(sf::Vector2f(save->posX, save->posY), m_resMgr->getPlayerTexture(), save->hp);
	m_gun = new Gun();
	std::cout << "lala2" << std::endl;

	for (unsigned i = 0; i < ENT_MAX_SIZE; ++i)
	{
		if (save->creatureData[i].x == NULL) break;
		
			float x = save->creatureData[i].x;
			float y = save->creatureData[i].y;
			int type = save->creatureData[i].type;
			creature.push_back(new Creature(sf::Vector2f(x, y), type, m_resMgr->GetEntityTexture(type)));
		
	}
	std::cout << "lala3" << std::endl;

	for (unsigned i = 0; i < ENT_MAX_SIZE; ++i)
	{
		if (save->entityData[i].x == NULL) break;

			float x = save->entityData[i].x;
			float y = save->entityData[i].y;
			int type = save->entityData[i].type;
			entity.push_back(new Entity(sf::Vector2f(x, y), type, m_resMgr->GetEntityTexture(2)));
		
	}
	std::cout << "lala4" << std::endl;

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