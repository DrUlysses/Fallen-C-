#ifndef _GAMESCREEN_HPP_
#define _GAMESCREEN_HPP_

#include "Screen.hpp"
#include "Entity.hpp"
#include "EntityPlayer.hpp"
#include "EntityBullet.hpp"
#include "EntityEnemy.hpp"
#include "EntityStar.hpp"
#include "EntityExplosion.hpp"
#include "EntityParticle.hpp"
#include "EntityShipwreck.hpp"
#include <list>
#include <SFML/Audio.hpp>

// ����� ����
class GameScreen : public Screen
{
	std::list<Entity*> entities;
	std::list<EntityBullet*> bullets;
	std::list<EntityEnemy*> enemies;
	EntityPlayer* player;
	float enemySpawnTimer;
	float enemySpawnSpeed;
	float starSpawnTimer;
	float starSpawnSpeed;
	float gameTimer;
	float gameSpeed;
	float fMusicTimer;
	int iMusicTimer;
	bool isGameActive;
	bool friendlyFire;
	sf::Music* music;

	sf::Font font;
	sf::Text hpBar, youWin;
	sf::Clock clock;
	float timer;

public:

	bool enemyAttack;

	GameScreen(Application& App, sf::String pName, int points = 0, int gunLevel = 0, int health = 100);

	// ����� ��������� ������� ��������
	void SpawnBullet(const float& posX, const float& posY, const EntityType& senderType, const BulletType& bulletType, const bool& downward, const float& angle = 0);
	void SpawnEnemy(const int& type);
	void SpawnStar();
	void SpawnExplosion(const float& posX, const float& posY);
	void SpawnParticles(const float& posX, const float& posY, const int& density = 4);
	void SpawnShipwreck(Entity* ship);

	// �������� ����� ����
	void UpdateLoop(float time);
	void CollisionLoop(float time);
	void SpawnLoop(float time);
	void DrawLoop(float time);

	// ��������� ������� ����
	void Handle(sf::Event event);

	// ��������� �������� ����
	void Draw(sf::Time time);

	// �������� ������ �� ����������
	Application& getApp();

	// �������� ���������� ����������
	EntityEnemy* getNearestEnemy(const float& posX, const float& posY);

	// �������� ������
	EntityPlayer* getPlayer();

	// ���������� ������, ���� ���� �������
	const bool& IsGameActive() const;

	// ���������/����������� ����
	void PauseGame();
	void StartGame();
};

#endif