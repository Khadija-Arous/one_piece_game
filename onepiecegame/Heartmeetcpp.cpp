#include "Heartmeet.h"

#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

Heartmeet::Heartmeet()
{

};
Heartmeet::Heartmeet(sf::Texture* texture, float w, float h) 
	{

		this->rowNumber = rowNumber;
    	this->heartFacingRight = heartFacingRight;
		heartFacingRight = true;
		
		meet.setSize(sf::Vector2f(100.0f, 100.0f));
		meet.setPosition(w, h);
		meet.setTexture(texture);
		
		sf::Sprite hearts(*texture);
		

	}

void Heartmeet::draw(sf::RenderWindow& window)
{
	
		window.draw(hearts);
		window.draw(meet);
	
}
sf::RectangleShape Heartmeet::getmeetbody()
{
	return meet;
}
void Heartmeet::moveheart(float w,float h)
{
	meet.move(sf::Vector2f(w, h));
	heartmoved = true;
}
bool Heartmeet::ismoved()
{
	return heartmoved;
}