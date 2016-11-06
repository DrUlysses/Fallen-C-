#include "EntityParticle.hpp"
#include "GameScreen.hpp"

EntityParticle::EntityParticle(const sf::Vector2f& pos)
{
	speed.x = -200.0f + rand() % 400;
	speed.y = -200.0f + rand() % 400;

	float length = sqrt(speed.x * speed.x + speed.y * speed.y);
	speed.x /= length;
	speed.y /= length;

	float velocity = 200.0f + rand() % 100;
	speed.x *= velocity;
	speed.y *= velocity;
	
	lifeTime = 100;
	fadeVelocity = 150.0f + rand() % 150;
	rotationRate = 500.0f + rand() % 200;
	checkXCollision = false;
	checkYCollision = false;
	setPosition(pos + sf::Vector2f(float(rand() % 5), float(rand() % 5)));
	setScale(1.0f + rand() % 3, 1.0f + rand() % 3);
	setColor(sf::Color(255 - rand() % 25, 255 - rand() % 150, 0));
}

void EntityParticle::Update(float time)
{
	lifeTime -= fadeVelocity * time;

	if(lifeTime < 0)
	{
		SetAsOver();
	}

	sf::Color color = getColor();
	color.a = int(lifeTime / 100 * 205) + 50;
	setColor(color);

	Entity::Update(time);
}

void EntityParticle::Draw()
{
	if(!getTexture())
	{
		sf::RectangleShape rect;
		rect.setFillColor(getColor());
		rect.setPosition(getPosition());
		rect.setSize(getScale());
		rect.setRotation(getRotation());
		screen->getApp().draw(rect);
	}
	else
	{
		screen->getApp().draw(*this);
	}
}