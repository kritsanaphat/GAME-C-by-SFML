#define _CRT_SECURE_NO_WARNINGS


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>
#include "Menu.h"
#include "lederboard.h"
#include "GAMEOVER.h"
#include "Textbox.h"
#include "win.h"


int dead = 0;
float debounce = 0;
int cnt;
int j;
char scorechar[20];
int score = 0;
int heart = 3;
int numb =0;
int itemchk = 0;
int itemshot = 0;
int i;
int startgame = 0;
int rd1;
int z = 0;
int pst = 0, pst1[6];
int chk_1[6] = { 0 };
int animationFrame = 0;
float x = 0, y = 0;
int chkwin=5;
clock_t start = -0.5, end = 0;


std::vector<std::pair<std::string, int>> vec;
bool sortbysecdesc(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b);

float deltatime = 0.0f;
sf::Font font;
sf::Text score1;
sf::Text score2;
sf::Text score3;
sf::Texture HEART;
sf::Texture ITEM;
sf::Texture ITEM1;
sf::Texture BULLET;
sf::Texture BULLET1;
sf::Texture monsterTexture;
sf::Texture playerTexture;
sf::Texture BackgroundTexture;
sf::Texture BOSS;
sf::Texture BOSS2;
sf::Texture BOSS3;
sf::Texture BOSS4;
sf::Texture BOSS5;


sf::Sprite heart1;
sf::Sprite heart2;
sf::Sprite heart3;
sf::Sprite item;
sf::Sprite item1;
sf::Sprite shapeSprite;
sf::Sprite background;
sf::Vector2f spawnPoint = { 900.f, 500.f };

sf::SoundBuffer soundeffect3;
sf::Sound soundgetDamage;


//score
sf::Text textscore;


//high score
sf::Text HighScoreText;


sf::Text hname, hscore;


void Control();
void shot(); 
void getitem();
void getitem1();
void showscore();

class Bullet {
public:
	sf::Sprite bullet;

	void setfrist() {
		bullet.setTexture(BULLET);
		bullet.setTextureRect(sf::IntRect(0, 0, 50, 50));
	}

	void set(int x, int y)
	{
		if (itemshot == 1) {
			BULLET1.loadFromFile("imgSFMLgaMe/extrabullet.png");
			bullet.setTexture(BULLET1);
			bullet.setTextureRect(sf::IntRect(0, 0, 60, 60));
			itemshot = 2;
		}
		else {
			bullet.setTexture(BULLET);
			bullet.setTextureRect(sf::IntRect(0, 0, 50, 50));
		}
		bullet.setPosition(x, y);
	}
};

Bullet bullet[6];

class Monster {
public:
	int animation = 0;
	sf::Sprite monster;
	int hit = 0;

	void set(int x, int y)
	{
		monster.setTexture(monsterTexture);
		monster.setPosition(x, y);
	}

	void move()
	{
		animation++;
		int k = 0, p = 0;
		k = monster.getPosition().x;
		p = monster.getPosition().y;
		if (shapeSprite.getPosition().y + (shapeSprite.getGlobalBounds().height - monster.getGlobalBounds().height) / 2 > p)
		{
			monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 65, 0, 65, 84));
			monster.move(0, 0.19);
		}
		else if (shapeSprite.getPosition().y + (shapeSprite.getGlobalBounds().height - monster.getGlobalBounds().height) / 2 < p)
		{
			monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 65, 100 * 3, 65, 84));
			monster.move(0, -0.19);
		}
		if (shapeSprite.getPosition().x> k)
		{
			monster.move(0.30, 0);
			if (shapeSprite.getPosition().x -100> k)
			{
				monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 65, 100 * 2, 65, 84));
			}
		}
		else if (shapeSprite.getPosition().x< k)
		{
			monster.move(-0.30, 0);
			if (shapeSprite.getPosition().x+100 < k) {
				monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 65, 100, 65, 84));
			}
		}


		if (monster.getGlobalBounds().intersects(shapeSprite.getGlobalBounds())) {
			heart--;
			rd1 = rand() % 1001;
			if (rand() % 2 == 0) {
				monster.setPosition(sf::Vector2f(-30, rd1));
			}
			else monster.setPosition(sf::Vector2f(1800, rd1));
		}
		if (itemshot == 0) {
			for (int i = 0; i < 4; i++) {
				if (monster.getGlobalBounds().intersects(bullet[i].bullet.getGlobalBounds())) {
					numb++;
					rd1 = rand() % 1001;
					chk_1[i] = 0;
					bullet[i].bullet.setPosition(sf::Vector2f(-5000, -5000));
					if (rand() % 2 == 0) {
						monster.setPosition(sf::Vector2f(-30, rd1));
					}
					else monster.setPosition(sf::Vector2f(1800, rd1));
					score = score + 10;
					break;
				}
			}
		}
		else for (int i = 0; i < 4; i++) {
			if (monster.getGlobalBounds().intersects(bullet[i].bullet.getGlobalBounds())) {
				numb++;
				rd1 = rand() % 1001;
				if (rand() % 2 == 0) {
					monster.setPosition(sf::Vector2f(-30, rd1));
				}
				else monster.setPosition(sf::Vector2f(1800, rd1));
				itemshot = 0;
				score = score + 10;
				textscore.setString("SCORE : " + std::to_string(score));
				break;
			}
		}
	}
};

Monster monster[4];

class Boss1 {
public:
	int blood = -1;
	int animation = 0;
	sf::Sprite monster;
	int hit = 0;

	void set(int x, int y)
	{
		blood =5;
		monster.setTexture(BOSS);
		monster.setPosition(x, y);
	}

	void move()
	{
		animation++;
		int k = 0, p = 0;
		k = monster.getPosition().x;
		p = monster.getPosition().y;
		if (shapeSprite.getPosition().y + (shapeSprite.getGlobalBounds().height - monster.getGlobalBounds().height) / 2 > p)
		{
			monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 0, 120, 168));
			monster.move(0, 0.15);
		}
		else if (shapeSprite.getPosition().y + (shapeSprite.getGlobalBounds().height - monster.getGlobalBounds().height) / 2 < p)
		{
			monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 168 * 3, 120, 168));
			monster.move(0, -0.15);
		}
		if (shapeSprite.getPosition().x > k)
		{
			monster.move(0.25, 0);
			if (shapeSprite.getPosition().x - 100 > k)
			{
				monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 168 * 2,120, 168));
			}
		}
		else if (shapeSprite.getPosition().x < k)
		{
			monster.move(-0.25, 0);
			if (shapeSprite.getPosition().x + 100 < k) {
				monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 168, 120, 168));
			}
		}


		if (monster.getGlobalBounds().intersects(shapeSprite.getGlobalBounds())) {
			heart=0;
			
		}

		for (int i = 0; i < 4; i++) {
			if (monster.getGlobalBounds().intersects(bullet[i].bullet.getGlobalBounds())) {
				chk_1[i] = 0;
				bullet[i].bullet.setPosition(sf::Vector2f(-5000, -5000));
				blood--;
				break;
			}
		}
		if (blood <= 0) {
			chkwin = 4;
			x = rand() % 1500 + 200;
			y = rand() % 800 + 100;
			item1.setPosition(sf::Vector2f(x, y));
			score = score + 200;
			textscore.setString("SCORE : " + std::to_string(score));
			monster.setPosition(-5000, -5000);
			blood = -1;
		}
		
	}
};

Boss1 boss1;

class Boss2 {
public:
	int blood = -1;
	int animation = 0;
	sf::Sprite monster;
	int hit = 0;

	void set(int x, int y)
	{
		blood = 6;
		monster.setTexture(BOSS2);
		monster.setPosition(x, y);
	}

	void move()
	{
		animation++;
		int k = 0, p = 0;
		k = monster.getPosition().x;
		p = monster.getPosition().y;
		if (shapeSprite.getPosition().y + (shapeSprite.getGlobalBounds().height - monster.getGlobalBounds().height) / 2 > p)
		{
			monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 118, 0, 120, 168));
			monster.move(0, 0.15);
		}
		else if (shapeSprite.getPosition().y + (shapeSprite.getGlobalBounds().height - monster.getGlobalBounds().height) / 2 < p)
		{
			monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 118, 168 * 3, 120, 168));
			monster.move(0, -0.15);
		}
		if (shapeSprite.getPosition().x > k)
		{
			monster.move(0.25, 0);
			if (shapeSprite.getPosition().x - 100 > k)
			{
				monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 168 * 2, 115, 170));
			}
		}
		else if (shapeSprite.getPosition().x < k)
		{
			monster.move(-0.25, 0);
			if (shapeSprite.getPosition().x + 100 < k) {
				monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 168, 120, 163));
			}
		}


		if (monster.getGlobalBounds().intersects(shapeSprite.getGlobalBounds())) {
			heart = 0;

		}

		for (int i = 0; i < 4; i++) {
			if (monster.getGlobalBounds().intersects(bullet[i].bullet.getGlobalBounds())) {
				chk_1[i] = 0;
				bullet[i].bullet.setPosition(sf::Vector2f(-5000, -5000));
				blood--;
				break;
			}
		}
		if (blood <= 0) {
			chkwin=3;
			x = rand() % 1500 + 200;
			y = rand() % 800 + 100;
			item1.setPosition(sf::Vector2f(x, y));
			score = score + 300;
			textscore.setString("SCORE : " + std::to_string(score));
			monster.setPosition(-5000, -5000);
			blood = -1;
		}

	}
};

Boss2 boss2;

class Boss3 {
public:
	int blood = -1;
	int animation = 0;
	sf::Sprite monster;
	int hit = 0;

	void set(int x, int y)
	{
		blood = 7;
		monster.setTexture(BOSS3);
		monster.setPosition(x, y);
	}

	void move()
	{
		animation++;
		int k = 0, p = 0;
		k = monster.getPosition().x;
		p = monster.getPosition().y;
		if (shapeSprite.getPosition().y + (shapeSprite.getGlobalBounds().height - monster.getGlobalBounds().height) / 2 > p)
		{
			monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 0, 120, 168));
			monster.move(0, 0.15);
		}
		else if (shapeSprite.getPosition().y + (shapeSprite.getGlobalBounds().height - monster.getGlobalBounds().height) / 2 < p)
		{
			monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 168 * 3, 120, 168));
			monster.move(0, -0.15);
		}
		if (shapeSprite.getPosition().x > k)
		{
			monster.move(0.25, 0);
			if (shapeSprite.getPosition().x - 100 > k)
			{
				monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 168 * 2, 120, 168));
			}
		}
		else if (shapeSprite.getPosition().x < k)
		{
			monster.move(-0.25, 0);
			if (shapeSprite.getPosition().x + 100 < k) {
				monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 168, 120, 168));
			}
		}


		if (monster.getGlobalBounds().intersects(shapeSprite.getGlobalBounds())) {
			heart = 0;

		}

		for (int i = 0; i < 4; i++) {
			if (monster.getGlobalBounds().intersects(bullet[i].bullet.getGlobalBounds())) {
				chk_1[i] = 0;
				bullet[i].bullet.setPosition(sf::Vector2f(-5000, -5000));
				blood--;
				break;
			}
		}
		if (blood <= 0) {
			chkwin=2;
			x = rand() % 1500 + 200;
			y = rand() % 800 + 100;
			item1.setPosition(sf::Vector2f(x, y));
			score = score + 400;
			textscore.setString("SCORE : " + std::to_string(score));
			monster.setPosition(-5000, -5000);
			blood = -1;
		}

	}
};

Boss3 boss3;

class Boss4 {
public:
	int blood = -1;
	int animation = 0;
	sf::Sprite monster;
	int hit = 0;

	void set(int x, int y)
	{
		blood = 8;
		monster.setTexture(BOSS4);
		monster.setPosition(x, y);
	}

	void move()
	{
		animation++;
		int k = 0, p = 0;
		k = monster.getPosition().x;
		p = monster.getPosition().y;
		if (shapeSprite.getPosition().y + (shapeSprite.getGlobalBounds().height - monster.getGlobalBounds().height) / 2 > p)
		{
			monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 118, 0, 120, 168));
			monster.move(0, 0.15);
		}
		else if (shapeSprite.getPosition().y + (shapeSprite.getGlobalBounds().height - monster.getGlobalBounds().height) / 2 < p)
		{
			monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 118, 168 * 3, 120, 168));
			monster.move(0, -0.15);
		}
		if (shapeSprite.getPosition().x > k)
		{
			monster.move(0.25, 0);
			if (shapeSprite.getPosition().x - 100 > k)
			{
				monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 168 * 2, 120, 168));
			}
		}
		else if (shapeSprite.getPosition().x < k)
		{
			monster.move(-0.25, 0);
			if (shapeSprite.getPosition().x + 100 < k) {
				monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 168, 120, 168));
			}
		}


		if (monster.getGlobalBounds().intersects(shapeSprite.getGlobalBounds())) {
			heart = 0;

		}

		for (int i = 0; i < 4; i++) {
			if (monster.getGlobalBounds().intersects(bullet[i].bullet.getGlobalBounds())) {
				chk_1[i] = 0;
				bullet[i].bullet.setPosition(sf::Vector2f(-5000, -5000));
				blood--;
				break;
			}
		}
		if (blood <= 0) {
			chkwin=1;
			x = rand() % 1500 + 200;
			y = rand() % 800 + 100;
			item1.setPosition(sf::Vector2f(x, y));
			score = score + 500;
			textscore.setString("SCORE : " + std::to_string(score));
			monster.setPosition(-5000, -5000);
			blood = -1;
		}

	}
};

Boss4 boss4;

class Boss5 {
public:
	int blood = -1;
	int animation = 0;
	sf::Sprite monster;
	int hit = 0;

	void set(int x, int y)
	{
		blood = 8;
		monster.setTexture(BOSS5);
		monster.setPosition(x, y);
	}

	void move()
	{
		animation++;
		int k = 0, p = 0;
		k = monster.getPosition().x;
		p = monster.getPosition().y;
		if (shapeSprite.getPosition().y + (shapeSprite.getGlobalBounds().height - monster.getGlobalBounds().height) / 2 > p)
		{
			monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 0, 120, 168));
			monster.move(0, 0.15);
		}
		else if (shapeSprite.getPosition().y + (shapeSprite.getGlobalBounds().height - monster.getGlobalBounds().height) / 2 < p)
		{
			monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 168 * 3, 120, 168));
			monster.move(0, -0.15);
		}
		if (shapeSprite.getPosition().x > k)
		{
			monster.move(0.25, 0);
			if (shapeSprite.getPosition().x - 100 > k)
			{
				monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 168 * 2, 120, 168));
			}
		}
		else if (shapeSprite.getPosition().x < k)
		{
			monster.move(-0.25, 0);
			if (shapeSprite.getPosition().x + 100 < k) {
				monster.setTextureRect(sf::IntRect(((animation / 50) % 4) * 120, 168, 120, 168));
			}
		}


		if (monster.getGlobalBounds().intersects(shapeSprite.getGlobalBounds())) {
			heart = 0;

		}

		for (int i = 0; i < 4; i++) {
			if (monster.getGlobalBounds().intersects(bullet[i].bullet.getGlobalBounds())) {
				chk_1[i] = 0;
				bullet[i].bullet.setPosition(sf::Vector2f(-5000, -5000));
				blood--;
				break;
			}
		}
		if (blood <= 0) {
			chkwin=0;
			x = rand() % 1500 + 200;
			y = rand() % 800 + 100;
			item1.setPosition(sf::Vector2f(x, y));
			score = score + 1000;
			textscore.setString("SCORE : " + std::to_string(score));
			monster.setPosition(-5000, -5000);
			blood = -1;
		}

	}
};

Boss5 boss5;

int main()
{
	sf::Clock clock, clock2, clock3;
	sf::RenderWindow window(sf::VideoMode(1920, 1001), "MENU MODE", sf::Style::Close | sf::Style::Resize);
	Menu menu(window.getSize().x, window.getSize().y);
	lederboard Lederboard(window.getSize().x, window.getSize().y);
	gameover Gameover(window.getSize().x, window.getSize().y);
	win Win(window.getSize().x, window.getSize().y);


	sf::Texture texture;
	texture.loadFromFile("imgSFMLgaMe/BGMU1.JPG");
	sf::Sprite backgroundmenu;
	backgroundmenu.setTexture(texture);

	sf::Texture texture1;
	texture1.loadFromFile("imgSFMLgaMe/BGend.PNG");
	sf::Sprite backgroundgo;
	backgroundgo.setTexture(texture1);

	sf::Texture texture2;
	texture2.loadFromFile("imgSFMLgaMe/BGwin2.JPG");
	sf::Sprite backgroundwin;
	backgroundwin.setTexture(texture2);

	sf::Texture texture3;
	texture3.loadFromFile("imgSFMLgaMe/BGNAME.PNG");
	sf::Sprite backgroundname;
	backgroundname.setTexture(texture3);

	sf::Texture texture4;
	texture4.loadFromFile("imgSFMLgaMe/BGL.JPG");
	sf::Sprite backgroundleaderborad;
	backgroundleaderborad.setTexture(texture4);
	
	font.loadFromFile("Pure Joy.ttf");

	//sound
	sf::SoundBuffer soundeffect1;
	soundeffect1.loadFromFile("sound/shotsound.WAV");
	sf::Sound soundshot;
	soundshot.setBuffer(soundeffect1);
	sf::SoundBuffer soundeffect2;
	soundeffect2.loadFromFile("sound/bossApear.WAV");
	sf::Sound soundboss;
	soundboss.setBuffer(soundeffect2);
	sf::SoundBuffer soundeffect3;
	soundeffect3.loadFromFile("sound/gameover.WAV");
	sf::Sound soundover;
	soundover.setBuffer(soundeffect3);
	sf::SoundBuffer soundeffect4;
	soundeffect4.loadFromFile("sound/item.WAV");
	sf::Sound sounditem;
	sounditem.setBuffer(soundeffect4);
	sf::SoundBuffer soundeffect5;
	soundeffect5.loadFromFile("sound/getdamage.WAV");
	sf::Sound damage;
	damage.setBuffer(soundeffect5);
	sf::SoundBuffer soundeffect6;
	soundeffect6 .loadFromFile("sound/congrat.WAV");
	sf::Sound soundcon;
	soundcon.setBuffer(soundeffect6);

	//name 
	sf::Text name;
	name.setFont(font);
	name.setString("Name : ");
	name.setFillColor(sf::Color::Black);
	name.setPosition(200, 300);
	name.setCharacterSize(80);
	sf::String nameplayer;

	//score
	textscore.setFont(font);
	textscore.setString("SCORE : ");
	textscore.setFillColor(sf::Color::Black);
	textscore.setPosition(40, 0);
	textscore.setCharacterSize(40);

	//high score
	HighScoreText.setFont(font);
	HighScoreText.setFillColor(sf::Color::Black);
	HighScoreText.setCharacterSize(50);
	HighScoreText.setPosition(300, 300);

	hscore.setFont(font);
	hscore.setCharacterSize(40);
	hscore.setFillColor(sf::Color::Black);
	hname.setFont(font);
	hname.setCharacterSize(40);
	hname.setFillColor(sf::Color::Black);


	//scoreborad
	sf::RectangleShape board;
	board.setSize(sf::Vector2f(700, 500));
	board.setFillColor(sf::Color::Black);
	board.setPosition(500, 450);
	board.setOrigin(board.getGlobalBounds().width / 2, board.getGlobalBounds().height / 2);

	sf::Text scoreboard;
	scoreboard.setFont(font);
	scoreboard.setString("SCOREBOARD");
	scoreboard.setFillColor(sf::Color::Black);
	scoreboard.setCharacterSize(50);
	scoreboard.setPosition(380, 200);

	//back
	sf::Text back;
	back.setFont(font);
	back.setString("back");
	back.setFillColor(sf::Color::Black);
	back.setPosition(120, 580);
	back.setCharacterSize(40);

	std::vector<std::pair<int, std::string>> ScoreBoard;




//GAME
strgame:
	for (int i = 0; i < 6; i++) {
		bullet[i].setfrist();
	}
	if (startgame == 1) {
	
		srand(time(NULL));
		sf::RenderWindow window(sf::VideoMode(1920, 1001), "SFML works!", sf::Style::Close | sf::Style::Resize);

		j = heart;

		playerTexture.loadFromFile("imgSFMLgaMe/sprite1.png");
		BackgroundTexture.loadFromFile("imgSFMLgaMe/BGmap1.png");
		HEART.loadFromFile("imgSFMLgaMe/heartg.png");
		
		BOSS.loadFromFile("imgSFMLgaMe/boss1.png");
		BOSS2.loadFromFile("imgSFMLgaMe/boss2.png");
		BOSS3.loadFromFile("imgSFMLgaMe/boss3.png");
		BOSS4.loadFromFile("imgSFMLgaMe/boss4.png");
		BOSS5.loadFromFile("imgSFMLgaMe/boss5.png");

		ITEM1.loadFromFile("imgSFMLgaMe/heartitem2.png");
		ITEM.loadFromFile("imgSFMLgaMe/extrabullet.png");

		//monster
		monsterTexture.loadFromFile("imgSFMLgaMe/monster1.png");

		//BG
		background.setTexture(BackgroundTexture);

		// Sprite
		shapeSprite.setTexture(playerTexture);
		shapeSprite.setTextureRect(sf::IntRect(0 * 90, -10, 90, 121));
		shapeSprite.setPosition(spawnPoint);

		//item
		item.setTexture(ITEM);
		item.setTextureRect(sf::IntRect(0, 0, 60, 60));
		item.setPosition(sf::Vector2f(-500, -500));

		//item1
		item1.setTexture(ITEM1);
		item1.setTextureRect(sf::IntRect(0, 0, 50, 50));
		item1.setPosition(sf::Vector2f(-500, -500));

		//heart
		heart1.setPosition(sf::Vector2f(1800, 30));
		heart1.setTexture(HEART);
		heart1.setTextureRect(sf::IntRect(0, 0, 70, 70));
		heart2.setPosition(sf::Vector2f(1750, 30));
		heart2.setTexture(HEART);
		heart2.setTextureRect(sf::IntRect(0, 0, 70, 70));
		heart3.setPosition(sf::Vector2f(1700, 30));
		heart3.setTexture(HEART);
		heart3.setTextureRect(sf::IntRect(0, 0, 70, 70));
		
		//Score
		score1.setFont(font);
		score1.setCharacterSize(70);
		score1.setFillColor(sf::Color::Red);
		score1.setPosition(sf::Vector2f(800, 30));


		//Monnster
		for (int i = 0; i < 4; i++) {
			if (rand() % 2 == 0) {
				monster[i].set(-30, rand() % 1001);
			}
			else {
				monster[i].set(1900, rand() % 1001);
			}
		}


		while (window.isOpen())
		{


			if (chkwin == 0) {
				//write files
				std::string name;
				name = nameplayer;
				std::ofstream highscore;
				highscore.open("score/Score.txt", std::ios::out | std::ios::app);
				highscore << "\n" << name << " " << score;
				highscore.close();

				//read files
				ScoreBoard.clear();

				std::ifstream loadFile;
				loadFile.open("score/Score.txt");
				while (!loadFile.eof()) {
					std::string tempName;
					int tempScore;
					loadFile >> tempName >> tempScore;
					std::cout << tempName << " " << tempScore << std::endl;
					ScoreBoard.push_back({ tempScore,tempName });
				}
				loadFile.close();

				std::sort(ScoreBoard.begin(), ScoreBoard.end(), std::greater<std::pair< int, std::string>>());
				std::cout << ScoreBoard.data();
				std::vector<std::pair<int, std::string >>::iterator k = ScoreBoard.begin();
				HighScoreText.setString("HIGH SCORE : " + std::to_string(k->first));


				Beep(100, 2000);
				startgame = 4;
				window.close();
				goto strgame;
			}

			//dead
			if (heart == 0 || heart < 0) {

				
				//write files
				std::string name;
			    name = nameplayer;
				std::ofstream highscore;
				highscore.open("score/Score.txt", std::ios::out | std::ios::app);
				highscore << "\n" << name << " " << score;
				highscore.close();

				//read files
				ScoreBoard.clear();

				std::ifstream loadFile;
				loadFile.open("score/Score.txt");
				while (!loadFile.eof()) {
					std::string tempName;
					int tempScore;
					loadFile >> tempName >> tempScore;
					std::cout << tempName << " " << tempScore << std::endl;
					ScoreBoard.push_back({ tempScore,tempName });
				}
				loadFile.close();

				std::sort(ScoreBoard.begin(), ScoreBoard.end(), std::greater<std::pair< int, std::string>>());
				std::cout << ScoreBoard.data();
				std::vector<std::pair<int, std::string >>::iterator k = ScoreBoard.begin();
				HighScoreText.setString("HIGH SCORE : " + std::to_string(k->first));
				dead = 1;
			}
			if (dead == 1) {
				startgame = 3;
				goto strgame;
				window.close();
			}

			window.draw(background);
			if (heart > 0) {
				window.draw(heart1);
				
				if (heart > 1) {
					window.draw(heart2);
					if (heart > 2) {
						window.draw(heart3);
					}
				}
			}

			if (numb%10==0 && itemchk==0 && numb>0) {
				itemchk = 1;
				x = rand() % 1500+200;
				y = rand() % 800+100;
				item.setPosition(sf::Vector2f(x, y));
			}
			if (numb % 10 != 0)itemchk = 0;


			//boss1 
			if (numb==20 && boss1.blood<0) {
				soundboss.play();
				if (rand() % 2 == 0) {
					boss1.set(-30, rand() % 1001);
				}
				else {
					boss1.set(1900, rand() % 1001);
				}
			}

			//boss2
			if (numb == 10 && boss2.blood < 0) {
				soundboss.play();
				if (rand() % 2 == 0) {
					boss2.set(-30, rand() % 1001);
				}
				else {
					boss2.set(1900, rand() % 1001);
				}
			}

			//boss3
			if (numb == 38 && boss3.blood < 0) {
				soundboss.play();
				if (rand() % 2 == 0) {
					boss3.set(-30, rand() % 1001);
				}
				else {
					boss3.set(1900, rand() % 1001);
				}
			}

			//boss4
			if (numb == 45 && boss4.blood < 0) {
				soundboss.play();
				if (rand() % 2 == 0) {
					boss4.set(-30, rand() % 1001);
				}
				else {
					boss4.set(1900, rand() % 1001);
				}
			}

			//boss5
			if (numb == 53 && boss5.blood < 0) {
				soundboss.play();
				if (rand() % 2 == 0) {
					boss5.set(-30, rand() % 1001);
				}
				else {
					boss5.set(1900, rand() % 1001);
				}
			}


			getitem();
			getitem1();
			Control();
			shot();
		
			window.draw(shapeSprite);

			for (int i = 0; i < 6; i++) {
				if (chk_1[i] == 1) {
					window.draw(bullet[i].bullet);
				}
			}
			for (int i = 0; i < 4; i++) {
				monster[i].move();
			}

			//drawboss1
			if (boss1.blood >= 0) {
				boss1.move();
				window.draw(boss1.monster);
			}

			//drawboss2
			if (boss2.blood >= 0) {
				boss2.move();
				window.draw(boss2.monster);
			}

			//drawboss3
			if (boss3.blood >= 0) {
				boss3.move();
				window.draw(boss3.monster);
			}

			//drawboss4
			if (boss4.blood >= 0) {
				boss4.move();
				window.draw(boss4.monster);
			}

			//drawboss5
			if (boss5.blood >= 0) {
				boss5.move();
				window.draw(boss5.monster);
			}

			for (int i = 0; i < 4; i++) {
				window.draw(monster[i].monster);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				for (int i = 0; i < 6; i++) {
					soundshot.play();
				}
			}

			if (shapeSprite.getGlobalBounds().intersects(item1.getGlobalBounds())) {
				sounditem.play();
				
			}


			if (shapeSprite.getGlobalBounds().intersects(item.getGlobalBounds())) {
				sounditem.play();

			}


			if (shapeSprite.getGlobalBounds().intersects(monster->monster.getGlobalBounds())) {
				
				damage.play();

			}
			if (j != heart) {
				damage.play();
				j = heart;
			}

			window.draw(item1);
			window.draw(item);
			showscore();
			window.draw(score1);
			
			window.display();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}
	}


strgame1:
//LEDERBOARD
	if (startgame == 2) {
		sf::RenderWindow window(sf::VideoMode(1920, 1001), "LEDERBOARD", sf::Style::Close | sf::Style::Resize);


		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{

				case sf::Event::Closed:
					window.close();
					break;
				}
			}
			ScoreBoard.clear();

			std::ifstream loadFile;
			loadFile.open("score/Score.txt");
			while (!loadFile.eof())
			{
				std::string tempName;
				int tempScore;
				loadFile >> tempName >> tempScore;
				ScoreBoard.push_back({ tempScore,tempName });
			}
				loadFile.close();

				sort(ScoreBoard.begin(), ScoreBoard.end(), std::greater<std::pair< int, std::string>>());

				window.draw(backgroundleaderborad);
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
				}
			

			cnt = 0;
			for (std::vector<std::pair<int, std::string>>::iterator k = ScoreBoard.begin(); k != ScoreBoard.end(); ++k)
			{
				++cnt;
				if (cnt > 5)
					break;
				std::cout << cnt << std::endl;
				hscore.setPosition(300, 250 + (50 * cnt));
				hname.setPosition(600, 250 + (50 * cnt));
				hscore.setString(std::to_string(k->first));
				hname.setString(k->second);
				window.draw(hscore);
				window.draw(hname);
			}
			
			window.draw(scoreboard);
			window.display();
		}
	
		
	}

//WIN
	if (startgame == 4) {
		sf::RenderWindow window(sf::VideoMode(1920, 1001), "WIN", sf::Style::Close | sf::Style::Resize);
		soundcon.play() ;

		score3.setFont(font);
		score3.setCharacterSize(200);
		score3.setFillColor(sf::Color::Red);
		score3.setPosition(sf::Vector2f(300, 50));

		
		sprintf(scorechar, "YOU WINN!!!!                 %d", score);
		score3.setString(scorechar);


		

		while (window.isOpen())
		{
			

			window.draw(backgroundwin);
			window.draw(score3);
			Win.draw(window);
			window.display();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				window.close();
			}
		}
	}

//NAME
	if (startgame == 5) {
		sf::RenderWindow window(sf::VideoMode(1920, 1001), "NAME", sf::Style::Close | sf::Style::Resize);
		while (window.isOpen())
		{

			deltatime = clock.restart().asSeconds();

			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{

				case sf::Event::Closed:
					window.close();
					break;
				}
			}
			window.draw(backgroundname);




			if (event.type == sf::Event::TextEntered and debounce < clock2.getElapsedTime().asSeconds())
			{

				debounce = clock2.getElapsedTime().asSeconds() + 0.2;
				if (event.text.unicode >= 33 && event.text.unicode <= 126 && nameplayer.getSize() <= 13 && event.text.unicode != 44)
				{
					nameplayer += event.text.unicode;
				}
				else if (event.text.unicode == 8)//backspace
				{
					nameplayer = nameplayer.substring(0, nameplayer.getSize() - 1);
				}
				else if (event.text.unicode == 13 && nameplayer.getSize() > 0)//enter
				{
					startgame = 1;
					printf("play");
					window.close();
					goto strgame;
					break;
				}
			}


			name.setString("Name : " + nameplayer);

			window.draw(name);
			window.display();
		}
		
	}

//MENU
	if(startgame == 0){
		sf::RenderWindow window(sf::VideoMode(1920, 1001), "MENU", sf::Style::Close | sf::Style::Resize);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::TextEntered:
					
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						menu.MoveUp();
						break;
					case sf::Keyboard::Down:
						menu.MoveDown();
						break;
					case sf::Keyboard::Enter:
						switch (menu.GetpressedItem())
						{
						case 0 :
							startgame = 5;
							window.close();
							goto strgame;
							break;
						case 1:
							startgame = 2;
							window.close();
							goto strgame1;
							break;
						case 2:
							window.close();
							break;
						}
						break;
					}
					break;
				}
			}
		    window.draw(backgroundmenu);
			menu.draw(window);
			window.display();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}
	}

//GAMEOVER
	if (startgame == 3) {

		sf::RenderWindow window(sf::VideoMode(1920, 1001), "GAMEOVER", sf::Style::Close | sf::Style::Resize);

		soundover.play();


		while (window.isOpen())
		{

			window.draw(backgroundgo);

			Gameover.draw(window);

			window.display();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				window.close();
			}
		}
	}
	
	return 0;
}

void Control()
{
	animationFrame++;
	end = clock();
	float dif = (float)(end - start) / CLOCKS_PER_SEC;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (x >= 0) {
			pst = 1;
			shapeSprite.move(-0.5f, 0.0f);
			shapeSprite.setTextureRect(sf::IntRect(((animationFrame / 50) % 3) * 90, 125 * 3, 90, 121));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (y >= 110) {
			pst = 2;
			shapeSprite.move(0.0f, -0.5f);
			shapeSprite.setTextureRect(sf::IntRect(((animationFrame/50)%3)*90, -10, 90, 121));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (x <= 1850) {
			pst = 3;
			shapeSprite.move(0.5f, 0.0f);
			shapeSprite.setTextureRect(sf::IntRect(((animationFrame / 50) % 3) * 90, 121, 90, 121));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (y <= 851) {
			pst = 4;
			shapeSprite.move(0.0f, 0.5f);
			shapeSprite.setTextureRect(sf::IntRect(((animationFrame / 50) % 3) * 90, 121*2, 90, 121));
		}
	}
	x = shapeSprite.getPosition().x;
	y = shapeSprite.getPosition().y;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && dif > 0.5) {
		for (int i = 0; i < 6; i++) {
			if (chk_1[i] == 0)
			{
				if (pst == 1) {
					BULLET.loadFromFile("imgSFMLgaMe/bullet3.png");
					bullet[i].set(x, y + (shapeSprite.getGlobalBounds().height - bullet->bullet.getGlobalBounds().height) / 2);
					

				}
				if (pst == 2) {
					BULLET.loadFromFile("imgSFMLgaMe/bullet2.png");
					bullet[i].set(x , y);
					

				}
				if (pst == 3) {
					BULLET.loadFromFile("imgSFMLgaMe/bullet1.png");
					bullet[i].set(x , y + (shapeSprite.getGlobalBounds().height - bullet->bullet.getGlobalBounds().height) / 2);
					

				}
				if (pst == 4) {
					BULLET.loadFromFile("imgSFMLgaMe/bullet4.png");
					bullet[i].set(x , y );
					
				}
				pst1[i] = pst;
				chk_1[i] = 1;
				start = clock();
				break;
			}
		}

	}
}

void shot() {
	for (int i = 0; i < 6; i++) {
		if (chk_1[i] == 1) {
			float speed = 1.5;
			if (pst1[i] == 1) {
				bullet[i].bullet.move(-speed, 0);
			}
			if (pst1[i] == 2) {
				bullet[i].bullet.move(0, -speed);
			}
			if (pst1[i] == 3) {
				bullet[i].bullet.move(speed, 0);
			}
			if (pst1[i] == 4) {
				bullet[i].bullet.move(0, speed);
			}
			if (bullet[i].bullet.getPosition().x < -30 || bullet[i].bullet.getPosition().x>1920) {
				chk_1[i] = 0;
			}
			if (bullet[i].bullet.getPosition().y < -30 || bullet[i].bullet.getPosition().y>1001) {
				chk_1[i] = 0;
			}

		}

	}
}

void getitem() {
	if (shapeSprite.getGlobalBounds().intersects(item.getGlobalBounds())) {
		item.setPosition(-500, -500);
		itemshot = 1;
		score = score + 50;
	}
}

void showscore() {
	
	sprintf(scorechar, "SCORE   %d", score);
	score1.setString(scorechar);
}

void getitem1() {
	if (shapeSprite.getGlobalBounds().intersects(item1.getGlobalBounds())) {
		item1.setPosition(-500, -500);
		heart++;
		if (heart >= 3) {
			heart = 3;
		}
		score = score + 50;
	}
}