#pragma once
#include<sfml\Graphics.hpp>
#define MAX_ITEMS 3

class Menu
{
public:
	Menu(float width,float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetpressedItem() { return selectedItem; }

private:
	int selectedItem=0;
	sf::Font font;
	sf::Text menu[MAX_ITEMS];
};

