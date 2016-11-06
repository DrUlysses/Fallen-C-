#include "Entity.hpp"
#include "GameScreen.hpp"

Entity::Entity()
{
	frameStart = 0;
	frameEnd = 0;
	frameCurrent = 0;
	frameTimer = 0;
	animationSpeed = 1;
	animationLoop = true;
	animationPlay = true;
	frameOffsetX = 0;
	frameOffsetY = 0;
	frameWidth = 0;
	frameHeight = 0;
	checkXCollision = false;
	checkYCollision = false;
	speed = sf::Vector2f(0, 0);
	rotationRate = 0;
	health = 100;
	isAlive = true;
	isOver = false;
	isWait = false;
}

void Entity::Initialize(GameScreen* screen)
{
	this->screen = screen;
	setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}

void Entity::SetAnimation(const int& frameStart, const int& frameEnd)
{
	if(this->frameStart != frameStart || this->frameEnd != frameEnd)
	{
		this->frameStart = frameStart;
		this->frameEnd = frameEnd;
		frameCurrent = frameStart;
		frameTimer = 0;
		animationPlay = true;
	}
}

void Entity::SetAnimationSpeed(const float& animationSpeed)
{
	this->animationSpeed = animationSpeed;
}

void Entity::SetAnimationLoop(const bool& animationLoop)
{
	this->animationLoop = animationLoop;
}

void Entity::SetFrameOffset(const int& frameOffsetX, const int& frameOffsetY)
{
	this->frameOffsetX = frameOffsetX;
	this->frameOffsetY = frameOffsetY;
}

void Entity::SetFrameSize(const int& frameWidth, const int& frameHeight)
{
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
}

void Entity::ChangeHealth(const int& deltaHealth)
{
	health += deltaHealth;
}

void Entity::Update(float time)
{
	Application& App = screen->getApp();

	if(health <= 0 && isAlive)
	{
		OnDeath();
		isAlive = false;
	}

	if(isWait)
	{
		isOver = true;
	}

	// Анимация объекта
	if(getTexture())
	{
		if(animationPlay)
		{
			frameCurrent = frameStart + int(frameTimer * animationSpeed);

			if(frameCurrent > frameEnd)
			{
				frameCurrent = frameStart;
				frameTimer = 0;

				if(animationLoop)
				{
					animationPlay = true;
				}
				else
				{
					animationPlay = false;
				}

				OnAnimationStopped();
			}

			frameTimer += time;
		}

		int frameCountX = getTexture()->getSize().x / frameWidth;
		int frameX = frameOffsetX + (frameCurrent % frameCountX) * frameWidth;
		int frameY = frameOffsetY + (frameCurrent / frameCountX) * frameHeight;

		setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));
	}

	// Проверка на выход за границы экрана
	float posX = getPosition().x;
	float posY = getPosition().y;
	float sizeX = getGlobalBounds().width;
	float sizeY = getGlobalBounds().height;

	if(isAlive)
	{
		float dtX = posX + sizeX / 2 - App.getWidth();
		float dtY = posY + sizeY / 2 - App.getHeight();

		if(dtX > 0 && checkXCollision)
		{
			posX -= dtX;
		}

		if(dtY > 0 && checkYCollision)
		{
			posY -= dtY;
		}

		dtX = posX - sizeX / 2;
		dtY = posY - sizeY / 2;

		if(dtX < 0 && checkXCollision) 
		{
			posX -= dtX;
		}

		if(dtY < 0 && checkYCollision)
		{
			posY -= dtY;
		}

		setPosition(posX, posY);
	}
	else
	{
		isWait = true;
	}
	
	if(getEntityType() != Player)
	{
		if(posX + sizeX / 2 < 0 || posX - sizeX / 2 > App.getWidth())
		{
			isOver = true;
		}

		if(posY + sizeY / 2 < 0 || posY - sizeY / 2 > App.getHeight())
		{
			isOver = true;
		}
	}

	// Физика движения
	move(speed * time);

	rotate(rotationRate * time);
}

void Entity::Draw()
{
	screen->getApp().draw(*this);
}

bool Entity::IsDead() const
{
	return !isAlive;
}

const bool& Entity::IsOver() const
{
	return isOver;
}

bool Entity::DoesCollide(const Entity* entity) const
{
	return entity->getGlobalBounds().intersects(getGlobalBounds());
}

void Entity::SetAsDead()
{
	isAlive = false;
}

void Entity::SetAsOver()
{
	isOver = true;
}

const int& Entity::getHealth() const
{
	return health;
}

GameScreen* Entity::getScreen() const
{
	return screen;
}

Weapon::Weapon(const WeaponType& weaponType, Entity* entityOwner, const bool& downward)
{
	this->weaponType = weaponType;
	this->entityOwner = entityOwner;
	this->downward = downward;
}

Weapon::Weapon()
{
	weaponType = WEAPON_0;
	entityOwner = 0;
	downward = false;
}

void Weapon::Shoot()
{
	float posX = entityOwner->getPosition().x;
	float posY = entityOwner->getPosition().y;
	float sizeX = entityOwner->getGlobalBounds().width;
	float sizeY = entityOwner->getGlobalBounds().height;
	float offsetY = downward ? sizeY : -sizeY;
	float offsetX = sizeX * 0.35f;

	if(entityOwner->getEntityType() == Player)
	{
		offsetY *= 0.55f;
	}
	else
	{
		offsetY *= 0.75f;
	}

	if(weaponType == WEAPON_0)
	{
		entityOwner->getScreen()->SpawnBullet(posX, posY + offsetY, entityOwner->getEntityType(), BULLET_0, downward);
	}
	else if(weaponType == WEAPON_1)
	{
		entityOwner->getScreen()->SpawnBullet(posX - offsetX, posY + offsetY / 4, entityOwner->getEntityType(), BULLET_0, downward);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX, posY + offsetY / 4, entityOwner->getEntityType(), BULLET_0, downward);
	}
	else if(weaponType == WEAPON_2)
	{
		entityOwner->getScreen()->SpawnBullet(posX - offsetX * 1.095f, posY + offsetY / 4, entityOwner->getEntityType(), BULLET_0, downward, -5);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 0.000f, posY + offsetY / 1, entityOwner->getEntityType(), BULLET_1, downward);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 1.095f, posY + offsetY / 4, entityOwner->getEntityType(), BULLET_0, downward, 5);
	}
	else if(weaponType == WEAPON_3)
	{
		entityOwner->getScreen()->SpawnBullet(posX - offsetX * 1.000f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, -5);
		entityOwner->getScreen()->SpawnBullet(posX - offsetX * 0.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, -1);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 0.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, 1);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 1.000f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, 5);
	}
	else if(weaponType == WEAPON_4)
	{
		entityOwner->getScreen()->SpawnBullet(posX - offsetX * 1.000f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, -20);
		entityOwner->getScreen()->SpawnBullet(posX - offsetX * 0.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, -10);
		entityOwner->getScreen()->SpawnBullet(posX, posY + offsetY, entityOwner->getEntityType(), BULLET_2, downward);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 0.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, 10);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 1.000f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, 20);
	}
	else if(weaponType == WEAPON_5)
	{
		entityOwner->getScreen()->SpawnBullet(posX - offsetX * 1.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, -20);
		entityOwner->getScreen()->SpawnBullet(posX - offsetX * 1.000f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, -10);
		entityOwner->getScreen()->SpawnBullet(posX - offsetX * 0.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_2, downward, -5);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 0.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_2, downward, 5);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 1.000f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, 10);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 1.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, 20);
	}
	else if(weaponType == WEAPON_6)
	{
		entityOwner->getScreen()->SpawnBullet(posX - offsetX * 1.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, -20);
		entityOwner->getScreen()->SpawnBullet(posX - offsetX * 1.000f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, -10);
		entityOwner->getScreen()->SpawnBullet(posX - offsetX * 0.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_2, downward, -5);
		entityOwner->getScreen()->SpawnBullet(posX, posY + offsetY, entityOwner->getEntityType(), BULLET_3, downward);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 0.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_2, downward, 5);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 1.000f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, 10);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 1.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, 20);
	}
	else if(weaponType == WEAPON_7)
	{
		entityOwner->getScreen()->SpawnBullet(posX - offsetX * 1.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, -20);
		entityOwner->getScreen()->SpawnBullet(posX - offsetX * 1.000f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, -10);
		entityOwner->getScreen()->SpawnBullet(posX - offsetX * 0.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_2, downward, -5);
		entityOwner->getScreen()->SpawnBullet(posX, posY + offsetY, entityOwner->getEntityType(), BULLET_3, downward);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 0.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_2, downward, 5);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 1.000f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, 10);
		entityOwner->getScreen()->SpawnBullet(posX + offsetX * 1.500f, posY + offsetY, entityOwner->getEntityType(), BULLET_1, downward, 20);

		if(int(rand() % 2) == 1)
		{
			for(float angle = 0; angle < 360.5f; angle += 15)
			{
				entityOwner->getScreen()->SpawnBullet(posX, posY, entityOwner->getEntityType(), BULLET_2, downward, angle);
			}
		}
	}
	else if(weaponType == WEAPON_8)
	{
		int tick = int(rand() % 2);

		if(tick == 0)
		{
			for(float angle = 0; angle < 360.5f; angle += 20)
			{
				entityOwner->getScreen()->SpawnBullet(posX, posY, entityOwner->getEntityType(), BULLET_2, downward, angle);
			}
		}
		else if(tick == 1)
		{
			entityOwner->getScreen()->SpawnBullet(posX, posY + offsetY, entityOwner->getEntityType(), BULLET_7, downward);
		}
	}
	else if(weaponType == WEAPON_E)
	{
		entityOwner->getScreen()->SpawnBullet(posX, posY + offsetY, entityOwner->getEntityType(), BULLET_E, downward);
	}
	else
	{
		int tick = int(rand() % 2);

		if(tick == 0)
		{
			for(float angle = 0; angle < 360.5f; angle += 15)
			{
				entityOwner->getScreen()->SpawnBullet(posX, posY, entityOwner->getEntityType(), BULLET_2, downward, angle);
			}
		}
		else if(tick == 1)
		{
			entityOwner->getScreen()->SpawnBullet(posX, posY + offsetY, entityOwner->getEntityType(), BULLET_7, downward);
		}
	}
}

void Weapon::Shoot(const bool& downward, const float& angle)
{
	float posX = entityOwner->getPosition().x;
	float posY = entityOwner->getPosition().y;
	float sizeX = entityOwner->getGlobalBounds().width;
	float sizeY = entityOwner->getGlobalBounds().height;
	float offsetY = downward ? sizeY : -sizeY;
	float offsetX = sizeX * 0.35f;

	if(entityOwner->getEntityType() == Player)
	{
		offsetY *= 0.55f;
	}
	else
	{
		offsetY *= 0.75f;
	}

	if (weaponType == WEAPON_E)
	{
		entityOwner->getScreen()->SpawnBullet(posX, posY + offsetY, entityOwner->getEntityType(), BULLET_E, downward, angle);
	}
}