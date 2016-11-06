#ifndef _ENTITYBULLET_HPP_
#define _ENTITYBULLET_HPP_

#include "Entity.hpp"
#include "EntityEnemy.hpp"

enum BulletType
{
	BULLET_0,
	BULLET_1,
	BULLET_2,
	BULLET_3, 
	BULLET_4,
	BULLET_5,
	BULLET_6,
	BULLET_7,
	BULLET_8,
	BULLET_9,
	BULLET_E
};

class EntityBullet : public Entity
{
	EntityType senderType;
	BulletType bulletType;
	bool downward;
	float angle;
	int type;
	float velocity;
	EntityEnemy* target;
	bool firstTarget;
	sf::Vector2f previousDirection;

public:

	EntityBullet(const EntityType& senderType, const BulletType& bulletType, const bool& downward, const float& angle = 0);
	void Initialize(GameScreen* screen);
	void Update(float time);
	EntityType getEntityType() const;
	const EntityType& getSenderType() const;
	const BulletType& getBulletType() const;
};

#endif