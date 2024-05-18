#include "Knife.h"


Knife::Knife(sf::Texture* KnifeTexture, sf::Vector2u totalImages, float switchingTime, unsigned windowWidth, unsigned windowHeight, float k_width, float k_height,int numk, int knifeSpeed):animation(KnifeTexture, totalImages, switchingTime,rowNumber)
{
    this->numk = numk;
    this->k_height = k_height;
    this->k_width = k_width;
    knifeFacingRight = true;
    // Create knives
    rowNumber = 0;
   
    for (int i = 0; i < numk; i++)
    {
        sf::Sprite knife;
        knifeBody.setSize(sf::Vector2f(40.0f, 20.0f));
        knifeBody.setPosition(k_width,k_height );
        knifeBody.setTexture(KnifeTexture);
        knife.setTexture(*KnifeTexture);
        knife.setPosition(std::rand() % windowWidth, 0);
        knife.setOrigin(k_width / 2, k_height / 2);
        knives.push_back(knife);
       
    }
}

void Knife::move_knifes(sf::RenderWindow& window,unsigned windowWidth, unsigned windowHeight, float k_width, float k_height,int knifeSpeed)
{
    // Move knives
    for (sf::Sprite& knife : knives)
    {
        knife.move(0, knifeSpeed);
        if (knife.getPosition().y > windowHeight)
        {
            knife.setPosition(std::rand() % windowWidth, 0 - std::rand() % (windowHeight / 2));
        }
    }
    // Check for knife collisions
    for (sf::Sprite& knife : knives)
    {
        if (knife.getGlobalBounds().top + k_height > windowHeight)
        {
            // Knife hit the bottom
            if (sf::Mouse::getPosition(window).x > knife.getPosition().x - k_width / 2 &&
                sf::Mouse::getPosition(window).x < knife.getPosition().x + k_width / 2 &&
                sf::Mouse::getPosition(window).y > knife.getPosition().y - k_height / 2 &&
                sf::Mouse::getPosition(window).y < knife.getPosition().y + k_height / 2)
            {
                // Knife hit the mouse
                window.close();
            }
        }
        else
        {
            // Knife is coming from the sides
            if (knife.getGlobalBounds().left < 0 && knife.getGlobalBounds().top > 0 && knife.getGlobalBounds().top < windowHeight ||
                knife.getGlobalBounds().left + k_width > windowWidth && knife.getGlobalBounds().top > 0 && knife.getGlobalBounds().top < windowHeight)
            {
                // Knife hit the window border
                knife.setPosition(std::rand() % windowWidth, 0 - std::rand() % (windowHeight / 2));
            }
        }
    }
   


}
void Knife::update(float deltaTime, const sf::RenderWindow& window)
{

    sf::Vector2f movement(0.0f, 0.0f);
    if (movement.x == 0.0f)
        rowNumber = 0;
    else
    {
        rowNumber = 0;
        if (movement.x > 0.0f)
            knifeFacingRight = true;
        else
            knifeFacingRight = false;
    }
    // Met à jour l'animation en fonction du mouvement et de la direction
    animation.update(rowNumber, deltaTime, knifeFacingRight);
    // Déplace le corps du joueur
    knifeBody.setTextureRect(animation.uvRect);

    // Vérifie si le joueur est en dehors des limites de la fenêtre
    sf::Vector2f newPosition = knifeBody.getPosition() + movement;
    knifeBody.move(movement);

}
void Knife::draw(sf::RenderWindow& window)
{
    for (const sf::Sprite& knife : knives)
    {
        window.draw(knife);
    }
}
std::vector<sf::Sprite> Knife::getknives()
{
    return knives;
}
sf::RectangleShape Knife::getknifeBody()
{
    return knifeBody;
}
void Knife::checkCollisionAndErase(Luffy& luffy,Heartmeet& heart1,sf::Music& m) {
    // Get the position and size of Luffy's body
    sf::FloatRect luffyBounds = luffy.getLuffyBody().getGlobalBounds();
   
    // Iterate through all knives
    for (auto it = knives.begin(); it != knives.end(); ++it) {
        // Get the position and size of the current knife
        sf::FloatRect knifeBounds = it->getGlobalBounds();
        
        // Check for collision between Luffy and the current knife
        if (luffyBounds.intersects(knifeBounds)) {
            // Erase the knife from the vector
            m.play();
            it = knives.erase(it);
           
           
            heart1.moveheart(-1000, -1000); 
            
            
            --it;
           
                // Decrement iterator to ensure it points to the correct position after erasing
              
                // Check for collision between Luffy and the current knifes 
        }
        
       
      
    }
    
    

}