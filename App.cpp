#include "App.h"
bool App::Init()
{
	m_window.Create(sf::VideoMode(m_screenWidth, m_screenHeight, 32), "Platform Fighter v0.2.1");

	m_window.SetFramerateLimit(60);
	m_window.EnableKeyRepeat(false);

	m_resMgr = new ResourceManager("sheet.png", "player.png");

	m_map = new Map(m_resMgr);
	if(!m_map->LoadNextLevel("data/maps/1.map")) return false;

	m_player = new Player(m_map->getPlayerPos(), m_resMgr->getPlayerTexture());
	std::cout << "przed" << std::endl;
	int k = 0;
		for(int j = 0; j < m_map->getMapWidth(); j++)
		{
			for(int i = 0; i < m_map->getMapHeight(); i++)
			{
				if (m_map->getEntity(i, j) == 1)
				{
					std::cout << "Mob created." << std::endl;
					std::cout << "x: " << i*16 << std::endl;
					std::cout << "y: " << j*16 << std::endl;
					m_mob1[k] = new Mob1(sf::Vector2f(i*16, j*16));
					++k;
				}
			}
		}
	std::cout << "po" << std::endl;
	m_gun = new Gun();
	m_cam = new Camera(sf::Vector2i(m_window.GetWidth(), m_window.GetHeight()), sf::Vector2i(m_map->getMapWidth(), m_map->getMapHeight()));

	m_pauseShape.SetFillColor(sf::Color(0, 0, 0, 192));
	m_pauseShape.SetSize(sf::Vector2f(m_screenWidth, m_screenHeight));
	return true;
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

	for(int i = 0; i < BULLET_ARRAY_SIZE; i++)
	{
		if(m_gun->getBulletAlive(i)) m_window.Draw(m_gun->getBulletShape(i));
	}
	m_window.Draw(m_player->GetShape());

	for (int i = 0; i < CREATURE_COUNT; ++i)
	{
		m_window.Draw(m_mob1[i]->GetShape());
	}

	//Render mapy
	m_map->Draw(&m_window);

	//RYSOWANIE STALYCH ELEMENTOW EKRANU
	m_window.SetView(m_window.GetDefaultView());


	if(m_paused) m_window.Draw(m_pauseShape);
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
		if (Event.Type == sf::Event::Closed)
		{   // zamkniêcie okna
			m_done = true;
			return;
		}

		else if(Event.Type == sf::Event::MouseMoved)
		{
			m_mPos = sf::Vector2f(Event.MouseMove.X, Event.MouseMove.Y);
		}

		else if(Event.Type == sf::Event::MouseButtonPressed)
		{
			if(Event.Key.Code == sf::Mouse::Left)
			{
				m_gun->Shoot(m_window.ConvertCoords(m_mPos.x, m_mPos.y, m_cam->GetView()), sf::Vector2f(m_player->GetBox().Left + 8, m_player->GetBox().Top + 8));
			}
		}
		else if(Event.Type == sf::Event::KeyPressed)
		{
			if(Event.Key.Code == sf::Keyboard::N) m_player->ToggleNoclip();
		}
		else if(Event.Type == sf::Event::LostFocus) m_paused = true;
		else if(Event.Type == sf::Event::GainedFocus) m_paused = false;
	}

	if(sf::Keyboard::IsKeyPressed(sf::Keyboard::W) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Up)) m_player->Jump();
	
	if(sf::Keyboard::IsKeyPressed(sf::Keyboard::A) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Left)) m_player->GoLeft();
	else m_player->StopLeft();

	if(sf::Keyboard::IsKeyPressed(sf::Keyboard::D) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Right)) m_player->GoRight();
	else m_player->StopRight();
}

void App::Update(sf::Time dt)
{
	m_player->Update(dt.AsMilliseconds());
	for (int i = 0; i < CREATURE_COUNT; ++i)
	{
		m_mob1[i]->Update(dt.AsMilliseconds());
	}

	for(int j = 0; j < m_map->getMapHeight(); j++)
	{
		for(int i = 0; i < m_map->getMapWidth(); i++)
		{
			if(m_map->isSolid(i, j))
			{
				if(CheckCollision(m_player->GetBox(), m_map->getBox(i, j)))
				{
					m_player->SolidCollision(m_map->getBox(i, j));
				}
				
				for (int current = 0; current < CREATURE_COUNT; ++current)
				{
					if (CheckCollision(m_mob1[current]->GetBox(), m_map->getBox(i, j)))
					{
						m_mob1[current]->SolidCollision(m_map->getBox(i, j));
					}
					if (CheckCollision(m_mob1[current]->GetBox(), m_player->GetBox()))
					{
						m_player->CreatureCollision(m_mob1[current]);
					}
				}
				
				for(int b = 0; b < BULLET_ARRAY_SIZE; b++)
				{
					if(CheckCollision(m_gun->getBulletBox(b), m_map->getBox(i, j)))
					{
						m_gun->KillBullet(b);
					}
				}
			}
		}
	}
	m_gun->Update(dt.AsMilliseconds());

	m_cam->Set(m_player->GetBox());
}

bool App::CheckCollision(sf::FloatRect A, sf::FloatRect B)
{
	if(A.Intersects(B)) return true;
	else return false;
}

