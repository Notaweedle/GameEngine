#include "pch.h"
#include "Scene.h"
#include "Actor.h"


namespace nu
{

	void Scene::AddActor(Actor* actor) 
	{ 
		actor->m_scene = this;
		m_actor.push_back(actor);
	}

	void Scene::Update(float dt) {
		for (auto actor : m_actor) {
			actor->Update(dt);
		}
	}
	void Scene::Draw(const class Renderer& renderer) {

		for (auto actor : m_actor) {
			actor->Draw(renderer);
		}
	}

};
