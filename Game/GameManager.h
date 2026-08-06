#pragma once
#include <Scene.h>
#include <Font.h>
#include <Text.h>

enum class GameState { StartGame, InGame, GameOver };

class GameManager
{
public:
	void Initialize();
	void Update(float dt);
	void Draw();

	bool IsQuit() const { return m_quit; }

	// fonts (shared resources; the Text objects reference these)
	nu::res_t<nu::Font> m_font;
	nu::res_t<nu::Font> m_fontSmall;

	// static text
	nu::Text m_titleText;
	nu::Text m_startText;
	nu::Text m_gameOverText;
	nu::Text m_restartText;

	// dynamic text
	nu::Text m_scoreText;
	nu::Text m_livesText;
	nu::Text m_finalScoreText;
protected:
	bool CheckCollisions();
	void ResetGame();
	void RespawnPlayer();

	nu::Scene m_scene;
	GameState m_state = GameState::StartGame;

	int m_score = 0;
	int m_lives = 3;
	int m_waveCount = 1;
	bool m_quit = false;

	
};
