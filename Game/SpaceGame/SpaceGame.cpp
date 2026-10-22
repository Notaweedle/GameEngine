#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "../Assets.h"
#include "Framework/Scene.h"
#include <string>
#include <memory>
#include <format>   
#include <Renderer/ParticleSystem.h>
#include <Renderer/ParticleManager.h>

using namespace nu;

bool SpaceGame::Initialize()
{
	SetWorkingDirectory("SpaceGame");
	Game::Initialize();
	m_scene = std::make_unique<nu::Scene>();

	auto& e = Engine::Get();
	TTF_Init();

	e.GetAudio().LoadSound("laser", "Audio/laserShoot.wav");
	e.GetAudio().LoadSound("music", "Audio/music.mp3");
	e.GetAudio().PlayMusic("music");

	m_font      = Resources().GetWithID<Font>("font48", "font.ttf", 48);
	m_fontSmall = Resources().GetWithID<Font>("font28", "font.ttf", 28);

	
	m_background = Resources().Get<Texture>("background.png", e.GetRenderer());
	e.GetParticleSystem().SetTexture(Resources().Get<Texture>("particle.png", e.GetRenderer()));

	
	m_titleText.SetFont(m_font);
	m_startText.SetFont(m_fontSmall);
	m_gameOverText.SetFont(m_font);
	m_restartText.SetFont(m_fontSmall);
	m_scoreText.SetFont(m_fontSmall);
	m_livesText.SetFont(m_fontSmall);
	m_finalScoreText.SetFont(m_fontSmall);

	m_titleText.Create(e.GetRenderer(), "ASTEROIDS", Color(1.0f, 1.0f, 1.0f));
	m_startText.Create(e.GetRenderer(), "Press SPACE to Start", Color(0.8f, 0.8f, 0.8f));
	m_gameOverText.Create(e.GetRenderer(), "GAME OVER", Color(1.0f, 0.3f, 0.3f));
	m_restartText.Create(e.GetRenderer(), "Press SPACE to Restart", Color(0.8f, 0.8f, 0.8f));

	return true;
}

void SpaceGame::Update(float dt)
{
	auto& e = Engine::Get();

	switch (m_state)
	{
	case GameState::StartGame:
	{
		if (e.GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			ResetGame();
			m_state = GameState::InGame;
		}
		break;
	}

	case GameState::InGame:
	{
		if (e.GetInput().GetKeyPressed(SDL_SCANCODE_F1)) {
			m_scene->SetDebugDraw(!m_scene->GetDebugDraw());
		}

		m_scene->Update(dt);
		e.GetParticleSystem().Update(dt);

		// wave spawning
		if (m_scene->GetActorsByTag("enemy").empty()) {

			m_waveCount++;
			SpaceGame::SpawnAtEdges( 5 * m_waveCount, 2560.0f, 1600.0f);
		}

		// collision outcomes (detection/resolution now lives in Scene::UpdateCollisions)
		m_score += 100 * m_scene->TakeEnemyKills();

		if (m_scene->TakePlayerHit()) {
			m_lives--;
			if (m_lives <= 0) {
				m_finalScoreText.Create(e.GetRenderer(), std::format("Score: {}" , std::to_string(m_score)) ,Color(0.8f, 0.8f, 0.8f));
				m_state = GameState::GameOver;
			}
			else {
				RespawnPlayer();
			}
		}

		
		if (m_score != m_lastScore) {
			m_scoreText.Create(e.GetRenderer(), std::format("Score: {}", m_score), Color(1.0f, 1.0f, 1.0f));
			m_lastScore = m_score;
		}
		if (m_lives != m_lastLives) {
			m_livesText.Create(e.GetRenderer(), std::format("Lives: {}", m_lives), Color(1.0f, 1.0f, 1.0f));
			m_lastLives = m_lives;
		}
		break;
	}

	case GameState::GameOver:
	{
		e.GetParticleSystem().Update(dt);

		if (e.GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			ResetGame();
			m_state = GameState::InGame;
		}
		break;
	}
	}
}

void SpaceGame::Draw()
{
	auto& e = Engine::Get();
	float cx = 2560.0f / 2.0f;
	float cy = 1600.0f / 2.0f;

	e.GetRenderer().Clear();

	if (m_background) e.GetRenderer().DrawTexture(m_background.get(), cx, cy, 0.0f, 1.0f);

	switch (m_state)
	{
	case GameState::StartGame:
		m_titleText.Draw(e.GetRenderer(), cx - m_titleText.GetWidth() / 2.0f, cy - 80.0f);
		m_startText.Draw(e.GetRenderer(), cx - m_startText.GetWidth() / 2.0f, cy + 20.0f);
		break;

	case GameState::InGame:
		m_scene->Draw(e.GetRenderer());
		e.GetParticleSystem().Draw(e.GetRenderer());
		m_scoreText.Draw(e.GetRenderer(), 20.0f, 20.0f);
		m_livesText.Draw(e.GetRenderer(), 20.0f, 55.0f);
		break;

	case GameState::GameOver:
		e.GetParticleSystem().Draw(e.GetRenderer());
		m_gameOverText.Draw(e.GetRenderer(), cx - m_gameOverText.GetWidth() / 2.0f, cy - 80.0f);
		m_finalScoreText.Draw(e.GetRenderer(), cx - m_finalScoreText.GetWidth() / 2.0f, cy + 20.0f);
		m_restartText.Draw(e.GetRenderer(), cx - m_restartText.GetWidth() / 2.0f, cy + 60.0f);
		break;
	}

	e.GetRenderer().Present();
}

void SpaceGame::SpawnAtEdges(int count, float worldW, float worldH) {

    const float MARGIN = 25.0f;

    for (int i = 0; i < count; i++) {
        float x = 0.f;
        float y = 0.f;
        int edge = RandomInt() % 4;

        switch (edge) {
        case 0: x = nu::math::randomf(0.0f, worldW); y = -MARGIN;          break;
        case 1: x = nu::math::randomf(0.0f, worldW); y = worldH + MARGIN;  break;
        case 2: x = -MARGIN;          y = nu::math::randomf(0.0f, worldH);  break;
        case 3: x = worldW + MARGIN;  y = nu::math::randomf(0.0f, worldH);  break;
        }

       
        const std::string type = (math::randomf(0.0f, 1.0f) <= 0.1f) ? "RainDrop" : "yeedi";

        auto enemy = Factory::Instance().Create<Actor>(type);
        if (enemy)
        {
            enemy->setPosistion({ x, y });
            m_scene->AddActor(std::move(enemy));
        }
    }
}

void SpaceGame::ResetGame()
{
	
	m_scene->RemoveActors();

	m_scene->Load("data/data.json");





	m_score = 0;
	m_lives = 3;
	m_waveCount = 1;
	m_lastScore = -1;  
	m_lastLives = -1;

	RespawnPlayer();
	
	SpaceGame::SpawnAtEdges(5, 2560.0f, 1600.0f);
}




void SpaceGame::RespawnPlayer()
{
	auto player = Factory::Instance().Create<Actor>("PlayerPrototype");
	player->setName("Player");
	player->setPosistion({ 1280.0f, 800.0f });
	m_scene->AddActor(std::move(player));
}


