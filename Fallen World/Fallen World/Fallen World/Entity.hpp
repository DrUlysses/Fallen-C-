#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include "Screen.hpp"
#include "Application.hpp"

class GameScreen;

enum EntityType 
{ 
	Player,
	Enemy,
	Star,
	Bullet 
};

class Entity : public sf::Sprite
{
protected:

	GameScreen* screen;

	int frameStart;
	int frameEnd;
	int frameCurrent;
	float frameTimer;
	float animationSpeed;
	bool animationLoop;
	bool animationPlay;
	int frameOffsetX;
	int frameOffsetY;
	int frameWidth;
	int frameHeight;

	bool checkXCollision;
	bool checkYCollision;
	sf::Vector2f speed;
	float rotationRate;

	int health;
	bool isAlive;
	bool isOver;
	bool isWait;

public:

	Entity();

	// �������������� ������
	virtual void Initialize(GameScreen* screen);

	// ����� ������� �������� �������
	void SetAnimation(const int& frameStart, const int& frameEnd);

	// ����� �������� ��������
	void SetAnimationSpeed(const float& animationSpeed);

	// ����� ������������ ��������
	void SetAnimationLoop(const bool& animationLoop);

	// ����� �������� �����
	void SetFrameOffset(const int& frameOffsetX, const int& frameOffsetY);

	// ����� ������ ������ �����
	void SetFrameSize(const int& frameWidth, const int& frameHeight);

	// �������� �������� �������
	void ChangeHealth(const int& deltaHealth);

	// ��������� ������ �������
	virtual void Update(float time);

	// ������������ ������
	virtual void Draw();

	// ���������� ��� �������
	virtual EntityType getEntityType() const { return Enemy; };

	// ������� ����
	virtual void OnEvent(sf::Event event) { };

	// ������� ������ �������
	virtual void OnDeath() { };

	// ������� ����� ����� ��������
	virtual void OnAnimationStopped() { };

	// ���������� ������, ���� ������ ����
	bool IsDead() const;

	// ���������� ������, ���� ������ ������ �� ������������
	const bool& IsOver() const;

	// ���������� ������, ���� ����� ��������� ���� ������������
	bool DoesCollide(const Entity* entity) const;

	// �������� ������ ��� ������
	void SetAsDead();

	// �������� ������ ��� ��������������
	void SetAsOver();

	// �������� �������� �������
	const int& getHealth() const;

	// �������� �����, � �������� ����������� ���� ������
	GameScreen* getScreen() const;
};

enum WeaponType
{
	WEAPON_0,//������ ���� ����
	WEAPON_1,//��� ����� ��
	WEAPON_2,//���, ������� ������� ����������
	WEAPON_3,//������, ����� �����, ���� ���������� 
	WEAPON_4,//����
	WEAPON_5,//�����
	WEAPON_6,//����
	WEAPON_7,//����, �������� ������� �� ����������
	WEAPON_8,//������� �� ����������, �������� ������(��������)
	WEAPON_9, //���������������
	WEAPON_E// ���� ������
};

class Weapon
{
	WeaponType weaponType;
	Entity* entityOwner; 
	bool downward;

public:

	Weapon();
	Weapon(const WeaponType& weaponType, Entity* entityOwner, const bool& downward);

	// ���������� ������� �� ������� �������
	void Shoot();

	// ���������� �������, �� ����������� �������� ���� �� ������� �� ��������, �������� � ������������
	// �������� ������ ��� ��������� ����� ������
	void Shoot(const bool& downward, const float& angle);
};

#endif