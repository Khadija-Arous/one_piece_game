#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"

class Bagi
{

	
private:
	
	sf::RectangleShape BagiBody;
	Animation animation;
	unsigned int rowNumber;
	float bagiSpeed;
	bool bagiFacingRight;
public:
	Bagi(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, float BagiSpeed, float w, float h);
	void update(float deltaTime, const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void bagi_moveleft(sf::Vector2f newPosition, const sf::RenderWindow& window, float deltaTime, sf::Vector2f movement);
	void bagi_moveright(sf::Vector2f newPosition, const sf::RenderWindow& window, float deltaTime, sf::Vector2f movement);
	sf::RectangleShape getBagiBody();
	void changeAnimation(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, unsigned int row);
};
