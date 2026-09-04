#pragma once
#include "Framework/Actor.h"


class Door : public nu::Actor
{
public:
	CLASS_PROTOTYPE(Door)

	void Open();                                   // remove the door + its collision
	bool IsOpen() const { return IsDestroyed(); }
};
