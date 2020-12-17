#include "lederboard.h"

lederboard::lederboard(float width, float height)
{
	if (!font.loadFromFile("Pure Joy.ttf")) {

	}
	Lederboard[0].setFont(font);
	Lederboard[0].setCharacterSize(72);
	Lederboard[0].setFillColor(sf::Color::Red);
	Lederboard[0].setString("BACK");
	Lederboard[0].setOrigin(Lederboard[0].getGlobalBounds().width / 2, Lederboard[0].getGlobalBounds().height / 2);
	Lederboard[0].setPosition(sf::Vector2f(150, 800));

}
lederboard::~lederboard()
{

}

void lederboard::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEMS; i++) {
		window.draw(Lederboard[i]);
	}
}
void lederboard::MoveUp() {
	if (selectedItem - 1 >= 0)
	{
		Lederboard[selectedItem].setFillColor(sf::Color::Yellow);
		selectedItem--;
		Lederboard[selectedItem].setFillColor(sf::Color::Red);
	}
}

void lederboard::MoveDown() {
	if (selectedItem + 1 < MAX_ITEMS)
	{
		Lederboard[selectedItem].setFillColor(sf::Color::Yellow);
		selectedItem++;
		Lederboard[selectedItem].setFillColor(sf::Color::Red);
	}
}