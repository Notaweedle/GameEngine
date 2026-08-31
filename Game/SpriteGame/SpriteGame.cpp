#include "SpriteGame.h"
#include "Engine.h"
#include <memory>

using namespace nu;

bool SpriteGame::Initialize()
{
	SetWorkingDirectory("SpriteGame");   // -> Assets/SpriteGame
	Game::Initialize();
	m_scene = std::make_unique<Scene>();

	// TODO: load the new game's scene / set up state here

	return true;
}

void SpriteGame::Update(float dt)
{
	// TODO: new game update logic
	if (m_scene) m_scene->Update(dt);
}

void SpriteGame::Draw()
{
	auto& e = Engine::Get();
	e.GetRenderer().Clear();

	if (m_scene) m_scene->Draw(e.GetRenderer());

	e.GetRenderer().Present();
}
