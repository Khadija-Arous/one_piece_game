#pragma once
#pragma once
#include <iostream>
#include <SFML/Audio.hpp>>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include "Animation.h"
#include "Luffy.h"
#include "Heartmeet.h"

class Knife
{
private:
	int numk;//3


	std::vector<sf::Sprite> knives;
	////knifes

	int knifeSpeed;//5
	int k_width;//20
	int k_height;///40
	/// tebe3 lanimation

	Animation animation;
	bool knifeFacingRight;
	unsigned int rowNumber;
	sf::RectangleShape knifeBody;

public:
	Knife(sf::Texture* KnifeTexture, sf::Vector2u totalImages, float switchingTime, unsigned windowWidth, unsigned windowHeight, float k_width, float k_height, int numk, int knifeSpeed);
	void move_knifes(sf::RenderWindow& window, unsigned windowWidth, unsigned windowHeight, float k_width, float k_height, int knifeSpeed);
	void draw(sf::RenderWindow& window);
	void update(float deltaTime, const sf::RenderWindow& window);
	std::vector<sf::Sprite> getknives();
	sf::RectangleShape getknifeBody();
	void checkCollisionAndErase(Luffy& luffy, Heartmeet& heart1, sf::Music& m);
};