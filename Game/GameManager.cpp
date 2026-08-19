#include "GameManager.h"
#include "Engine.h"
#include "Player.h"
#include "Assets.h"

#include <string>
#include <memory>
#include <format>   
#include <ParticleSystem.h>
#include <ParticleManager.h>

using namespace nu;

void GameManager::Initialize()
{
	auto& e = Engine::Get();

	e.GetAudio().LoadSound("laser", "Assets/laserShoot.wav");
	e.GetAudio().LoadSound("music", "Assets/music.mp3");
	e.GetAudio().PlayMusic("music");

	m_font      = Resources().GetWithID<Font>("font48", "Assets/font.ttf", 48);
	m_fontSmall = Resources().GetWithID<Font>("font28", "Assets/font.ttf", 28);

	// background sprite + particle sprite
	m_background = Resources().Get<Texture>("Assets/background.png", e.GetRenderer());
	e.GetParticleSystem().SetTexture(Resources().Get<Texture>("Assets/particle.png", e.GetRenderer()));

	
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
				m_finalScoreText.Create(e.GetRenderer(), std::format("Score: {}" , std::to_string(m_score)) ,Color(0.8f, 0.8f, 0.8f));
				m_state = GameState::GameOver;
			}
			else {
				RespawnPlayer();
			}
		}

		// update HUD text
		m_scoreText.Create(e.GetRenderer(), std::format("Score: {}" , std::to_string(m_score)), Color(1.0f, 1.0f, 1.0f));
		m_livesText.Create(e.GetRenderer(), std::format("Lives: {}" , std::to_string(m_lives)), Color(1.0f, 1.0f, 1.0f));
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

	// background sprite fills the screen (2560x1600), drawn behind everything
	if (m_background) e.GetRenderer().DrawTexture(m_background.get(), cx, cy, 0.0f, 1.0f);

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
				auto pd = enmy_expl();
				pd.position = enemy->getTranform().position;
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
			auto pd = player_expl();
			pd.position = player->getTranform().position;
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

	RespawnPlayer();
	
	Enemy::SpawnAtEdges(m_scene, 5, 2560.0f, 1600.0f);
}

void GameManager::RespawnPlayer()
{
	

	PlayerDesc playerDesc;
	playerDesc.speed = 1500.f;
	playerDesc.transform.position = { 2560.0f / 2, 1600.0f / 2 };
	playerDesc.transform.rotation = 0.f;
	playerDesc.transform.scale = 3.f;
	playerDesc.tag = "player";
	playerDesc.name = "Player";
	/*playerDesc.model = *Assets::model_player;*/
	playerDesc.texture = Resources().Get<Texture>("Assets/PlayerShip.png", Engine::Get().GetRenderer());

	auto player = std::make_unique<Player>(playerDesc);
	player->SetRadius(30.f);
	m_scene.AddActor(std::move(player));
}


