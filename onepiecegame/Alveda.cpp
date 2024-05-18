#include "Alveda.h"
Alveda::Alveda(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, float alvedaSpeed, float w, float h) : animation(texture, totalImages, switchingTime,rowNumber), alvedaSpeed(alvedaSpeed)
	{
		rowNumber = 0;
		alvedaFacingRight = true;
		AlvedaBody.setSize(sf::Vector2f(350.0f, 300.0f));
		AlvedaBody.setPosition(w, h);
		AlvedaBody.setTexture(texture);
	}
void Alveda::update(float deltaTime, const sf::RenderWindow& window)
	{

		sf::Vector2f movement(0.0f, 0.0f);
	
		if (alvedaFacingRight)
		{
				if (AlvedaBody.getPosition().x + AlvedaBody.getSize().x < window.getSize().x)
				{
					movement.x = -alvedaSpeed * deltaTime;

				}
				else
				{
					alvedaFacingRight = false;  // Change direction to left
				}
		}
		else
		{
				if (AlvedaBody.getPosition().x > 0)
				{
					movement.x = +alvedaSpeed * deltaTime;

				}
				else
				{
					alvedaFacingRight = true; // Change direction to right
				}
		}

		
		
		// Met à jour l'animation en fonction du mouvement et de la direction
		animation.update(rowNumber, deltaTime, alvedaFacingRight);
		// Déplace le corps du joueur
		AlvedaBody.setTextureRect(animation.uvRect);
		AlvedaBody.move(movement);


	}
void Alveda::draw(sf::RenderWindow& window)
	{
		window.draw(AlvedaBody);
	}

sf::RectangleShape Alveda::getalvedaBody() {
	return AlvedaBody;
}
void Alveda::changeAnimation(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, unsigned int row)
{
	animation.changeTexture(texture, totalImages, switchingTime, row);
}
bool Alveda::isNearLuffy(Luffy& luffy, float d)
{
	// Get the positions of Morgan and Luffy bodies
	sf::Vector2f alvedaPosition = AlvedaBody.getPosition();
	sf::Vector2f luffyPosition = luffy.getLuffyBody().getPosition();

	// Calculate the distance between Morgan and Luffy
	float distance = std::sqrt(std::pow(alvedaPosition.x - luffyPosition.x, 2) + std::pow(alvedaPosition.y - luffyPosition.y, 2));

	// Return true if the distance is less than or equal to 10 pixels
	return distance <= d;
}