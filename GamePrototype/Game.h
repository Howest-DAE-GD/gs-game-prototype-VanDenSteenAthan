#pragma once
#include "BaseGame.h"
#include "vector"
class Player;
class Enemy;
class Texture;
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	// OWN MEMBERS
	Player* m_Player;
	Point2f m_MousePos;
	std::vector<Enemy*> m_enemies;

	Texture* m_txtDead;
	Texture* m_txtRestart;
	const std::string TXT_FONT_FILE{ "Painter-LxXg.ttf" };

	bool m_GameIsRunning;
	Enemy* CreateNewEnemy();
};