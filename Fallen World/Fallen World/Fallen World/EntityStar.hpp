#ifndef _ENTITYSTAR_HPP_
#define _ENTITYSTAR_HPP_

#include "Entity.hpp"

class EntityStar : public Entity
{
public:

	EntityStar();
	void Initialize(GameScreen* screen);
	EntityType getEntityType() const;
}; 

#endif