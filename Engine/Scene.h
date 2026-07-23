#pragma once
#include <vector>
#include <string>
#include "Actor.h"
namespace nu
{
	class Actor;
	class Scene {
	public:
		void AddActor(Actor* actor);


		void Update(float dt);
		void Draw(const class Renderer& renderer);

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

	private:
		std::vector<Actor*> m_actor;
	};


	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto actor : m_actor)
		{
			T* actorT = dynamic_cast<T*>(actor);
			if (actorT && actorT->m_name == name) {
				return actorT;
			}
		}
		return nullptr;
	}

}