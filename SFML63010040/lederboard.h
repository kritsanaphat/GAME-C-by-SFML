#pragma once
#include<sfml\Graphics.hpp>
#define MAX_ITEMS 1

class lederboard
{
public:
	lederboard(float width, float height);
	~lederboard();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetpressedItem() { return selectedItem; }

private:
	int selectedItem = 0;
	sf::Font font;
	sf::Text Lederboard[MAX_ITEMS];
};

