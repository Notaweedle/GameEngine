#include "Door.h"

// NOTE: the door is spawned as a plain "Actor" prototype named "Door" (see the
// scene json). We deliberately do NOT FACTORY_REGISTER(Door) here, because that
// would claim the name "door" and stop the scene's "Door" prototype from
// registering (Factory::RegisterPrototype refuses to overwrite an existing name).

void Door::Open()
{
	Destroy();
}
