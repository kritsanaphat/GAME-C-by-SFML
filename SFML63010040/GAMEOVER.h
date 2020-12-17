#pragma once
#include<sfml\Graphics.hpp>
#define MAX_ITEMS 2

class gameover
{
public:
	gameover(float width, float height);
	~gameover();

	void draw(sf::RenderWindow& window);
	void MoveLeft();
	void MoveRight();
	int GetpressedItem() { return selectedItem; }

private:
	int selectedItem = 0;
	sf::Font font;
	sf::Text Gameover[MAX_ITEMS];
};

class Gameover
{
};

