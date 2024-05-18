#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Luffy.h"


class Alveda
{
private:
	sf::RectangleShape AlvedaBody;
	Animation animation;
	unsigned int rowNumber;
	float alvedaSpeed;
	bool alvedaFacingRight;
public:
	Alveda(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, float alvedaSpeed, float w, float h) ;
	void update(float deltaTime, const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	sf::RectangleShape getalvedaBody();
	void changeAnimation(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, unsigned int row);
	bool isNearLuffy(Luffy& luffy,float d);
};