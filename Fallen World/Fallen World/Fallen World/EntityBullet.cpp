#include "EntityBullet.hpp"
#include "GameScreen.hpp"

EntityBullet::EntityBullet(const EntityType& senderType, const BulletType& bulletType, const bool& downward, const float& angle)
{
	this->senderType = senderType;
	this->bulletType = bulletType;
	this->downward = downward;
	this->angle = angle;
	this->type = type;
	velocity = 412;
	target = 0;
	firstTarget = true;
	previousDirection = sf::Vector2f(0, -1);
	checkXCollision = false;
	checkYCollision = false;
	if(bulletType == BULLET_0)
	{
		SetAnimation(0, 0);
		SetAnimationSpeed(1);
		SetFrameOffset(4, 0);
		SetFrameSize(3, 7);
	}
	else if(bulletType == BULLET_1)
	{
		SetAnimation(0, 0);
		SetAnimationSpeed(1);
		SetFrameOffset(8, 0);
		SetFrameSize(3, 7);
	}
	else if(bulletType == BULLET_2)
	{
		SetAnimation(0, 0);
		SetAnimationSpeed(1);
		SetFrameOffset(16, 0);
		SetFrameSize(4, 10);
	}
	else if(bulletType == BULLET_3)
	{
		SetAnimation(0, 0);
		SetAnimationSpeed(1);
		SetFrameOffset(22, 0);
		SetFrameSize(3, 7);
	}
	else if(bulletType == BULLET_4)
	{
		SetAnimation(0, 0);
		SetAnimationSpeed(1);
		SetFrameOffset(30, 0);
		SetFrameSize(11, 10);
	}
	else if (bulletType == BULLET_E)
	{
		SetAnimation(0, 0);
		SetAnimationSpeed(1);
		SetFrameOffset(6, 17);
		SetFrameSize(8, 8);
	}
	else
	{
		SetAnimation(0, 1);
		SetAnimationSpeed(10);
		SetFrameOffset(66, 0);
		SetFrameSize(4, 14);
	}
}

void EntityBullet::Initialize(GameScreen* screen)
{
	setTexture(screen->getApp().getTexture("media\\ammo.png"));	
	Entity::Initialize(screen);
}

void EntityBullet::Update(float time) 
{
	if(bulletType != BULLET_7)
	{
		float fullAngle = 0;
		
		speed.y = -velocity;
		speed.x = 0;
		
		if(downward)
		{
			fullAngle = 180;
		}
		
		fullAngle += angle;
		
		float angleRadians = fullAngle * acos(0.f) / 90;
		float speedX = speed.x;
		float speedY = speed.y;
		
		speed.x = speedX * cos(angleRadians) - speedY * sin(angleRadians); 
		speed.y = speedX * sin(angleRadians) + speedY * cos(angleRadians);
		
		setRotation(fullAngle);
	}
	else
	{
		if(!target && firstTarget)
		{
			target = screen->getNearestEnemy(getPosition().x, getPosition().y);
			firstTarget = false;
		}

		sf::Vector2f direction;

		if(target)
		{
			if(!target->IsDead())
			{
				direction = target->getPosition() - getPosition();
				float length = sqrt(direction.x * direction.x + direction.y * direction.y);
				direction /= length;
				previousDirection = direction;
			}
			else
			{
				target = 0;
			}
		}

		if(!target)
		{
			direction = previousDirection;
		}

		speed = direction * velocity;

		angle = 0;

		if(direction.x > 0)
		{
			angle = acos(-direction.y) / acos(0.f) / 2 * 180;
		}

		if(direction.x < 0)
		{
			angle = acos(direction.y) / acos(0.f) / 2 * 180 + 180;
		}

		setRotation(angle);
	}

	Entity::Update(time);
}

EntityType EntityBullet::getEntityType() const
{
	return Bullet;
}

const EntityType& EntityBullet::getSenderType() const
{
	return senderType;
}

const BulletType& EntityBullet::getBulletType() const
{
	return bulletType;
}

