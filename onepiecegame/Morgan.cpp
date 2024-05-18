#include "Morgan.h"
Morgan::Morgan(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, float morganSpeed, float w, float h) : animation(texture, totalImages, switchingTime, rowNumber), morganSpeed(morganSpeed)
{
	rowNumber = 0;
	morganFacingRight = true;
	morganBody.setSize(sf::Vector2f(220.0f, 300.0f));
	morganBody.setPosition(w, h);
	morganBody.setTexture(texture);
}
void Morgan::update(float deltaTime, const sf::RenderWindow& window)
{

	sf::Vector2f movement(0.0f, 0.0f);

	if (morganFacingRight)
	{
		if (morganBody.getPosition().x + morganBody.getSize().x < window.getSize().x)
		{
			movement.x = -morganSpeed * deltaTime;

		}
		else
		{
			morganFacingRight = false;  // Change direction to left
		}
	}
	else
	{
		if (morganBody.getPosition().x > 0)
		{
			movement.x = +morganSpeed * deltaTime;

		}
		else
		{
			morganFacingRight = true; // Change direction to right
		}
	}



	// Met à jour l'animation en fonction du mouvement et de la direction
	animation.update(rowNumber, deltaTime, morganFacingRight);
	// Déplace le corps du joueur
	morganBody.setTextureRect(animation.uvRect);
	morganBody.move(movement);


}
void Morgan::draw(sf::RenderWindow& window)
{
	window.draw(morganBody);
}

sf::RectangleShape Morgan::getmorganBody() {
	return morganBody;
}
void Morgan::changeAnimation(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, unsigned int row)
{
	animation.changeTexture(texture, totalImages, switchingTime, row);
}
bool Morgan::isNearLuffy(Luffy& luffy,float d)
{
	// Get the positions of Morgan and Luffy bodies
	sf::Vector2f morganPosition = morganBody.getPosition();
	sf::Vector2f luffyPosition = luffy.getLuffyBody().getPosition();

	// Calculate the distance between Morgan and Luffy
	float distance = std::sqrt(std::pow(morganPosition.x - luffyPosition.x, 2) + std::pow(morganPosition.y - luffyPosition.y, 2));

	// Return true if the distance is less than or equal to 10 pixels
	return distance <= d;
}