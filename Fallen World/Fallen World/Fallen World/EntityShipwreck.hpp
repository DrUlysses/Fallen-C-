#ifndef _ENTITYSHIPWRECK_HPP_
#define _ENTITYSHIPWRECK_HPP_

#include "Entity.hpp"

class EntityShipwreck : public Entity
{
	float lifeVelocity;
	float lifeTime;

public:

	EntityShipwreck(Entity* ship, const int& shipwreckId, const int& shipwreckDepth);

	void Update(float time);
};

#endif