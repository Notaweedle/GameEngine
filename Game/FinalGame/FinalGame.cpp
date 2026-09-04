#include "FinalGame.h"
#include "Engine.h"
#include <Framework/Actor.h>
#include <Renderer/Tilemap.h>
#include <Resources/ResourceManager.h>
#include <Core/Factory.h>
#include <Core/StringUtil.h>
#include <Core/Color.h>
#include <Components/SpriteRendererComponent.h>
#include <Renderer/ParticleSystem.h>
#include <Renderer/Texture.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "../SpriteGame/PlayerController.h"
#include <memory>
#include <string>
#include <iostream>

using namespace nu;

static const float kAttackRange = 220.0f;   // melee reach in pixels
static const float kChaseSpeed  = 130.0f;   // enemy chase speed (px/sec)
static const float kHurtCooldown = 1.0f;    // seconds of i-frames after a hit

// emit a quick particle burst at a world position
static void EmitBurst(const Vector2& pos, const Color& color, int count, float speed)
{
	ParticleDesc pd;
	pd.position = pos;
	pd.speed = speed;
	pd.speedVariance = speed * 0.5f;
	pd.lifetime = 0.7f;
	pd.lifetimeVariance = 0.3f;
	pd.color = color;
	pd.count = count;
	Engine::Get().GetParticleSystem().Emit(pd);
}

static Vector2 ObjectToWorld(res_t<Tilemap> map, Actor* tilemapActor, const Tilemap::TileObject& obj)
{
	float mapCx = obj.x + obj.width * 0.5f;
	
	float mapCy = (obj.gid != 0) ? (obj.y - obj.height * 0.5f)
	                             : (obj.y + obj.height * 0.5f);
	Vector2 base = tilemapActor->getTransform().position;
	float   scale = tilemapActor->getTransform().scale;
	return Vector2{
		base.x + (mapCx - map->GetOriginX()) * scale,
		base.y + (mapCy - map->GetOriginY()) * scale
	};
}

bool FinalGame::Initialize()
{
	SetWorkingDirectory("FinalGame");   // -> Assets/FinalGame
	Game::Initialize();

	auto& e = Engine::Get();
	TTF_Init();
	m_font = Resources().GetWithID<Font>("winfont", "Font/font.ttf", 64);
	e.GetAudio().LoadSound("attack", "Sound/WAV/AttackSound_.wav");
	e.GetAudio().LoadSound("music", "Sound/WAV/Dungeon_1.wav");
	e.GetAudio().PlayMusic("music");

	m_winText.SetFont(m_font);
	m_winText.Create(e.GetRenderer(), "YOU WIN!", Color(1.0f, 0.9f, 0.2f));
	m_gameOverText.SetFont(m_font);
	m_gameOverText.Create(e.GetRenderer(), "GAME OVER  -  Press R", Color(1.0f, 0.3f, 0.3f));
	m_hpText.SetFont(m_font);
	m_keyText.SetFont(m_font);

	e.GetParticleSystem().SetTexture(Resources().Get<Texture>("../SpaceGame/particle.png", e.GetRenderer()));

	LoadLevel("Data/dang1_scene.json", "Data/dang1.tmj");
	return true;
}

void FinalGame::LoadLevel(const std::string& sceneJson, const std::string& tmjPath)
{
	m_tmjPath = tmjPath;
	m_hasKey = false;
	m_skeletonsSpawned = false;
	m_bossSpawned = false;
	m_goldKeyDropped = false;
	m_hasGoldKey = false;
	m_bossHealth = 3;
	m_uiLastKeyState = -1; 

	m_scene = std::make_unique<Scene>();
	m_scene->Load(sceneJson);

	SpawnFromObjects();
}

void FinalGame::SpawnFromObjects()
{
	res_t<Tilemap> map = Resources().Get<Tilemap>(m_tmjPath, Engine::Get().GetRenderer());
	if (!map) return;

	Actor* tilemapActor = m_scene->GetActorByName<Actor>("Tilemap");
	if (!tilemapActor) return;

	for (const auto& obj : map->GetObjects())
	{
		if (obj.name.empty()) continue;

		auto actor = Factory::Instance().Create<Actor>(obj.name);
		if (!actor) continue;                          // markers (spawn_point, etc.) have no prototype

		actor->setPosistion(ObjectToWorld(map, tilemapActor, obj));

		if (obj.gid != 0)
		{
			if (auto* sr = actor->GetComponent<SpriteRendererComponent>())
				sr->SetTile(map->GetTilesetTexture(), map->GetGidRect(obj.gid));
		}

		m_scene->AddActor(std::move(actor));
	}
}

void FinalGame::SpawnSkeletons()
{
	res_t<Tilemap> map = Resources().Get<Tilemap>(m_tmjPath, Engine::Get().GetRenderer());
	if (!map) return;
	Actor* tilemapActor = m_scene->GetActorByName<Actor>("Tilemap");
	if (!tilemapActor) return;

	int count = 0;
	for (const auto& obj : map->GetObjects())
	{
		if (!EqualsIgnoreCase(obj.name, "spawn_point")) continue;

		auto skeleton = Factory::Instance().Create<Actor>("Skeleton");
		if (!skeleton) continue;
		skeleton->setPosistion(ObjectToWorld(map, tilemapActor, obj));
		m_scene->AddActor(std::move(skeleton));
		count++;
	}
	std::cout << "[FinalGame] spawn_flag crossed -> spawned " << count << " skeletons\n";
}

void FinalGame::SpawnBoss()
{
	res_t<Tilemap> map = Resources().Get<Tilemap>(m_tmjPath, Engine::Get().GetRenderer());
	if (!map) return;
	Actor* tilemapActor = m_scene->GetActorByName<Actor>("Tilemap");
	if (!tilemapActor) return;

	for (const auto& obj : map->GetObjects())
	{
		if (!EqualsIgnoreCase(obj.name, "spawn_pt_boss")) continue;

		auto boss = Factory::Instance().Create<Actor>("Boss");
		if (!boss) return;
		Vector2 world = ObjectToWorld(map, tilemapActor, obj);
		boss->setPosistion(world);
		m_bossPos = world;
		m_scene->AddActor(std::move(boss));

		// dramatic spawn burst
		EmitBurst(world, Color{ 0.6f, 0.1f, 0.8f, 1.0f }, 60, 350.0f);
		EmitBurst(world, Color{ 1.0f, 1.0f, 1.0f, 1.0f }, 30, 200.0f);
		return;   // one boss
	}
}

void FinalGame::SpawnGoldKey(const Vector2& pos)
{
	auto gkey = Factory::Instance().Create<Actor>("GoldKey");
	if (!gkey) return;
	gkey->setPosistion(pos);
	m_scene->AddActor(std::move(gkey));
}

void FinalGame::DoAttack(Actor* player)
{
	


	Vector2 pp = player->getTransform().position;
	Actor* boss = m_scene->GetActorByName<Actor>("boss");
	nu::Engine::Get().GetAudio().PlaySound("attack");

	for (Actor* enemy : m_scene->GetActorsByTag<Actor>("enemy"))
	{
		if (enemy == boss) continue;
		if ((enemy->getTransform().position - pp).Length() <= kAttackRange)
		{
			EmitBurst(enemy->getTransform().position, Color{ 0.9f, 0.9f, 1.0f, 1.0f }, 20, 200.0f);
			enemy->Destroy();
		}
	}

	if (boss && !boss->IsDestroyed() &&
		(boss->getTransform().position - pp).Length() <= kAttackRange)
	{
		m_bossPos = boss->getTransform().position;
		if (--m_bossHealth <= 0)
		{
			EmitBurst(m_bossPos, Color{ 0.6f, 0.1f, 0.8f, 1.0f }, 50, 320.0f);   // death
			boss->Destroy();
		}
		else
		{
			EmitBurst(m_bossPos, Color{ 1.0f, 0.3f, 0.3f, 1.0f }, 18, 180.0f);   // took damage
		}
	}
}


void FinalGame::UpdateEnemies(Actor* player, float dt)
{
	Vector2 pp = player->getTransform().position;

	for (Actor* enemy : m_scene->GetActorsByTag<Actor>("enemy"))
	{
		Vector2 ep = enemy->getTransform().position;
		Vector2 to = pp - ep;
		float dist = to.Length();
		if (dist > 1.0f)
			enemy->setPosistion(ep + (to / dist) * (kChaseSpeed * dt));

		if (m_damageCooldown <= 0.0f && player->CheckCollision(*enemy))
		{
			m_playerHP--;
			m_damageCooldown = kHurtCooldown;
		}
	}

	if (m_damageCooldown > 0.0f) m_damageCooldown -= dt;
	if (m_playerHP <= 0) m_gameOver = true;
}

void FinalGame::UpdateHUD()
{
	auto& r = Engine::Get().GetRenderer();

	if (m_playerHP != m_uiLastHP)
	{
		m_hpText.Destroy();
		m_hpText.Create(r, "HP: " + std::to_string(m_playerHP), Color(1.0f, 0.35f, 0.35f));
		m_uiLastHP = m_playerHP;
	}

	int keyState = (m_hasKey ? 1 : 0) + (m_hasGoldKey ? 2 : 0);
	if (keyState != m_uiLastKeyState)
	{
		std::string s = std::string("Key: ") + (m_hasKey ? "YES" : "-") +
		                "    Gold Key: " + (m_hasGoldKey ? "YES" : "-");
		m_keyText.Destroy();
		m_keyText.Create(r, s, Color(1.0f, 0.9f, 0.4f));
		m_uiLastKeyState = keyState;
	}
}

void FinalGame::Update(float dt)
{
	if (!m_scene) return;
	m_scene->Update(dt);
	Engine::Get().GetParticleSystem().Update(dt);

	auto& input = Engine::Get().GetInput();

	if (m_won) return;

	if (m_gameOver)
	{
		if (input.GetKeyPressed(SDL_SCANCODE_R))
		{
			m_playerHP = m_maxHP;
			m_gameOver = false;
			m_uiLastHP = -1;
			LoadLevel("Data/dang1_scene.json", "Data/dang1.tmj");
		}
		return;
	}

	Actor* player = m_scene->GetActorByName<Actor>("Hero");
	if (!player) return;

	bool ePressed = input.GetKeyPressed(SDL_SCANCODE_E);
	bool attackPressed = input.GetKeyPressed(SDL_SCANCODE_SPACE);

	if (attackPressed) DoAttack(player);

	UpdateEnemies(player, dt);
	if (m_gameOver)
	{
		if (auto* pc = dynamic_cast<PlayerController*>(player)) pc->Die();   // play death anim
		UpdateHUD();
		return;
	}

	Actor* key = m_scene->GetActorByName<Actor>("key");
	if (key && !key->IsDestroyed() && player->CheckCollision(*key))
	{
		m_hasKey = true;
		key->Destroy();
	}

	Actor* door = m_scene->GetActorByName<Actor>("door");

	Actor* trapdoor = m_scene->GetActorByName<Actor>("trapdoor");
	if (trapdoor && ePressed && player->CheckCollision(*trapdoor))
	{
		LoadLevel("Data/dang2_scene.json", "Data/dang2.tmj");
		return;
	}
	Actor* ladder = m_scene->GetActorByName<Actor>("ladder");
	if (ladder && ePressed && player->CheckCollision(*ladder))
	{
		LoadLevel("Data/dang1_scene.json", "Data/dang1.tmj");
		return;
	}

	if (!m_skeletonsSpawned)
	{
		Actor* flag = m_scene->GetActorByName<Actor>("spawn_flag");
		if (flag && player->CheckCollision(*flag))
		{
			SpawnSkeletons();
			m_skeletonsSpawned = true;
		}
	}
	if (m_skeletonsSpawned && !m_bossSpawned)
	{
		if (m_scene->GetActorsByTag<Actor>("enemy").empty())
		{
			SpawnBoss();
			m_bossSpawned = true;
		}
	}
	if (m_bossSpawned && !m_goldKeyDropped)
	{
		Actor* boss = m_scene->GetActorByName<Actor>("boss");
		if (!boss || boss->IsDestroyed())
		{
			SpawnGoldKey(m_bossPos);
			m_goldKeyDropped = true;
			m_scene->GetActorByName<Actor>("door")->Destroy();
		}
	}
	Actor* gold = m_scene->GetActorByName<Actor>("goldkey");
	if (gold && !gold->IsDestroyed() && player->CheckCollision(*gold))
	{
		m_hasGoldKey = true;
		gold->Destroy();
	}

	if (m_hasGoldKey && door && !door->IsDestroyed() && player->CheckCollision(*door))
		door->Destroy();


	if (m_hasKey && door && !door->IsDestroyed() && player->CheckCollision(*door))
		door->Destroy();

	
	Actor* winBox = m_scene->GetActorByName<Actor>("game_win");
	if (winBox && ePressed && m_hasGoldKey && player->CheckCollision(*winBox))
	{
		m_won = true;
		UpdateHUD();
		return;
	}

	UpdateHUD();
}

void FinalGame::Draw()
{
	auto& e = Engine::Get();
	e.GetRenderer().Clear();
	e.GetRenderer().enableCamera(true);

	if (m_scene) m_scene->Draw(e.GetRenderer());
	e.GetParticleSystem().Draw(e.GetRenderer());   // world-space, camera still enabled

	// HUD (screen space, not affected by the camera)
	m_hpText.Draw(e.GetRenderer(), 30.0f, 30.0f);
	m_keyText.Draw(e.GetRenderer(), 30.0f, 100.0f);

	float cx = 2560.0f * 0.5f;
	float cy = 1600.0f * 0.5f;
	if (m_won)
		m_winText.Draw(e.GetRenderer(), cx - m_winText.GetWidth() * 0.5f, cy - m_winText.GetHeight() * 0.5f);
	if (m_gameOver)
		m_gameOverText.Draw(e.GetRenderer(), cx - m_gameOverText.GetWidth() * 0.5f, cy - m_gameOverText.GetHeight() * 0.5f);

	e.GetRenderer().Present();
}
