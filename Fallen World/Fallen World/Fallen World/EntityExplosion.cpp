#include "EntityExplosion.hpp"
#include "GameScreen.hpp"

EntityExplosion::EntityExplosion()
{
	checkXCollision = false;
	checkYCollision = false;

	SetAnimationSpeed(35);
	SetAnimation(0, 24);
	SetFrameSize(130, 130);
	setScale(0.5f, 0.5f);
}

void EntityExplosion::Initialize(GameScreen* screen)
{
	setTexture(screen->getApp().getTexture("media\\explosion.png"));
	Entity::Initialize(screen);
}

void EntityExplosion::OnAnimationStopped()
{
	isOver = true;
}