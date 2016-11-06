#ifndef _ENTITYENEMY_HPP_
#define _ENTITYENEMY_HPP_

#include "Entity.hpp"

class EntityEnemy : public Entity
{
	Weapon weapon;
	int type;
	bool shoot;
	float velocity;
	float shootVelocity;
	float shootTimer;
	float stopVelocity;
	float stopTimer;
	float distance;
	float speedX;
	float speedY;
	
public:

	EntityEnemy(int type);
	void Initialize(GameScreen* screen);
	void Update(float time);
	void Draw();
	void OnDeath();
	EntityType getEntityType() const;
};

#endif