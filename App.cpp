#include "App.h"
bool App::Init()
{
	m_window.Create(sf::VideoMode(m_screenWidth, m_screenHeight, 32), "Platform Fighter v0.4.6", sf::Style::Titlebar);

	m_window.SetFramerateLimit(60);
	m_window.EnableKeyRepeat(false);

	m_resMgr = new ResourceManager("data/gfx/sheet.png", "data/gfx/player.png", "data/gfx/entSheet.png", "data/gfx/hudSheet.png", "data/gfx/guiSheet.png");

	m_hud = new HUD(m_resMgr->getHudTexture());

	m_map = new Map(m_resMgr);
	if(!m_map->LoadNextLevel("data/maps/1.map")) return false;

	m_player = new Player(m_map->getPlayerPos(), m_resMgr->getPlayerTexture());

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
				entity.push_back(new Entity(sf::Vector2f(static_cast<float>(i*16), static_cast<float>(j*16)), type, m_resMgr->GetEntityTexture(1)));
			}
		}
	}

	m_menu = new Menu(m_resMgr->GetGuiTexture());
	m_gun = new Gun();
	m_cam = new Camera(sf::Vector2i(m_window.GetWidth(), m_window.GetHeight()), sf::Vector2i(m_map->getMapWidth(), m_map->getMapHeight()));

	m_pauseShape.SetFillColor(sf::Color(0, 0, 0, 192));
	m_pauseShape.SetSize(sf::Vector2f(static_cast<float>(m_screenWidth), static_cast<float>(m_screenHeight)));
	return true;
}

void App::Run()
{
	if(!Init()) m_done = true;
	sf::Clock dt;

	dt.Restart();
	// p�tla g��wna
	m_done = false;
	while (!m_done)
	{
		if (m_paused) ProcessEvents();
		else
		{

			ProcessEvents();
			if(dt.GetElapsedTime().AsSeconds() < 0.1f)
				Update(dt.GetElapsedTime());
		
			dt.Restart();
		
			Draw();
		}
	}
	m_window.Close();
}

void App::Draw()
{
    //RYSOWANIE UWZGLEDNIAJAC KAMERE
	m_window.SetView(m_cam->GetView());
	
	m_window.Clear(sf::Color(255, 255, 255));

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

	//RYSOWANIE STALYCH ELEMENTOW EKRANU
	m_window.SetView(m_window.GetDefaultView());
	m_hud->Draw(&m_window);
	m_menu->Draw(&m_window);

	if(m_paused) m_window.Draw(m_pauseShape);
	m_window.Display();
}

void App::ProcessEvents()
{
	if (m_done)
	{ // je�eli mamy zako�czy�, to pomijamy obs�ug� zdarze�
		return;
	}
 
	// przejrzymy kolejne zdarzenia z kolejki
	sf::Event Event;
	while (m_window.PollEvent(Event))
	{
		if(Event.Type == sf::Event::TextEntered)
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
		}

		else if(Event.Type == sf::Event::MouseButtonPressed)
		{
			if(Event.Key.Code == sf::Mouse::Left)
			{
				m_gun->Shoot(m_window.ConvertCoords(static_cast<unsigned int>(m_mPos.x), static_cast<unsigned int>(m_mPos.y), 
							 m_cam->GetView()), sf::Vector2f(m_player->GetBox().Left + 8, m_player->GetBox().Top + 8));
			}
		}
		else if(Event.Type == sf::Event::KeyPressed)
		{
			//if(Event.Key.Code == sf::Keyboard::N) m_player->ToggleNoclip();

			if(Event.Key.Code == sf::Keyboard::Escape)
			{   // zamkni�cie okna
				m_done = true;
				return;
			}
		}
		else if(Event.Type == sf::Event::LostFocus) m_paused = true;
		else if(Event.Type == sf::Event::GainedFocus) m_paused = false;
	}

	if(sf::Keyboard::IsKeyPressed(sf::Keyboard::W) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Up)) m_player->Jump();
	else m_player->StopUp();

	if(sf::Keyboard::IsKeyPressed(sf::Keyboard::A) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Left)) m_player->GoLeft();
	else m_player->StopLeft();

	if(sf::Keyboard::IsKeyPressed(sf::Keyboard::D) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Right)) m_player->GoRight();
	else m_player->StopRight();

	if(sf::Keyboard::IsKeyPressed(sf::Keyboard::S) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Down)) m_player->GoDown();
	else m_player->StopDown();
}

void App::Update(sf::Time dt)
{
	m_player->Update(dt.AsMilliseconds());
	for (unsigned i = 0; i < creature.size(); ++i)
	{
		creature[i]->Update(dt.AsMilliseconds());
	}
	for (unsigned i = 0; i < entity.size(); ++i)
	{
		entity[i]->UpdateSprite();
	}

	// WSZYSTKIE KOLIZJI DOTYCZ�CE MAPY
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

bool App::CheckCollision(sf::FloatRect A, sf::FloatRect B)
{
	if(A.Intersects(B)) return true;
	else return false;
}

