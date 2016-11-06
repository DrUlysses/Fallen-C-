#include "GuiScreenShop.hpp"

const int gunPrices[] =
{
	0,
	100,
	200,
	300,
	400,
	500,
	600,
	700,
	800,
	900
};

GuiScreenShop::GuiScreenShop(Application& App, GameScreen* gameScreen) : GuiScreen(App)
{
	this->gameScreen = gameScreen;
	shopTexture = App.getTexture("media\\shop.png");
	gunsTexture = App.getTexture("media\\shopAmmo.png");
	arrowTexture = App.getTexture("media\\arrow.png");
	drawBackground = false;
}

void GuiScreenShop::Handle(sf::Event event)
{
	if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B) || (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 3))
	{
		gameScreen->StartGame();
		App.SetScreen(gameScreen);
	}

	if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) || (event.type == sf::Event::JoystickMoved && event.joystickMove.position >= 98))
	{
		EntityPlayer* player = gameScreen->getPlayer();

		int pricePoints = gunPrices[player->getGunLevel() + 1];
		int playerPoints = player->getPoints();

		if(player->getGunLevel() <= 8 && playerPoints >= pricePoints)
		{
			player->setPoints(playerPoints - pricePoints);
			player->setGunLevel(player->getGunLevel() + 1);
			App.PlaySound("media\\successBuy.wav");
		}
		else
		{
			App.PlaySound("media\\noCash.wav");
		}
	}
}

void GuiScreenShop::Draw(sf::Time time)
{
	gameScreen->Draw(time);
	GuiScreen::Draw(time);

	float shopPosX = App.getWidth() - shopTexture.getSize().x;
	float shopPosY = 0;

	sf::Sprite sprite;
	sprite.setPosition(shopPosX, shopPosY);
	sprite.setTexture(shopTexture);
	sprite.setTextureRect(sf::IntRect(0, 0, shopTexture.getSize().x, shopTexture.getSize().y));
	App.draw(sprite);

	sf::Text shopTitle;
	shopTitle.setString("Shop");
	shopTitle.setFont(App.getButtonFont());
	shopTitle.setPosition(shopPosX + (shopTexture.getSize().x - shopTitle.getGlobalBounds().width) / 2, shopPosY + 9);
	App.draw(shopTitle);

	const int imageTileWidth = 30;
	const int imageTileHeight = 30;

	sf::Text gunsTitle;
	gunsTitle.setString("Guns");
	gunsTitle.setFont(App.getButtonFont());
	gunsTitle.setPosition(shopPosX + 15, shopPosY + 60 + (imageTileHeight - gunsTitle.getGlobalBounds().height * 2) / 2);
	App.draw(gunsTitle);

	int gunLevel = gameScreen->getPlayer()->getGunLevel();

	sf::IntRect firstAmmoRect;
	firstAmmoRect.left = (gunLevel % 5) * imageTileWidth;
	firstAmmoRect.top = (gunLevel / 5) * imageTileHeight;
	firstAmmoRect.width = imageTileWidth;
	firstAmmoRect.height = imageTileHeight;

	sf::RectangleShape firstAmmoBack;
	firstAmmoBack.setFillColor(sf::Color(110, 110, 110, 255));
	firstAmmoBack.setPosition(shopPosX + 100, shopPosY + 60);
	firstAmmoBack.setSize(sf::Vector2f(float(firstAmmoRect.width), float(firstAmmoRect.height)));
	App.draw(firstAmmoBack);

	sf::Sprite firstAmmo;
	firstAmmo.setPosition(shopPosX + 100, shopPosY + 60);
	firstAmmo.setTexture(gunsTexture);
	firstAmmo.setTextureRect(firstAmmoRect);
	App.draw(firstAmmo);

	if(gunLevel <= 9)
	{
		bool canBuy = gameScreen->getPlayer()->getPoints() >= gunPrices[gunLevel + 1];

		sf::IntRect secondAmmoRect;
		secondAmmoRect.left = ((gunLevel + 1) % 5) * imageTileWidth;
		secondAmmoRect.top = ((gunLevel + 1) / 5) * imageTileHeight;
		secondAmmoRect.width = imageTileWidth;
		secondAmmoRect.height = imageTileHeight;

		sf::RectangleShape secondAmmoBack;

		if(gunLevel != 9)
		{
			if(canBuy)
			{
				secondAmmoBack.setFillColor(sf::Color::Green);
			}
			else
			{
				secondAmmoBack.setFillColor(sf::Color::Red);
			}
		}
		else
		{
			secondAmmoBack.setFillColor(sf::Color::Red);
		}

		secondAmmoBack.setPosition(shopPosX + 150, shopPosY + 60);
		secondAmmoBack.setSize(sf::Vector2f(float(secondAmmoRect.width), float(secondAmmoRect.height)));
		App.draw(secondAmmoBack);

		sf::Sprite secondAmmo;
		secondAmmo.setPosition(shopPosX + 150, shopPosY + 60);
		secondAmmo.setTexture(gunsTexture);
		secondAmmo.setTextureRect(secondAmmoRect);
		App.draw(secondAmmo);

		if(gunLevel != 9)
		{
			sf::Text gunPrice;

			if(canBuy)
			{
				gunPrice.setColor(sf::Color::Green);
			}
			else
			{
				gunPrice.setColor(sf::Color::Red);
			}

			gunPrice.setString(std::to_string((_Longlong)gunPrices[gunLevel + 1]) + " pts.");
			gunPrice.setFont(App.getButtonFont());
			gunPrice.setScale(0.55f, 0.55f);
			gunPrice.setPosition(shopPosX + 230 + 12, shopPosY + 60 + (imageTileHeight - gunPrice.getGlobalBounds().height * 1.45f) / 2);
			App.draw(gunPrice);
		}
	}

	int arrowImageWidth = arrowTexture.getSize().x;
	int arrowImageHeight = arrowTexture.getSize().y;

	float arrowScaleX = (float)imageTileWidth / arrowImageWidth;
	float arrowScaleY = (float)imageTileHeight / arrowImageHeight;

	sf::Sprite arrow;
	arrow.setPosition(shopPosX + 200, shopPosY + 60);
	arrow.setScale(arrowScaleX, arrowScaleY);
	arrow.setTexture(arrowTexture);
	App.draw(arrow);
}