#include "Luffy.h"
#include "SFML/Audio.hpp"


Luffy::Luffy(sf::Texture * texture, sf::Vector2u totalImages, float switchingTime,float LuffySpeed, float jumpVelocity) : animation(texture, totalImages, switchingTime,rowNumber), LuffySpeed(LuffySpeed)
	{
		this->LuffySpeed = LuffySpeed;
		this->jumpVelocity = jumpVelocity;
		this->isJumping = false;
		// Initialisation du reste des membres...
	rowNumber = 0;
	LuffyFacingRight = true;
	LuffyBody.setSize(sf::Vector2f(220.0f, 250.0f));
	LuffyBody.setPosition(20.0f, 720.0f);
	LuffyBody.setTexture(texture);
	//--------------- Update : Variables liées au saut ------------------

	gravity = 0.5f; // Gravité affectant le joueur
	jumpStrength = -20.0f; // Vitesse de saut vers le haut
	verticalVelocity = 0.0f; // Vitesse verticale initiale
	groundLevel = 750.0f; // Niveau du sol
	isOnGround = true; // État initial au sol

	//----------------------------------------------------------------

	
}

// Fonction de mise à jour pour gérer le mouvement et l'animation du joueur
void Luffy::update(float deltaTime, const sf::RenderWindow& window)
{
	sf::Vector2f movement(0.0f, 0.0f); sf::Music run;
	
	// Vérifie les entrées du clavier pour le mouvement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		
		movement.x -= LuffySpeed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		
		movement.x += LuffySpeed * deltaTime;
	}
	////luffy up and down
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		movement.y -= LuffySpeed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		movement.y += LuffySpeed * deltaTime;*/

	
	// Logique de saut
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping)
	{
		
		// Démarre le saut en définissant la vélocité du saut
		isJumping = true;
		movement.y = -jumpVelocity; // Définir la vélocité initiale du saut
		// Change la ligne d'animation pour le saut
		rowNumber = 1;
		// Mettre à jour la texture rect du sprite pour l'animation de saut
		int jumpAnimationFrameWidth = 120; // Largeur de chaque image 
		LuffyBody.setTextureRect(sf::IntRect(0, 0, jumpAnimationFrameWidth, LuffyBody.getLocalBounds().height));
		
	}
	

		// Logique de saut
		if (isJumping)
		{
			// Ajuste la position en fonction de la vélocité du saut
			movement.y += jumpVelocity * deltaTime; // Appliquer la gravité

			// Met à jour la position verticale du personnage
			LuffyBody.move(0, movement.y * deltaTime);

			// Si le joueur atteint le sol (par exemple, la limite inférieure de la fenêtre),
			// arrête le saut
			if (LuffyBody.getPosition().y + LuffyBody.getLocalBounds().height >= window.getSize().y)
			{
				isJumping = false;
				// Réinitialise la vélocité verticale
				movement.y = 0.0f;
				// Remettez la ligne d'animation à celle de l'état normal
				rowNumber = 0;
				// Mettez à jour la texture rect du sprite pour l'animation normale
				animation.update(rowNumber, deltaTime, LuffyFacingRight);
				LuffyBody.setTextureRect(animation.uvRect);
				// Assurez-vous que le personnage est bien sur le sol
				LuffyBody.setPosition(LuffyBody.getPosition().x, window.getSize().y - LuffyBody.getLocalBounds().height);
			}
		}
	
	
	
	//LuffyFacingRight = (movement.x < 0.0f) ? true : false;
	if (movement.x == 0.0f)
		rowNumber = 0;
	else
	{
		rowNumber = 0;
		if (movement.x > 0.0f)
			LuffyFacingRight = true;
		else
			LuffyFacingRight = false;
	}


	// Met à jour l'animation en fonction du mouvement et de la direction
	animation.update(rowNumber, deltaTime, LuffyFacingRight);

	// Déplace le corps du joueur
	LuffyBody.setTextureRect(animation.uvRect);

/// Vérifie si le joueur est en dehors des limites de la fenêtre
	sf::Vector2f newPosition = LuffyBody.getPosition() + movement;
	if (newPosition.x >= 0 && newPosition.x + LuffyBody.getLocalBounds().width <=( window.getSize().x))
		LuffyBody.move(movement);
	
	// Initialize Luffy and load game over texture
	if (!gameOverTexture.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/background/end.png")) {
		std::cerr << "Failed to load game over texture" << std::endl;
	}
	gameOverSprite.setTexture(gameOverTexture);
	
}
sf::RectangleShape Luffy::getLuffyBody()
{
	return LuffyBody;
}



// Fonction pour dessiner le joueur sur la fenêtre
void Luffy::draw(sf::RenderWindow& window)
{
	//LuffyBody.setPosition(round(180.0f), round(250.0f));
	window.draw(LuffyBody);
}
void Luffy::changeAnimation(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, unsigned int row)
{
	animation.changeTexture(texture, totalImages, switchingTime, row);
}

void Luffy::setPosition(sf::Vector2f newPos) {
	position = newPos;
}
/*sf::Vector2f Luffy::getposition()
{
	return 
}*/
/*void Luffy::updateBackground(BackgroundMap& background, sf::RenderWindow& window)
{
	background.update(position, window.getSize());
}*/

// Method to check collision with knives
bool Luffy::checkCollisionWithKnives(const std::vector<sf::Sprite>& knives) {
	for (const auto& knife : knives) {
		if (LuffyBody.getGlobalBounds().intersects(knife.getGlobalBounds())) {
			
			return true;
		}
	}
	return false;
}

void Luffy::die() {
	std::cout << "Luffy has died!" << std::endl;

	// Handle death logic such as resetting the game or showing game over screen
}
void Luffy::win() {
	std::cout << "Luffy win!!!!" << std::endl;

	// Handle death logic such as resetting the game or showing game over screen
}

void Luffy::drawGameOver(sf::RenderWindow& window) {
	sf::Texture gameOverTexture;
	if (!gameOverTexture.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/background/Game Over.jpg")) {
		std::cerr << "Error loading file!" << std::endl;
		return;
	}

	sf::Sprite gameOverSprite(gameOverTexture);
	window.draw(gameOverSprite);
}
void Luffy::drawGameWin(sf::RenderWindow& window)
{
	sf::Texture winTexture;
	if (!winTexture.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/background/end.png")) {
		std::cerr << "Error loading file!" << std::endl;
		return;
	}

	sf::Sprite winSprite(winTexture);
	window.draw(winSprite);
}

//bool Luffy::checkCollisionWithBagi(sf::RectangleShape& bagibody)

	//return LuffyBody.getGlobalBounds().intersects(bagibody.getGlobalBounds());


bool Luffy::checkCollisionWithBagi(const sf::RectangleShape& bagibody) {
	return LuffyBody.getGlobalBounds().intersects(bagibody.getGlobalBounds());
}


bool Luffy::isNearbagi(Bagi& bagi, float d)
{
	// Get the positions of Morgan and Luffy bodies
	sf::Vector2f bagiPosition = LuffyBody.getPosition();
	sf::Vector2f luffyPosition = bagi.getBagiBody().getPosition();

	// Calculate the distance between Morgan and Luffy
	float distance = std::sqrt(std::pow(bagiPosition.x - luffyPosition.x, 2) + std::pow(bagiPosition.y - luffyPosition.y, 2));

	// Return true if the distance is less than or equal to 10 pixels
	return distance <= d;
}

