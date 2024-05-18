

#include "BackgroundMap.h"

BackgroundMap::BackgroundMap(const std::string& mapFilename, const sf::Vector2f& playerStartPosition, const sf::Vector2u& windowSize)
    : playerStartPosition(playerStartPosition), windowSize(windowSize)
{
    if (!mapTexture.loadFromFile(mapFilename)) {
        std::cerr << "Error loading map texture" << std::endl;
    }
    mapSprite.setTexture(mapTexture);
    gameView.setSize(windowSize.x, windowSize.y);
    gameView.setCenter(playerStartPosition);
}

void BackgroundMap::update(const sf::Vector2f& playerPosition) {
    float deltaTime(2);
    // Define the threshold for starting the scrolling
    float scrollStartOffset = windowSize.x * 0.001;
    float center = gameView.getCenter().x;
    float viewSpeed = 1024; // pixels per second
    
    if (playerPosition.x > center + scrollStartOffset) {
        // Player is to the right of the center threshold, move view right
        center += viewSpeed * deltaTime;
        if (center > playerPosition.x - scrollStartOffset) {
            center = playerPosition.x - scrollStartOffset;
        }
    }
    else if (playerPosition.x < center - scrollStartOffset) {
        // Player is to the left of the center threshold, move view left
        center -= viewSpeed * deltaTime;
        if (center < playerPosition.x + scrollStartOffset) {
            center = playerPosition.x + scrollStartOffset;
        }
    }

    // Clamp the center to the map boundaries
    center = std::max(windowSize.x / 2.0f, center); // Minimum x center
    center = std::min(mapTexture.getSize().x - windowSize.x / 2.0f, center); // Maximum x center

    gameView.setCenter(center, windowSize.y / 2.0f); // Assuming no vertical scrolling
}

void BackgroundMap::draw(sf::RenderWindow& window) {
    window.setView(gameView);
    window.draw(mapSprite);
    window.setView(window.getDefaultView()); // Reset to default view after drawing (if needed elsewhere)
}



