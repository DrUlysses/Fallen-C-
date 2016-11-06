#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include <SFML\Graphics.hpp>

// Класс приложения объявлен для того, чтобы можно было использовать перекрёстное объявление:
// В классе приложения хранится указатель на экран, в классе экрана - ссылка на приложение
class Application;

// Абстрактный класс, который должен быть унаследован любым экраном
class Screen
{
protected:

	Application& App;

public:

	Screen(Application& App);

	// Реализуется экраном-наследником для обработки событий окна
	virtual void Handle(sf::Event event) = 0;

	// Реализуется экраном-наследником для рендеринга содержимого экрана
	virtual void Draw(sf::Time time) = 0;
};

#endif