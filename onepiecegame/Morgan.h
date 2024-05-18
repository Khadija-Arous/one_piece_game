#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Luffy.h"


class Morgan
{
private:
	sf::RectangleShape morganBody;
	Animation animation;
	unsigned int rowNumber;
	float morganSpeed;
	bool morganFacingRight;
public:
	Morgan(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, float morganSpeed, float w, float h);
	void update(float deltaTime, const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	sf::RectangleShape getmorganBody();
	void changeAnimation(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, unsigned int row);
	bool isNearLuffy(Luffy& luffy,float d) ;
};