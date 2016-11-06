#include "EntityEnemy.hpp"
#include "GameScreen.hpp"

EntityEnemy::EntityEnemy(int type)
{
	weapon = Weapon(WEAPON_E, this, true);

	this->type = type;
	shoot = true;

	if(type == 0)
	{
		velocity = 300;
		speed.x = velocity;
		speed.y = velocity * 0.1f;
		checkXCollision = true;
		checkYCollision = false;
		SetFrameSize(28, 29);
		SetAnimation(0, 0);
	}
	else if(type == 1)
	{
		velocity = 500;
		speed.x = velocity;
		speed.y = velocity * 0.12f;
		checkXCollision = true;
		checkYCollision = false;
		SetFrameSize(16, 22);
		SetAnimation(0, 0);
	}
	else if(type == 2)
	{
		velocity = 700;
		shootVelocity = 3;
		shootTimer = 0;
		stopVelocity = 0.7f;
		stopTimer = 0;
		checkXCollision = false;
		checkYCollision = false;
		SetFrameSize(37, 37);
		SetAnimation(0, 1);
	}

	setRotation(180);
	SetAnimationSpeed(17);
}

void EntityEnemy::Initialize(GameScreen* screen)
{
	Application& App = screen->getApp();

	switch(type)
	{
		case 0: setTexture(App.getTexture("media\\stdEnemy.png")); break;
		case 1: setTexture(App.getTexture("media\\legEnemy.png")); break;
		case 2: setTexture(App.getTexture("media\\unEnemy.png")); break;
		default: setTexture(App.getTexture("media\\stdEnemy.png"));
	}

	Entity::Initialize(screen);

	if(type != 2)
	{
		setPosition(100.0f + rand() % int(App.getWidth() - 200), getGlobalBounds().height / 2);
	}
	else
	{
		setPosition(150.0f + (rand() % 2) * (App.getWidth() - 300.0f), 100.0f + rand() % int(App.getHeight() - 200));

		float posX = getPosition().x;
		float posY = getPosition().y;
		float playerPosX = screen->getPlayer()->getPosition().x;
		float playerPosY = screen->getPlayer()->getPosition().y;
		float dtPosX = playerPosX - posX;
		float dtPosY = playerPosY - posY;

		distance = sqrt(dtPosX * dtPosX + dtPosY * dtPosY);

		speedX = speed.x = dtPosX / distance * velocity;
		speedY = speed.y = dtPosY / distance * velocity;

		if(speed.x > 0)
		{
			SetAnimation(2, 3);
		}
		else
		{
			SetAnimation(4, 5);
		}
	}
}

void EntityEnemy::Update(float time)
{
	if(isAlive)
	{
		float posX = getPosition().x;
		float posY = getPosition().y;
		float sizeX = getGlobalBounds().width;
		float sizeY = getGlobalBounds().height;

		if(type != 2)
		{
			if(posX - sizeX / 2 <= 0)
			{
				speed.x = -speed.x;
				SetAnimation(1, 1);
			}
			else if(posX + sizeX / 2 >= screen->getApp().getWidth())
			{
				speed.x = -speed.x;
				SetAnimation(2, 2);
			}
		}

		if(type == 0)
		{
			if(shoot)
			{
				if(rand() % 1000 == 500)
				{
					weapon.Shoot();
				}
			}
		}
		else if(type == 1)
		{
			float playerPosX = screen->getPlayer()->getPosition().x;
			float playerSizeX = screen->getPlayer()->getGlobalBounds().width;

			if(posX <= playerPosX - playerSizeX * 2)
			{
				speed.x = velocity;
				SetAnimation(1, 1);
			}
			else if(posX >= playerPosX + playerSizeX * 2)
			{
				speed.x = -velocity;
				SetAnimation(2, 2);
			}
		}
		else if(type == 2)
		{
			if(distance > 0)
			{
				distance -= velocity * time;
			}

			if(distance < 0)
			{
				stopTimer += time;

				if(stopTimer > stopVelocity)
				{
					speed.x = speedX;
					speed.y = speedY;

					if(speed.x > 0)
					{
						SetAnimation(2, 3);
					}
					else
					{
						SetAnimation(4, 5);
					}
				}
				else
				{
					if(shoot)
					{
						shootTimer += time;

						if(shootTimer > 1 / shootVelocity)
						{
							bool downward = false;

							float playerPosX = screen->getPlayer()->getPosition().x;
							float playerPosY = screen->getPlayer()->getPosition().y;

							if(posY < playerPosY)
							{
								downward = true;
							}

							float angle = 0;

							float dirX = playerPosX - posX;
							float dirY = playerPosY - posY;
							float length = sqrt(dirX * dirX + dirY * dirY);
							dirX /= length;
							dirY /= length;

							if(dirX > 0)
							{
								angle = acos(-dirY) / acos(0.f) / 2 * 180 + (downward ? 180 : 0);
							}

							if(dirX < 0)
							{
								angle = acos(dirY) / acos(0.f) / 2 * 180 + (downward ? 360 : 180);
							}


							weapon.Shoot(downward, angle);

							shootTimer = 0;
						}
					}

					speed.x = 0;
					speed.y = 0;

					SetAnimation(0, 1);
				}
			}
		}
	}

	Entity::Update(time);
}

void EntityEnemy::Draw()
{
	if(isAlive && health < 100)
	{
		float posX = getPosition().x;
		float posY = getPosition().y;
		float sizeX = getGlobalBounds().width;
		float sizeY = getGlobalBounds().height;

		float barWidth = sizeX * 1.5f;
		float barHeight = 5;

		sf::RectangleShape redBar;
		redBar.setFillColor(sf::Color::Red);
		redBar.setPosition(posX - barWidth / 2, posY - sizeY * 1.04f - barHeight);
		redBar.setSize(sf::Vector2f(barWidth, barHeight));
		screen->getApp().draw(redBar);

		sf::RectangleShape greenBar;
		greenBar.setFillColor(sf::Color::Green);
		greenBar.setPosition(posX - barWidth / 2, posY - sizeY * 1.04f - barHeight);
		greenBar.setSize(sf::Vector2f(barWidth * health / 100.0f, barHeight));
		screen->getApp().draw(greenBar);
	}

	Entity::Draw();
}

void EntityEnemy::OnDeath()
{
	screen->getPlayer()->setPoints(screen->getPlayer()->getPoints() + 10);
	screen->getPlayer()->ChangeHealth(1);
	screen->SpawnExplosion(getPosition().x, getPosition().y);
	screen->SpawnShipwreck(this);
}

EntityType EntityEnemy::getEntityType() const
{
	return Enemy;
}