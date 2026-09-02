#include "pch.h"
#include "Game.h"
#include "Scene.h"

namespace nu
{
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
