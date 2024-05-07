#include "pch.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Shade.h"
#include "Texture.h"

Game::Game( const Window& window ) 
	:BaseGame{ window },
	m_MousePos{},
	m_GameIsRunning{true}
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_Player = new Player(50.f, 50.f, 50.f);
	for (int i{ 0 }; i < 10; ++i)
	{
		m_enemies.push_back(CreateNewEnemy());
	}
	m_txtDead = new Texture("You got an identity crisis!", TXT_FONT_FILE, 36.f, Color4f{ 1.f, 0.42f, 0.42f, 1.f });
	m_txtRestart = new Texture("Press 'R' to restart.", TXT_FONT_FILE, 28.f, Color4f{ 1.f, 0.42f, 0.42f, 1.f });
}

void Game::Cleanup( )
{
	delete m_Player;
	delete m_txtDead;
	delete m_txtRestart;
}

void Game::Update( float elapsedSec )
{
	if (!m_GameIsRunning) return;
	m_Player->Update(elapsedSec, GetViewPort());

	for (int i{ 0 }; i < m_enemies.size(); ++i)
	{
		m_enemies[i]->Update(elapsedSec, GetViewPort());
		if (utils::IsOverlapping(m_Player->GetRect(), m_enemies[i]->GetRect()))
		{
			m_Player->Attack(m_enemies[i]->GetShade());
			const int PLAYER_LIVES{ m_Player->GetLives()};
			
			if (PLAYER_LIVES > 0)
			{
				delete m_enemies[i];
				m_enemies.erase(m_enemies.begin() + i);
				m_enemies.push_back(CreateNewEnemy());
			}
			else
			{
				m_GameIsRunning = false;
				m_enemies.clear();
				break;
			}
		}
	}
}

void Game::Draw( ) const
{
	ClearBackground( );

	for (Enemy* enemy : m_enemies)
	{
		enemy->Draw();
	}

	m_Player->Draw(m_MousePos, GetViewPort());

	if (!m_GameIsRunning)
	{
		const Rectf vp{ GetViewPort() };
		m_txtDead->Draw(Point2f{ vp.width / 2 - m_txtDead->GetWidth() / 2, vp.height / 2 - m_txtDead->GetHeight() / 2 + 25.f});
		m_txtRestart->Draw(Point2f{ vp.width / 2 - m_txtRestart->GetWidth() / 2, vp.height / 2 - m_txtRestart->GetHeight() / 2 - m_txtDead->GetHeight()});
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	if (m_GameIsRunning) return;
	switch (e.keysym.sym)
	{
		case SDLK_r:
			for (int i{ 0 }; i < 10; ++i)
			{
				m_enemies.push_back(CreateNewEnemy());
			}
			delete m_Player;
			m_Player = new Player(50.f, 50.f, 50.f);

			m_GameIsRunning = true;
			break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	if (!m_GameIsRunning) return;
	m_MousePos = Point2f{ (float)e.x, (float)e.y };
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	if (!m_GameIsRunning) return;
	Point2f mousePos{ (float) e.x, (float) e.y };
	m_Player->ProcessMouseDownEvent(mousePos);
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	if (!m_GameIsRunning) return;
	Point2f mousePos{ (float) e.x, (float) e.y };
	m_Player->ProcessMouseUpEvent(mousePos);
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.30f, 0.35f, 0.35f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

Enemy* Game::CreateNewEnemy()
{
	return new Enemy(rand() % (int)GetViewPort().width, rand() % (int)GetViewPort().height);
}