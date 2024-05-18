
#include "Bagi.h"

Bagi::Bagi(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, float bagiSpeed, float w, float h) :
	animation(texture, totalImages, switchingTime, rowNumber), bagiSpeed(bagiSpeed)
{
	rowNumber = 0;
	bagiFacingRight = true;
	BagiBody.setSize(sf::Vector2f(214.0f, 200.0f));
	BagiBody.setPosition(w , h);  // Start from the right end
	BagiBody.setTexture(texture);
}

void Bagi::update(float deltaTime, const sf::RenderWindow& window)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (bagiFacingRight)
	{
		if (BagiBody.getPosition().x + BagiBody.getSize().x < window.getSize().x)
		{
			movement.x = bagiSpeed * deltaTime;
			
		}
		else
		{
			bagiFacingRight = false;  // Change direction to left
		}
	}
	else
	{
		if (BagiBody.getPosition().x > 0)
		{
			movement.x = -bagiSpeed * deltaTime;
			
		}
		else
		{
			bagiFacingRight = true; // Change direction to right
		}
	}

	// Update the animation based on the movement and direction
	animation.update(rowNumber, deltaTime, bagiFacingRight);
	BagiBody.setTextureRect(animation.uvRect);
	BagiBody.move(movement);
}

void Bagi::draw(sf::RenderWindow& window)
{
	window.draw(BagiBody);
}

sf::RectangleShape Bagi::getBagiBody() {
	return BagiBody;
}
void Bagi::changeAnimation(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, unsigned int row)
{
	animation.changeTexture(texture, totalImages, switchingTime, row);
}