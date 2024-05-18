#pragma once
#include<SFML/Graphics.hpp>
// Définition de la classe Animation
class Animation
{
private:
	// Temps total écoulé depuis le début de l'animation
	float elapsedTime;
	// Temps nécessaire pour passer à l'image suivante dans l'animation
	float switchingTime;
	// Nombre total d'images dans la texture (en lignes : 1, colonnes : 10)
	sf::Vector2u totalImages;
	// Position de l'image courante dans la texture (ligne, colonne)
	sf::Vector2u currentImagePosition;
	/// 
	sf::Texture* texture;
	int rowNumber;


public:
	// Rectangle d'encadrement dans la texture pour afficher l'image courante
	sf::IntRect uvRect;
	// Paramètres : la texture de l'animation, le nombre d'images dans la texture et le temps de changement d'image
		Animation(sf::Texture * texture, sf::Vector2u totalImages, float switchingTime,int rowNumber);
	// Méthode pour mettre à jour l'animation
	// Paramètres : le numéro de ligne dans la texture, le temps écoulé depuis la dernière mise à jour et la direction de l'animation
		// Dans notre cas nous n'avons qu'une seule ligne
		void update(int rowNumber, float deltaTime, bool playerFacingRight);
	
		void changeTexture(sf::Texture* newTexture, sf::Vector2u newTotalImages, float newSwitchingTime,unsigned int newrow);

}; 