#include "pch.h"
#include "Game.h"
#include "Scene.h"

namespace nu
{
	// ctor/dtor defined here (not in the header) so the unique_ptr<Scene> only needs
	// the full Scene definition in this translation unit.
	Game::Game() = default;
	Game::~Game() = default;

	void Game::SetScene(std::unique_ptr<Scene> scene)
	{
		m_scene = std::move(scene);
	}

	Scene* Game::GetScene()
	{
		return m_scene.get();
	}
}
