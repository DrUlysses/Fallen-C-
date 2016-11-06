#include "GameScreen.hpp"
#include "Application.hpp"
#include "GuiScreenPause.hpp"
#include "GuiScreenMainMenu.hpp"
#include "GuiScreenShop.hpp"
#include "GameFileScores.hpp"
#include <sstream>

GameScreen::GameScreen(Application& App, sf::String pName, int points, int gunLevel, int health) : Screen(App)
{
	enemySpawnTimer = 0;
	enemySpawnSpeed = 0.5f;
	starSpawnTimer = 0;
	starSpawnSpeed = 4;
	gameTimer = 0;
	gameSpeed = 0.95f;
	fMusicTimer = 0;
	iMusicTimer = 0;
	isGameActive = true;
	friendlyFire = false;
	music = App.getMusic("media\\gameMusic.ogg");
	music->setLoop(false);
	music->setVolume(3);
	music->stop();

	player = new EntityPlayer(pName, points, gunLevel, health);
	player->Initialize(this);

	App.getTexture("media\\explosion.png");

	srand(int(pName.getData()));
}

void GameScreen::SpawnBullet(const float& posX, const float& posY, const EntityType& senderType, const BulletType& bulletType, const bool& downward, const float& angle)
{
	EntityBullet* bullet = new EntityBullet(senderType, bulletType, downward, angle);
	bullet->Initialize(this);
	bullet->setPosition(posX, posY);
	bullets.push_back(bullet);
	entities.push_back(bullet);
}

void GameScreen::SpawnEnemy(const int& type)
{
	EntityEnemy* enemy = new EntityEnemy(type);
	enemy->Initialize(this);
	enemies.push_back(enemy);
	entities.push_back(enemy);
}

void GameScreen::SpawnStar()
{
	EntityStar* star = new EntityStar();
	star->Initialize(this);
	entities.push_back(star);
}

void GameScreen::SpawnExplosion(const float& posX, const float& posY)
{
	EntityExplosion* explosion = new EntityExplosion();
	explosion->Initialize(this);
	explosion->setPosition(posX, posY);
	entities.push_back(explosion);
}

void GameScreen::SpawnParticles(const float& posX, const float& posY, const int& density)
{
	int count = density + rand() % 7;

	for(int i = 0; i < count; ++i)
	{
		EntityParticle* particle = new EntityParticle(sf::Vector2f(posX, posY));
		particle->Initialize(this);
		entities.push_back(particle);
	}
}

void GameScreen::SpawnShipwreck(Entity* ship)
{
	int shipwreckDepth = 2 + rand() % 4;
	int shipwreckCount = shipwreckDepth * shipwreckDepth;

	for(int i = 0; i < shipwreckCount; ++i)
	{
		EntityShipwreck* shipwreck = new EntityShipwreck(ship, i, shipwreckDepth);
		shipwreck->Initialize(this);
		entities.push_back(shipwreck);
	}
}

void GameScreen::UpdateLoop(float time)
{
	std::list<Entity*>::iterator it;

	for(it = entities.begin(); it != entities.end();)
	{
		Entity* entity = *it;

		entity->Update(time);

		if(entity->IsOver())
		{
			switch(entity->getEntityType())
			{
				case Bullet:
					bullets.remove(dynamic_cast<EntityBullet*>(entity));
					break;
				case Enemy:
					enemies.remove(dynamic_cast<EntityEnemy*>(entity));
					player->RemoveFromCollisionList(dynamic_cast<EntityEnemy*>(entity));
					break;
			}

			entities.erase(it++);

			delete entity;
		}
		else
		{
			++it;
		}
	}

	player->Update(time);
}

void GameScreen::CollisionLoop(float time)
{
	std::list<EntityBullet*>::iterator bIt;

	for(bIt = bullets.begin(); bIt != bullets.end(); ++bIt)
	{
		EntityBullet* bullet = *bIt;

		std::list<EntityEnemy*>::iterator eIt;

		for(eIt = enemies.begin(); eIt != enemies.end(); ++eIt)
		{
			EntityEnemy* enemy = *eIt;

			bool checkEnemyCollision = true;

			if(!friendlyFire && bullet->getSenderType() == Enemy)
			{
				checkEnemyCollision = false;
			}

			if(checkEnemyCollision)
			{
				if(bullet->DoesCollide(enemy))
				{
					if(bullet->getBulletType() == 7)
					{
						enemy->ChangeHealth(-100);
						bullet->SetAsOver();
						SpawnParticles(enemy->getPosition().x, enemy->getPosition().y);
						break;
					}
					else
					{
						enemy->ChangeHealth(-50);
						bullet->SetAsOver();
						SpawnParticles(enemy->getPosition().x, enemy->getPosition().y);
						break;
					}
				}
				if(iMusicTimer >= 187)
				{
					enemy->ChangeHealth(-100);
				}
			}
		}

		if(bullet->getSenderType() != Player)
		{
			if(bullet->DoesCollide(player))
			{
				player->ChangeHealth(-25);
				bullet->SetAsOver();
				SpawnParticles(player->getPosition().x, player->getPosition().y, 20);
			}
		}
	}

	std::list<EntityEnemy*>::iterator eIt;

	for(eIt = enemies.begin(); eIt != enemies.end(); ++eIt)
	{
		EntityEnemy* enemy = *eIt;

		if(enemy->DoesCollide(player) && !player->IsInCollisionList(enemy))
		{
			enemy->ChangeHealth(-100);
			player->ChangeHealth(-50);
			player->AddToCollisionList(enemy);
			SpawnParticles(player->getPosition().x, player->getPosition().y);
			break;
		}
	}
}

void GameScreen::SpawnLoop(float time)
{
	if(enemySpawnTimer > 1 / enemySpawnSpeed)
	{
		if(rand() % 5 == 4 && iMusicTimer >= 25)
		{
			SpawnEnemy(1);
		}

		if(iMusicTimer == 129 || iMusicTimer == 135 || iMusicTimer == 139 || iMusicTimer == 142 || iMusicTimer == 149 || iMusicTimer >= 155)
		{
			SpawnEnemy(2);
		}

		SpawnEnemy(0);
		enemySpawnTimer = 0;
	}

	if(starSpawnTimer > 1 / starSpawnSpeed)
	{
		SpawnStar();
		starSpawnTimer = 0;
	}

	enemySpawnTimer += time;
	starSpawnTimer += time;
}

void GameScreen::DrawLoop(float time)
{
	if(fMusicTimer > 0.01f && iMusicTimer <= 7)
	{
		sf::Text welcome;
		welcome.setFont(getApp().getButtonFont());
		welcome.setCharacterSize(30);
		welcome.setString("\"Space\" for shoot\n\"Esc\" for pause, \"B\" for Shop");
		welcome.setPosition(App.getWidth() / 2.f, App.getHeight() / 2.f + fMusicTimer * 70);
		getApp().draw(welcome);
		if(sf::Joystick::isConnected(0))
		{
			sf::Text jwelcome;
			jwelcome.setFont(getApp().getButtonFont());
			jwelcome.setCharacterSize(30);
			jwelcome.setString("\"X or trigger\" for shoot\n\"Start\" for pause, \"Y\" for Shop");
			jwelcome.setPosition(App.getWidth() / 6.f, App.getHeight() / 2.f + fMusicTimer * 70);
			getApp().draw(jwelcome);
		}
	}

	std::list<Entity*>::iterator it;

	for(it = entities.begin(); it != entities.end(); ++it)
	{
		(*it)->Draw();
	}

	player->Draw();

	if(player->IsDead())
	{
		float posX = player->getPosition().x;
		float posY = player->getPosition().y;
		float sizeX = player->getGlobalBounds().width;
		float sizeY = player->getGlobalBounds().height;
		float screenWidth = App.getWidth();
		float screenHeight = App.getHeight();

		sf::Text text;
		text.setFont(getApp().getButtonFont());
		text.setCharacterSize(15);
		if(sf::Joystick::isConnected(0))
			text.setString("B to Restart\nStart to Escape");
		else
			text.setString("R to Restart\nEsc to Escape");

		float textPosX = posX + sizeX;
		float textPosY = posY + sizeY;
		float textSizeX = text.getGlobalBounds().width;
		float textSizeY = text.getGlobalBounds().height;

		if(textPosY > screenHeight - textSizeY)
		{
			textPosY = posY - textSizeY;
		}

		if(textPosX > screenWidth - textSizeX)
		{
			textPosX = posX - textSizeX;
		}

		float offset = sin(gameTimer * 6) * 3;

		text.setPosition(textPosX + offset, textPosY + offset);

		getApp().draw(text);
	}

	std::ostringstream infoString;
	infoString << "Health: " << player->getHealth() << std::endl;
	infoString << "Points: " << player->getPoints() << std::endl;
	infoString << "\nArtist: Carpenter Brut\nSong: Turbo Killer" << std::endl;

	sf::Text infoBar;
	infoBar.setFont(App.getButtonFont());
	infoBar.setCharacterSize(20);
	infoBar.setColor(sf::Color::Green);
	infoBar.setString(infoString.str());
	App.draw(infoBar);

	if(iMusicTimer >= 187)
	{
		sf::Text congratulations;
		congratulations.setFont(App.getButtonFont());
		congratulations.setCharacterSize(30);
		congratulations.setString("You finaly survived... yet\nEsc to Escape");
		congratulations.setPosition(App.getWidth() / 2, App.getHeight() / 2);
		App.draw(congratulations);
	}
}

void GameScreen::Handle(sf::Event event)
{
	if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 7))
	{
		PauseGame();
		App.SetScreen(new GuiScreenPause(App, this), false);
	}

	if(((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) || (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 1)) && player->IsDead())
	{
		music->stop();
		App.SetScreen(new GameScreen(App, player->getName()), true);
	}

	if(((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B) || (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 3)) && !player->IsDead())
	{
		PauseGame();
		App.SetScreen(new GuiScreenShop(App, this), false);
	}
}

void GameScreen::Draw(sf::Time time_)
{
	float time = time_.asSeconds() * gameSpeed;

	if(isGameActive)
	{
		if(music->getStatus() != sf::SoundSource::Playing)
		{
			music->play();
		}

		UpdateLoop(time);
		CollisionLoop(time);
		SpawnLoop(time);
	}

	fMusicTimer = music->getPlayingOffset().asSeconds();
	iMusicTimer = int(fMusicTimer);

	if(iMusicTimer >= 187)
	{
		if(isGameActive)
		{
			GameFileScores scores;
			scores.LoadFile("scores.dat");
			scores.AddPlayer(player->getName(), player->getPoints());
			scores.SaveFile("scores.dat");
			isGameActive = false;
		}
	}
	else if(iMusicTimer >= 170 && fMusicTimer < 175)
	{
		gameSpeed = 0.5f;
	}
	else if(iMusicTimer >= 169)
	{
		gameSpeed = 1.7f;
		enemySpawnSpeed = 2.5f;
	}
	else if(iMusicTimer >= 116 && iMusicTimer <= 129)
	{
		gameSpeed = 1.35f;
	}
	else if(iMusicTimer >= 89 && iMusicTimer <= 115)
	{
		enemySpawnSpeed = 2.f;
	}
	else if(iMusicTimer >= 78 && iMusicTimer <= 90)
	{
		gameSpeed = 1.f;
	}
	else if(iMusicTimer >= 51 && fMusicTimer < 64)
	{
		gameSpeed = 0.5f;
		enemySpawnSpeed = 1.5f;
	}
	else if(iMusicTimer > 24.5f)
	{
		gameSpeed = 1.35f;
		enemySpawnSpeed = 1.35f;
	}

	DrawLoop(time);

	gameTimer += time;
}

Application& GameScreen::getApp()
{
	return App;
}

EntityEnemy* GameScreen::getNearestEnemy(const float& posX, const float& posY)
{
	if(enemies.size() == 0)
	{
		return 0;
	}

	std::list<EntityEnemy*>::iterator eIt;

	EntityEnemy* nearestEnemy = *enemies.begin();

	float dtX = nearestEnemy->getPosition().x - posX;
	float dtY = nearestEnemy->getPosition().y - posY;
	float minDistance = dtX * dtX + dtY * dtY;

	for(eIt = std::next(enemies.begin(), 1); eIt != enemies.end(); ++eIt)
	{
		EntityEnemy* enemy = *eIt;

		dtX = nearestEnemy->getPosition().x - posX;
		dtY = nearestEnemy->getPosition().y - posY;

		if(minDistance > dtX * dtX + dtY * dtY && !enemy->IsDead())
		{
			nearestEnemy = enemy;
		}
	}

	if(nearestEnemy->IsDead())
	{
		return 0;
	}

	return nearestEnemy;
}

EntityPlayer* GameScreen::getPlayer()
{
	return player;
}

const bool& GameScreen::IsGameActive() const
{
	return isGameActive;
}

void GameScreen::PauseGame()
{
	music->pause();
	isGameActive = false;
}

void GameScreen::StartGame()
{
	music->play();
	isGameActive = true;
}