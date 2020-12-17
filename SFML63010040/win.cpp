#include "win.h"

win::win(float width, float height)
{
	if (!font.loadFromFile("Pure Joy.ttf")) {

	}
	

	
	Win[0].setFont(font);
	Win[0].setCharacterSize(100);
	Win[0].setFillColor(sf::Color::Yellow);
	Win[0].setString("""ENTER FOR EXIT""");
	Win[0].setOrigin(Win[0].getGlobalBounds().width / 2, Win[0].getGlobalBounds().height / 2);
	Win[0].setPosition(sf::Vector2f(950, 800));


}
win::~win()
{

}

void win::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEMS; i++) {
		window.draw(Win[i]);
	}
}
