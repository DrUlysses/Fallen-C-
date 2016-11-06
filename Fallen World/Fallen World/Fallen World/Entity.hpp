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

	// Инициализирует объект
	virtual void Initialize(GameScreen* screen);

	// Задаёт текущую анимацию объекта
	void SetAnimation(const int& frameStart, const int& frameEnd);

	// Задаёт скорость анимации
	void SetAnimationSpeed(const float& animationSpeed);

	// Задаёт зацикливание анимации
	void SetAnimationLoop(const bool& animationLoop);

	// Задаёт смещение кадра
	void SetFrameOffset(const int& frameOffsetX, const int& frameOffsetY);

	// Задаёт размер одного кадра
	void SetFrameSize(const int& frameWidth, const int& frameHeight);

	// Изменяет здоровье объекта
	void ChangeHealth(const int& deltaHealth);

	// Обновляет данные объекта
	virtual void Update(float time);

	// Отрисовывает объект
	virtual void Draw();

	// Возвращает тип объекта
	virtual EntityType getEntityType() const { return Enemy; };

	// Событие окна
	virtual void OnEvent(sf::Event event) { };

	// Событие смерти объекта
	virtual void OnDeath() { };

	// Событие конца цикла анимации
	virtual void OnAnimationStopped() { };

	// Возвращает истину, если объект мёртв
	bool IsDead() const;

	// Возвращает истину, если объект больше не используется
	const bool& IsOver() const;

	// Возвращает истину, если между объектами есть столкновение
	bool DoesCollide(const Entity* entity) const;

	// Помечает объект как мёртвый
	void SetAsDead();

	// Помечает объект как неиспользуемый
	void SetAsOver();

	// Получает здоровье объекта
	const int& getHealth() const;

	// Получает экран, к которому принадлежит этот объект
	GameScreen* getScreen() const;
};

enum WeaponType
{
	WEAPON_0,//просто одна пуля
	WEAPON_1,//две таких же
	WEAPON_2,//три, боковые немного расходятся
	WEAPON_3,//четыре, летят кучно, тоже расходятся 
	WEAPON_4,//пять
	WEAPON_5,//шесть
	WEAPON_6,//семь
	WEAPON_7,//семь, случайно выстрел по окружности
	WEAPON_8,//выстрел по окружности, случайно ракета(ваншотит)
	WEAPON_9, //самонаводящиеся
	WEAPON_E// Пули врагов
};

class Weapon
{
	WeaponType weaponType;
	Entity* entityOwner; 
	bool downward;

public:

	Weapon();
	Weapon(const WeaponType& weaponType, Entity* entityOwner, const bool& downward);

	// Производит выстрел из позиции объекта
	void Shoot();

	// Производит выстрел, но направление движения пули не зависит от значений, заданных в конструкторе
	// Доступно только для некоторых видов оружия
	void Shoot(const bool& downward, const float& angle);
};

#endif