#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class BackgroundMap {
public:
    BackgroundMap(const std::string& mapFilename, const sf::Vector2f& playerStartPosition, const sf::Vector2u& windowSize);
    void update(const sf::Vector2f& playerPosition);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
    sf::View gameView;          // View for managing what part of the map is visible
    sf::Vector2u windowSize;    // Size of the window to determine view size
    sf::Vector2f playerStartPosition;  // Initial position of the player, to center the view initially
};