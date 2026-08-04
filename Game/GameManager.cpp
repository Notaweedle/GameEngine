#include "GameManager.h"
#include "Engine.h"
#include "Player.h"
#include "Assets.h"

#include <string>
#include <memory>
#include <format>   // std::format used below
#include <ParticleSystem.h>

using namespace nu;

void GameManager::Initialize()
{
	auto& e = Engine::Get();

	e.GetAudio().LoadSound("laser", "Assets/laserShoot.wav");
	e.GetAudio().LoadSound("music", "Assets/music.mp3");
	e.GetAudio().PlayMusic("music");

	m_font.Load("Assets/font.ttf", 48);
	m_fontSmall.Load("Assets/font.ttf", 28);

	m_titleText.Create(e.GetRenderer(), "ASTEROIDS", m_font, 255, 255, 255);
	m_startText.Create(e.GetRenderer(), "Press SPACE to Start", m_fontSmall, 200, 200, 200);
	m_gameOverText.Create(e.GetRenderer(), "GAME OVER", m_font, 255, 80, 80);
	m_restartText.Create(e.GetRenderer(), "Press SPACE to Restart", m_fontSmall, 200, 200, 200);
}

void GameManager::Update(float dt)
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
			m_scene.SetDebugDraw(!m_scene.GetDebugDraw());
		}

		m_scene.Update(dt);
		e.GetParticleSystem().Update(dt);

		// wave spawning
		if (m_scene.GetActorsByTag("enemy").empty()) {
			m_waveCount++;
			Enemy::SpawnAtEdges(m_scene, 5 * m_waveCount, 2560.0f, 1600.0f);
		}

		// collisions
		if (CheckCollisions()) {
			if (m_lives <= 0) {
				m_finalScoreText.Create(e.GetRenderer(), std::format("Score: {}" , std::to_string(m_score)), m_fontSmall, 200, 200, 200);
				m_state = GameState::GameOver;
			}
			else {
				RespawnPlayer();
			}
		}

		// update HUD text
		m_scoreText.Create(e.GetRenderer(), std::format("Score: {}" , std::to_string(m_score)), m_fontSmall, 255, 255, 255);
		m_livesText.Create(e.GetRenderer(), std::format("Lives: {}" , std::to_string(m_lives)), m_fontSmall, 255, 255, 255);
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

void GameManager::Draw()
{
	auto& e = Engine::Get();
	float cx = 2560.0f / 2.0f;
	float cy = 1600.0f / 2.0f;

	e.GetRenderer().Clear();

	switch (m_state)
	{
	case GameState::StartGame:
		m_titleText.Draw(e.GetRenderer(), cx - m_titleText.GetWidth() / 2.0f, cy - 80.0f);
		m_startText.Draw(e.GetRenderer(), cx - m_startText.GetWidth() / 2.0f, cy + 20.0f);
		break;

	case GameState::InGame:
		m_scene.Draw(e.GetRenderer());
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

bool GameManager::CheckCollisions()
{
	std::vector<Actor*> enemies = m_scene.GetActorsByTag("enemy");

	for (Actor* bullet : m_scene.GetActorsByTag("bullet")) {
		for (Actor* enemy : enemies) {
			if (enemy->IsDestroyed()) continue;

			if (bullet->CheckCollision(*enemy)) {
				ParticleDesc pd;
				pd.position = enemy->getTranform().position;
				pd.speed = 150.0f;
				pd.speedVariance = 80.0f;
				pd.lifetime = 0.8f;
				pd.lifetimeVariance = 0.3f;
				pd.color = Color{ 1.0f, 0.5f, 0.0f, 1.0f };
				pd.count = 20;
				Engine::Get().GetParticleSystem().Emit(pd);

				bullet->Destroy();
				static_cast<Enemy*>(enemy)->OnKilled();
				m_score += 100;
				break;
			}
		}
	}

	Player* player = m_scene.GetActorByName<Player>("Player");
	if (player == nullptr) return false;

	for (Actor* enemy : enemies) {
		if (!enemy->IsDestroyed() && player->CheckCollision(*enemy)) {
			ParticleDesc pd;
			pd.position = player->getTranform().position;
			pd.speed = 200.0f;
			pd.speedVariance = 100.0f;
			pd.lifetime = 1.0f;
			pd.lifetimeVariance = 0.4f;
			pd.color = Color{ 1.0f, 0.2f, 0.2f, 1.0f };
			pd.count = 30;
			Engine::Get().GetParticleSystem().Emit(pd);

			enemy->Destroy();
			player->Destroy();
			m_lives--;
			return true;
		}
	}

	return false;
}

void GameManager::ResetGame()
{
	m_scene = Scene();
	m_score = 0;
	m_lives = 3;
	m_waveCount = 1;

	auto player = std::make_unique<Player>(2000.0f, Tranform{ Vector2{2560.0f / 2, 1600.0f / 2}, 0.0f, 15.0f }, *Assets::model_player);
	player->setName("Player");
	player->setTag("player");
	m_scene.AddActor(std::move(player));

	Enemy::SpawnAtEdges(m_scene, 5, 2560.0f, 1600.0f);
}

void GameManager::RespawnPlayer()
{
	auto player = std::make_unique<Player>(2000.0f, Tranform{ Vector2{2560.0f / 2, 1600.0f / 2}, 0.0f, 15.0f }, *Assets::model_player);
	player->setName("Player");
	player->setTag("player");
	m_scene.AddActor(std::move(player));
}
