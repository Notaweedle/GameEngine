#pragma once 
#include "Actor.h"
#include "Model.h"

class Player : public nu::Actor {
public:
	Player() = default;
	Player(float speed,const nu::Tranform& tranform) :
		Actor{ tranform } 
	{
	}

	Player(float speed,const nu::Tranform& tranform, const nu::Model& model) :
		Actor{tranform},
		m_speed{speed}
	{
	}

	void Update(float dt);
	void Draw(const class nu::Renderer& renderer) const;



private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};


