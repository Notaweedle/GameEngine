#include "pch.h"
#include "Secne.h"
#include "Actor.h"


namespace nu
{
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
