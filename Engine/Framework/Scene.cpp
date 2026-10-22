#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"
#include "Engine.h"
#include "Renderer/ParticleManager.h"


namespace nu
{
	
	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		actor->Start();                     // start components (creates physics bodies, etc.)
		m_actor.push_back(std::move(actor));
	}

	void Scene::RemoveActors() {
		m_actor.clear();
	}

	bool Scene::Load(const std::string& sceneName)
	{

		json::document_t doc;
		if (!json::Load(sceneName, doc)) {
			std::cerr << "Could not load scene: " << sceneName << std::endl;
			return false;
		}

		if (JSON_HAS_NAME(doc,"actors")){

			for (auto& actorValue : JSON_GET_NAME(doc, "actors").GetArray()) {

				//get actor type
				std::string typeName;
				JSON_READ_NAME(actorValue, "type", typeName);

				//create actor of type
				auto actor = Factory::Instance().Create<Actor>(typeName);
				if (!actor) continue;   // type not registered -> skip instead of crashing

				//read actor json
				actor->Read(actorValue);

				//check if prototype
				bool prototype = false;
				JSON_READ(actorValue, prototype);

				if (prototype)
				{	// if prototype, register under its OWN name so it can be created later
					std::string name;
					JSON_READ(actorValue, name);
					Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
				}
				else {
					// not a prototype, add actor to scene
					AddActor(std::move(actor)); 
				}

			}

		}
		return true;


	}

	void Scene::Update(float dt) {
		size_t count = m_actor.size();
		for (size_t i = 0; i < count; i++) {
			if (!m_actor[i]->IsDestroyed()) m_actor[i]->Update(dt);
		}

		UpdateCollisions();

		std::erase_if(m_actor, [](const std::unique_ptr<Actor>& actor) { return actor->IsDestroyed(); });

		for (auto& actor : m_pendingActor) {
			actor->Start();
			m_actor.push_back(std::move(actor));
		}
		m_pendingActor.clear();
	}
	void Scene::Draw(const class Renderer& renderer) {

		for (auto const& actor : m_actor) {
			actor->Draw(renderer);
			if (m_debugDraw) actor->DrawHitbox(renderer);
		}
	}

	void Scene::UpdateCollisions()
	{
		std::vector<Actor*> enemies = GetActorsByTag("enemy");

		for (Actor* bullet : GetActorsByTag("bullet")) {
			for (Actor* enemy : enemies) {
				if (enemy->IsDestroyed()) continue;

				if (bullet->CheckCollision(*enemy)) {
					ParticleDesc pd = enmy_expl();
					pd.position = enemy->getTransform().position;
					Engine::Get().GetParticleSystem().Emit(pd);

					bullet->Destroy();
					enemy->OnKilled();   // virtual on Actor; game entities (Enemy) override it
					m_enemyKills++;
					break;
				}
			}
		}

		Actor* player = GetActorByName<Actor>("Player");
		if (player == nullptr) return;

		for (Actor* enemy : enemies) {
			if (!enemy->IsDestroyed() && player->CheckCollision(*enemy)) {
				ParticleDesc pd = player_expl();
				pd.position = player->getTransform().position;
				Engine::Get().GetParticleSystem().Emit(pd);

				enemy->Destroy();
				player->Destroy();
				m_playerHit = true;
				return;
			}
		}
	}

};
