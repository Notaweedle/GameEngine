#pragma once
#include <Framework/Game.h>

class SpriteGame : public nu::Game
{
public:
	bool Initialize() override;
	void Update(float dt) override;
	void Draw() override;
};
