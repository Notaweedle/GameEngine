#pragma once 
#include "Actor.h"
#include "Model.h"
#include <Json.h>


struct PlayerDesc : public nu::ActorDesc
{
	float speed;
};


class Player : public nu::Actor {
public:


	Player() = default;

	
	Player(const PlayerDesc& desc) :
		Actor{ desc }, m_speed{ desc.speed }
	{
	}

	Player(float speed,const nu::Transform& transform) :
		Actor{ transform }, m_speed{ speed }
	{
	}

	Player(float speed,const nu::Transform& transform, const nu::Model& model) :
		Actor{ transform, model }, m_speed{ speed }
	{
	}

	CLASS_PROTOTYPE(Player)

	void Read(const nu::json::value_t& value) override;

	void Update(float dt) override;
	void Draw(const class nu::Renderer& renderer) const override;
	void Shoot();
	


private:
	int m_ammo = 0;
	float m_speed = 800.0f;
	float m_bulletSpeed = 600.0f;   // default; overridden by "bulletSpeed" in data.json
};


