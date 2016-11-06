#ifndef _ENTITYPARTICLE_HPP_
#define _ENTITYPARTICLE_HPP_

#include "Entity.hpp"

class EntityParticle : public Entity
{
	float lifeTime;
	float fadeVelocity;
	
public:

	EntityParticle(const sf::Vector2f& pos);
	void Update(float time);
	void Draw();
};

#endif