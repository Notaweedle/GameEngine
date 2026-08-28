#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Actor.h"
#include "Serialization/json.h"

namespace nu
{
	class Actor;
	class Scene {
	public:
		void AddActor(std::unique_ptr<Actor> actor);
		void RemoveActors();

		bool Load(const std::string& sceneName);

		void UpdateCollisions();
		void Update(float dt);
		void Draw(const class Renderer& renderer);

		void SetDebugDraw(bool enabled) { m_debugDraw = enabled; }
		bool GetDebugDraw() const { return m_debugDraw; }

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsByTag(const std::string& tag);

	private:
		std::vector<std::unique_ptr<Actor>> m_actor;
		std::vector<std::unique_ptr<Actor>> m_pendingActor;
		bool m_debugDraw = false;

	};


	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto const& actor : m_actor)
		{
			T* actorT = dynamic_cast<T*>(actor.get());
			if (actorT && actorT->m_name == name) {
				return actorT;
			}
		}
		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag)
	{
		std::vector<T*> actors;
		for (auto const& actor : m_actor)
		{
			if (actor->IsDestroyed()) continue;

			T* actorT = dynamic_cast<T*>(actor.get());
			if (actorT && actorT->m_tag == tag) {
				actors.push_back(actorT);
			}
		}
		return actors;
	}

	

}
