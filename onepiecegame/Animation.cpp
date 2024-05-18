#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, int rowNumber)
{
	this->rowNumber = rowNumber;
	this->totalImages = totalImages;
	this->switchingTime = switchingTime;
	// Initialisation du temps �coul� � z�ro
	elapsedTime = 0.0f;
	// Initialisation de la position de l'image courante sur l'axe horizontal � 0
	currentImagePosition.x = 0;
	// Calcul de la largeur et de la hauteur de chaque image dans la texture
	uvRect.width = texture->getSize().x / float(totalImages.x);
	uvRect.height = texture->getSize().y / float(totalImages.y);
}

void Animation::update(int rowNumber, float deltaTime, bool playerFacingRight)
{
	// D�finition du num�ro de ligne de l'image courante dans la texture
	currentImagePosition.y = rowNumber;
	// Ajout du temps �coul� depuis la derni�re mise � jour
	elapsedTime += deltaTime;
	if (elapsedTime >= switchingTime)
	{
		// R�initialisation du temps �coul�
		elapsedTime -= switchingTime;
		// Passage � l'image suivante sur l'axe horizontal
		currentImagePosition.x++;
		// V�rification si la derni�re image de la ligne a �t� atteinte
		if (currentImagePosition.x >= totalImages.x)
		{
			// Retour � la premi�re image de la ligne
			currentImagePosition.x = 0;
		}
	}
	// D�finition de la position verticale du rectangle d'encadrement dans la texture
		uvRect.top = currentImagePosition.y * uvRect.height;
	// V�rification de la direction du joueur
		if (playerFacingRight)
		{
			// Si le joueur regarde vers la droite, la position horizontale est d�finie directement
				uvRect.left = currentImagePosition.x * uvRect.width;
			uvRect.width = abs(uvRect.width);
		}
		else
		{
			// Si le joueur regarde vers la gauche, la position horizontale est invers�e
			uvRect.left = (currentImagePosition.x + 1) * abs(uvRect.width);
			uvRect.width = -abs(uvRect.width);
		}
		

}
void Animation::changeTexture(sf::Texture* newTexture, sf::Vector2u newTotalImages, float newSwitchingTime, unsigned int newRow)
{
	texture = newTexture;
	totalImages = newTotalImages;
	switchingTime = newSwitchingTime;
	rowNumber = newRow;
	// R�initialisation du temps �coul� � z�ro
	elapsedTime = 0.0f;
	// R�initialisation de la position de l'image courante sur l'axe horizontal � 0
	currentImagePosition.x = 0;
	// Calcul de la largeur et de la hauteur de chaque image dans la nouvelle texture
	uvRect.width = newTexture->getSize().x / float(newTotalImages.x);
	uvRect.height = newTexture->getSize().y / float(newTotalImages.y);
}