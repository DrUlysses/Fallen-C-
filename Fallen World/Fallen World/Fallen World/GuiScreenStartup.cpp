#include "GuiScreenStartup.hpp"
#include "GuiScreenMainMenu.hpp"

GuiScreenStartup::GuiScreenStartup(Application& App) : GuiScreen(App)
{
	counter = false;
}

void GuiScreenStartup::Draw(sf::Time time)
{
	float sw = App.getWidth();
	float sh = App.getHeight();
	sf::Texture& texture = App.getLogoTexture();
	sf::Music* music = App.getMusic("media\\startMenu.ogg");

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition((sw - texture.getSize().x) / 2, (sh - texture.getSize().y) / 2);
	sprite.setColor(sf::Color(255, 255, 255, (int)(counter / 2000 * 255)));
	App.draw(sprite);

	if (music->getStatus() != sf::SoundSource::Playing)
	{
		music->setVolume(3);
		music->setLoop(false);
		music->play();
	}

	counter += time.asMicroseconds() / 1000.f;

	if(counter > 2000)
	{
		App.getMusic("media\\startMenu.ogg")->stop();
		App.SetScreen(new GuiScreenMainMenu(App));
	}
}