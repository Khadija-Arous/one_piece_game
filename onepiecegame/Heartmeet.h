#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include "Luffy.h"


class Heartmeet
{
private:

	sf::RectangleShape meet;
	//Animation animation;
	unsigned int rowNumber;
	bool heartFacingRight ;
	sf::Sprite hearts;
	bool heartmoved = false;
	
	
public:
    Heartmeet();
	Heartmeet(sf::Texture* texture, float w, float h);
	//void update(float deltaTime, const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	sf::RectangleShape getmeetbody();
	void moveheart(float w, float h);
	bool ismoved();
	
};