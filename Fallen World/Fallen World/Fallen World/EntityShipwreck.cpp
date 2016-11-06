#include "EntityShipwreck.hpp"

EntityShipwreck::EntityShipwreck(Entity* ship, const int& shipwreckId, const int& shipwreckDepth)
{
	checkXCollision = false;
	checkYCollision = false;
	rotationRate = 100.0f + rand() % 50;
	lifeVelocity = 200.0f + rand() % 200;
	lifeTime = 0;

	speed.x = -50.0f + rand() % 100;
	speed.y = -50.0f + rand() % 100;

	float length = sqrt(speed.x * speed.x + speed.y * speed.y);
	speed.x /= length;
	speed.y /= length;

	float velocity = 200.0f + rand() % 100;
	speed.x *= velocity;
	speed.y *= velocity;

	setPosition(ship->getPosition());
	setScale(ship->getScale());
	setTexture(*ship->getTexture());

	int texSizeX = ship->getTexture()->getSize().x / shipwreckDepth;
	int texSizeY = ship->getTexture()->getSize().y / shipwreckDepth;
	int texPosX = shipwreckId % shipwreckDepth * texSizeX;
	int texPosY = shipwreckId / shipwreckDepth * texSizeY;

	SetAnimation(0, 0);
	SetFrameSize(texSizeX, texSizeY);
	SetFrameOffset(texPosX, texPosY);
}

void EntityShipwreck::Update(float time)
{
	lifeTime += lifeVelocity * time;

	if(lifeTime > 100)
	{
		SetAsOver();
	}

	setColor(sf::Color(255, 255, 255, int((1 - lifeTime / 100) * 245) + 10));

	Entity::Update(time);
}