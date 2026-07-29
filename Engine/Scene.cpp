#include "pch.h"
#include "Scene.h"
#include "Actor.h"


namespace nu
{

	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actor.push_back(std::move(actor));
	}

	void Scene::Update(float dt) {
		// index over the count captured up front: actors spawned during Update
		// (bullets, for example) join the scene but wait until the next frame
		size_t count = m_actor.size();
		for (size_t i = 0; i < count; i++) {
			if (!m_actor[i]->IsDestroyed()) m_actor[i]->Update(dt);
		}

		std::erase_if(m_actor, [](const std::unique_ptr<Actor>& actor) { return actor->IsDestroyed(); });
	}
	void Scene::Draw(const class Renderer& renderer) {

		for (auto& actor : m_actor) {
			actor->Draw(renderer);
			if (m_debugDraw) actor->DrawHitbox(renderer);
		}
	}

};
