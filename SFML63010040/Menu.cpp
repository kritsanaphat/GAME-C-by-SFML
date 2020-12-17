#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Pure Joy.ttf")) {

	}
	menu[0].setFont(font);
	menu[0].setCharacterSize(72);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setOrigin(menu[0].getGlobalBounds().width / 2, menu[0].getGlobalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setCharacterSize(72);
	menu[1].setFillColor(sf::Color::Yellow);
	menu[1].setString("Leaderboard ");
	menu[1].setOrigin(menu[1].getGlobalBounds().width / 2, menu[1].getGlobalBounds().height / 2);
	menu[1].setPosition(sf::Vector2f(width/2, height/(MAX_ITEMS+1)*2));

	menu[2].setFont(font);
	menu[2].setCharacterSize(72);
	menu[2].setFillColor(sf::Color::Yellow);
	menu[2].setString("Exit");
	menu[2].setOrigin(menu[2].getGlobalBounds().width / 2, menu[1].getGlobalBounds().height / 2);
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 3));

}
Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEMS; i++) {
		window.draw(menu[i]);
	}
}
void Menu::MoveUp() {
	if (selectedItem - 1 >= 0)
	{
		menu[selectedItem].setFillColor(sf::Color::Yellow);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown() {
	if (selectedItem + 1 < MAX_ITEMS)
	{
		menu[selectedItem].setFillColor(sf::Color::Yellow);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}