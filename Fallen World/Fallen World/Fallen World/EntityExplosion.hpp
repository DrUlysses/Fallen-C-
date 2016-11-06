#ifndef _ENTITYEXPLOSION_HPP_
#define _ENTITYEXPLOSION_HPP_

#include "Entity.hpp"

class EntityExplosion : public Entity
{
public:

	EntityExplosion();
	void Initialize(GameScreen* screen);
	void OnAnimationStopped();
};

#endif