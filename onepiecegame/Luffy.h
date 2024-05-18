#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "BackgroundMap.h"
#include <SFML/Window.hpp>
#include "Bagi.h"
class Luffy
{
private:
	sf::RectangleShape LuffyBody;
	Animation animation;
	unsigned int rowNumber;
	float LuffySpeed;
	bool LuffyFacingRight;
    //jump
	float jumpVelocity;
	bool isJumping;
	// Variables liées au saut
	float gravity;           // Gravité affectant le joueur
	float jumpStrength;      // Vitesse de saut vers le haut
	float verticalVelocity;  // Vitesse verticale actuelle du joueur
	float groundLevel;       // La coordonnée y représentant le niveau du sol
	bool isOnGround;         // Indicateur indiquant si le joueur est au sol

	sf::Vector2f position;
	// Additional member to hold the game over texture and sprite
	sf::Texture gameOverTexture;
	sf::Sprite gameOverSprite;


public:
	Luffy(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime, float LuffySpeed, float jumpVelocity);
	void update(float deltaTime, const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void changeAnimation(sf::Texture* texture, sf::Vector2u totalImages, float switchingTime,unsigned int row);
	sf::RectangleShape getLuffyBody();
	void setPosition(sf::Vector2f newPos);
	bool checkCollisionWithKnives(const std::vector<sf::Sprite>& knives);
	void die();
	void win();
	void drawGameOver(sf::RenderWindow& window);
	void drawGameWin(sf::RenderWindow& window);
	bool checkCollisionWithBagi(const sf::RectangleShape& bagibody);
	//void updateBackground(BackgroundMap& background, sf::RenderWindow& window);
	bool isNearbagi(Bagi& bagi, float d);

};
