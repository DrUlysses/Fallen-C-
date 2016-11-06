#include "Application.hpp"

int main()
{
	sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

	return Application(videoMode.width - 300, videoMode.height - 300, "Fallen World").Run();
}