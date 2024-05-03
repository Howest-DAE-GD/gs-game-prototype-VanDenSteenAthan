#include "pch.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Shade.h"

Game::Game( const Window& window ) 
	:BaseGame{ window },
	m_MousePos{}
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
}

void Game::Cleanup( )
{
	delete m_Player;
}

void Game::Update( float elapsedSec )
{
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
				///GAME DEAD
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
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	m_MousePos = Point2f{ (float)e.x, (float)e.y };
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	Point2f mousePos{ (float) e.x, (float) e.y };
	m_Player->ProcessMouseDownEvent(mousePos);
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
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
	return new Enemy(rand() % (int)GetViewPort().width, rand() % (int)GetViewPort().height, Shade((ShadeType)(rand() % 4)));
}