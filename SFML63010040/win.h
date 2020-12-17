#pragma once
#include<sfml\Graphics.hpp>
#define MAX_ITEMS 1

class win
{
public:
	win(float width, float height);
	~win();
	void draw(sf::RenderWindow& window);



private:
	int selectedItem = 0;
	sf::Font font;
	sf::Text Win[MAX_ITEMS];
};

class Win
{
};
