#pragma once
#include<SFML/Graphics.hpp>
#include<sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
	Textbox(int size, sf::Color color, bool sel) {
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isselected = sel;
		if (sel) {
			textbox.setString("_");
		}
		else {
			textbox.setString("");
		}
	}

	void setFont(sf::Font& font) {
		textbox.setFont(font);
	}

	void setPosition(sf::Vector2f pos) {
		textbox.setPosition(pos);
	}
	void setlimit(bool ToF) {
		haslimit = ToF;
	}
	void setlimit(bool ToF, int lim) {
		haslimit = ToF;
		limit = lim;
	}
	void setSelected(bool sel) {
		isselected = sel;
		if (!sel) {
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length() - 1; i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}
	std::string gettext() {
		return text.str();
	}
	void drawTo(sf::RenderWindow& window) {
		window.draw(textbox);
	}

	void typeOn(sf::Event input) {
		if (isselected) {
			int charTyped = input.text.unicode;
			if (charTyped < 128) {
				if (haslimit) {
					if (text.str().length() <= limit) {
						inputLogic(charTyped);
					}
					else if (text.str().length() > limit && charTyped == DELETE_KEY) {
						deleteLastchar();
					}
				}
				else {
					inputLogic(charTyped);
				}
			}
		}
	}
private:
	sf::Text textbox;
	std::ostringstream text;
	bool isselected = false;
	bool haslimit = false;
	int limit;

	void inputLogic(int chartyped) {
		if (chartyped != DELETE_KEY && chartyped != ENTER_KEY && chartyped != ESCAPE_KEY) {
			text << static_cast<char>(chartyped);
		}
		else if (chartyped == DELETE_KEY) {
			if (text.str().length() > 0) {
				deleteLastchar();
			}
		}
		textbox.setString(text.str() + "_");
	}
	void deleteLastchar() {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i];
		}
		text.str("");
		text << newT;
		textbox.setString(text.str());
	}
};
