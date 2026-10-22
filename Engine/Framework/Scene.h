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

		// collision outcomes for the game layer to consume each frame
		// (Scene resolves the physical collision; the game decides score/lives)
		int  TakeEnemyKills() { int n = m_enemyKills; m_enemyKills = 0; return n; }
		bool TakePlayerHit()  { bool h = m_playerHit; m_playerHit = false; return h; }

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

		int  m_enemyKills = 0;   // enemies killed by bullets since last consumed
		bool m_playerHit  = false;   // player hit an enemy since last consumed

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
