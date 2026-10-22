#pragma once
#include <Framework/Game.h>
#include <Framework/Scene.h>
#include <Renderer/Font.h>
#include <Renderer/Text.h>
#include <Renderer/Texture.h>

enum class GameState { StartGame, InGame, GameOver };

class SpaceGame : public nu::Game
{
public:
	bool Initialize() override;
	void Update(float dt) override;
	void Draw() override;

	bool IsQuit() const { return m_quit; }

	// background sprite
	nu::res_t<nu::Texture> m_background;

	// fonts
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
	void ResetGame();
	void SpawnAtEdges(int count, float worldW, float worldH);
	void RespawnPlayer();

	
	GameState m_state = GameState::StartGame;

	int m_score = 0;
	int m_lives = 3;
	int m_waveCount = 1;
	bool m_quit = false;

	int m_lastScore = -1;
	int m_lastLives = -1;
};
