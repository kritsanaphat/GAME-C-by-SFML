#include "GAMEOVER.h"

gameover::gameover(float width, float height)
{
	if (!font.loadFromFile("Pure Joy.ttf")) {

	}
	Gameover[0].setFont(font);
	Gameover[0].setCharacterSize(150);
	Gameover[0].setFillColor(sf::Color::Yellow);
	Gameover[0].setString("!!!! YOU LOSE !!!! ");
	Gameover[0].setOrigin(Gameover[0].getGlobalBounds().width / 2, Gameover[0].getGlobalBounds().height / 2);
	Gameover[0].setPosition(sf::Vector2f(1000, 200));

	Gameover[1].setFont(font);
	Gameover[1].setCharacterSize(100);
	Gameover[1].setFillColor(sf::Color::Yellow);
	Gameover[1].setString("""ENTER FOR EXIT""");
	Gameover[1].setOrigin(Gameover[1].getGlobalBounds().width / 2, Gameover[1].getGlobalBounds().height / 2);
	Gameover[1].setPosition(sf::Vector2f(1000,800));


}
gameover::~gameover()
{

}

void gameover::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEMS; i++) {
		window.draw(Gameover[i]);
	}
}
void gameover::MoveLeft() {
	if (selectedItem -1 == 0)
	{
		Gameover[selectedItem].setFillColor(sf::Color::Yellow);
		selectedItem--;
		Gameover[selectedItem].setFillColor(sf::Color::Red);
	}
}

void gameover::MoveRight() {
	if (selectedItem + 1 == 1)
	{
		Gameover[selectedItem].setFillColor(sf::Color::Yellow);
		selectedItem++;
		Gameover[selectedItem].setFillColor(sf::Color::Red);
	}
}