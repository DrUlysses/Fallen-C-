#ifndef _ENTITYPLAYER_HPP_
#define _ENTITYPLAYER_HPP_

#include "Entity.hpp"
#include "EntityEnemy.hpp"
#include <list>

class GameScreen;

class EntityPlayer : public Entity 
{
	Weapon weapon;
	sf::String name;
	int points;
	int gunLevel;
	float velocity;
	float counter;
	float shootVelocity;
	float shootCounter;
	std::list<EntityEnemy*> collisionList;

public:

	EntityPlayer(const sf::String& name, const int& points = 0, const int& gunLevel = 0, const int& health = 100);
	const sf::String& getName() const;
	const int& getPoints() const;
	void setPoints(const int& points);
	void Initialize(GameScreen* screen);
	void Update(float time);
	EntityType getEntityType() const;
	const int& getGunLevel() const;
	void setGunLevel(const int& gunLevel);
	void OnDeath();
	void AddToCollisionList(EntityEnemy* enemy);
	void RemoveFromCollisionList(EntityEnemy* enemy);
	bool IsInCollisionList(EntityEnemy* EntityEnemy);
};

#endif
