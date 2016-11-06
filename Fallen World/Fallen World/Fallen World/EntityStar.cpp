#include "EntityStar.hpp"
#include "GameScreen.hpp"

EntityStar::EntityStar()
{
	speed.x = 0;
	speed.y = 100;
	checkXCollision = false;
	checkYCollision = false;

	SetAnimation(0, 1);
	SetAnimationSpeed(1);
	SetFrameSize(3, 3);
}

void EntityStar::Initialize(GameScreen* screen)
{
	setTexture(screen->getApp().getTexture("media\\star.png"));
	setPosition(float(rand() % int(screen->getApp().getWidth()) + 1), 0);
	Entity::Initialize(screen);
}

EntityType EntityStar::getEntityType() const
{
	return Star;
}