#pragma once
#include <Framework/Game.h>
#include <Renderer/Text.h>
#include <Renderer/Font.h>
#include <Resources/Resource.h>
#include <Math/Vector2.h>
#include <string>

namespace nu { class Actor; }

class FinalGame : public nu::Game
{
public:
	bool Initialize() override;
	void Update(float dt) override;
	void Draw() override;

private:
	void LoadLevel(const std::string& sceneJson, const std::string& tmjPath);
	void SpawnFromObjects();
	void SpawnSkeletons();
	void SpawnBoss();
	void SpawnGoldKey(const nu::Vector2& pos);
	void DoAttack(nu::Actor* player);
	void UpdateEnemies(nu::Actor* player, float dt);   // chase + contact damage
	void UpdateHUD();                                  // rebuild HP/key text on change

	std::string m_tmjPath;

	// progression / win flow
	bool m_hasKey = false;
	bool m_skeletonsSpawned = false;
	bool m_bossSpawned = false;
	bool m_goldKeyDropped = false;
	bool m_hasGoldKey = false;
	bool m_won = false;
	int  m_bossHealth = 3;
	nu::Vector2 m_bossPos{ 0.0f, 0.0f };

	// player health / combat
	int   m_playerHP = 5;
	int   m_maxHP = 5;
	float m_damageCooldown = 0.0f;
	bool  m_gameOver = false;

	// HUD
	nu::res_t<nu::Font> m_font;
	nu::Text m_winText;
	nu::Text m_gameOverText;
	nu::Text m_hpText;
	nu::Text m_keyText;
	int m_uiLastHP = -1;
	int m_uiLastKeyState = -1;
};
