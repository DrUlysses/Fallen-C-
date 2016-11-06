#include "EntityPlayer.hpp"
#include "GameScreen.hpp"
#include "GameFileScores.hpp"

EntityPlayer::EntityPlayer(const sf::String& name, const int& points, const int& gunLevel, const int& health)
{
	weapon = Weapon(WEAPON_0, this, false);

	this->name = name;
	this->points = points;
	this->health = health;

	velocity = 398;
	counter = 0;
	shootVelocity = 4;
	shootCounter = 0;

	checkXCollision = true;
	checkYCollision = true;

	setGunLevel(gunLevel);
	SetAnimation(0, 1);
	SetAnimationSpeed(6);
	SetFrameSize(39, 43);
}

const sf::String& EntityPlayer::getName() const
{
	return name;
}

const int& EntityPlayer::getPoints() const
{
	return points;
}

void EntityPlayer::setPoints(const int& points)
{
	this->points = points;
}

void EntityPlayer::Initialize(GameScreen* screen)
{
	Application& App = screen->getApp();

	setPosition(App.getWidth() / 2, App.getHeight() - getGlobalBounds().height / 2 - 150);
	setTexture(App.getTexture("media\\player.png"));
	Entity::Initialize(screen);
}

void EntityPlayer::Update(float time)
{
	if(isAlive)
	{
		speed = sf::Vector2f(0, 0);

		// Управление кораблём игрока
		bool xMovement = false;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) <= -50.) 
		{
			speed.x = -velocity;
			SetAnimation(2, 3);
			xMovement = true;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) >= 50.) 
		{
			speed.x = velocity;
			SetAnimation(4, 5);
			xMovement = true;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) <= -50.) 
		{
			speed.y = -velocity;
		
			if(!xMovement)
			{
				SetAnimation(0, 1);
			}
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) >= 50.) 
		{
			speed.y = velocity;

			if(!xMovement)
			{
				SetAnimation(0, 1);
			}
		}

		// Состояние покоя
		if(abs(speed.x) < 0.001f && abs(speed.y) < 0.001f)
		{
			SetAnimation(0, 1);
		}

		// Стрельба
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 2) || sf::Joystick::isButtonPressed(0, 4) || sf::Joystick::isButtonPressed(0, 5))
		{
			if(shootCounter > 1 / shootVelocity)
			{
				weapon.Shoot();
				shootCounter = 0;
			}

			shootCounter += time;
		}
	}
	else
	{
		
		counter += time;
	}

	Entity::Update(time);
}

void EntityPlayer::OnDeath()
{
	speed.x = 0;
	speed.y = 0;
	GameFileScores scores;
	scores.LoadFile("scores.dat");
	scores.AddPlayer(name, points);
	scores.SaveFile("scores.dat");
	SetAnimation(6, 7);
	screen->PauseGame();
}

EntityType EntityPlayer::getEntityType() const
{
	return Player;
}

const int& EntityPlayer::getGunLevel() const
{
	return gunLevel;
}

void EntityPlayer::setGunLevel(const int& gunLevel)
{
	weapon = Weapon(static_cast<WeaponType>(gunLevel), this, false);
	this->gunLevel = gunLevel;
}

void EntityPlayer::AddToCollisionList(EntityEnemy* enemy)
{
	collisionList.push_back(enemy);
}

void EntityPlayer::RemoveFromCollisionList(EntityEnemy* enemy)
{
	collisionList.remove(enemy);
}

bool EntityPlayer::IsInCollisionList(EntityEnemy* enemy)
{
	std::list<EntityEnemy*>::iterator it;

	for(it = collisionList.begin(); it != collisionList.end(); ++it)
	{
		if(*it == enemy)
		{
			return true;
		}
	}

	return false;
}