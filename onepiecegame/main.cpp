#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include "Animation.h"
#include "Luffy.h"
#include<sstream>
#include <SFML/Audio.hpp>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "Heartmeet.h"
#include "Alveda.h"
#include "Knife.h"
#include "Bagi.h"
#include "BackgroundMap.h"
#include "Morgan.h"

//Window dimensions
const unsigned WINDOW_WIDTH = 1800;
const unsigned WINDOW_HEIGHT = 1000;

const int MAX_NUMBER_OF_ITEMS = 2;

const float LUFFY_FRAME_WIDTH = 180.0f;
const float LUFFY_FRAME_HEIGHT = 250.0f;
const float jumpVelocity = 400.0f;
const float LUFFY_SPEED = 300.0f;

const float alveda_speed= 70.0f;
const float bagi_speed = 20.0f;
const float morganSpeed = 85.0f;


// Background offset el pas de khalfya
unsigned offset = 2;



class Menu {
public:
	Menu(float width, float height) {
		if (!font.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/font/super_ocean/s.o.ttf")) {
			std::cout << "Error loading font file!" << std::endl;
		}
		menu[0].setFont(font);
		menu[0].setFillColor(sf::Color::Green);
		menu[0].setCharacterSize(80);
		menu[0].setString("Start Game");
		menu[0].setPosition(sf::Vector2f(300, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
		// height / (MAX_NUMBER_OF_ITEMS + 1) * 1
		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::Red);
		menu[1].setCharacterSize(80);
		menu[1].setString("Exit");
		menu[1].setPosition(sf::Vector2f(400, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));



		selectedItemIndex = 0;

		// Load the background texture
		if (!bgTexture.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/background/b1.jpg")) {
			std::cout << "Error loading background texture!" << std::endl;
		}
		bgSprite.setTexture(bgTexture);
		sf::Sprite backgroundSprite(bgTexture);

		float scrollSpeed = 100.0f; // Adjust the scroll speed
		sf::Clock clock;

		// Load the background music
		if (!bgMusic.openFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/video-audio/intr.ogg")) 
		{
			std::cout << "Error loading background music!" << std::endl;
		}
		bgMusic.setLoop(true);
		bgMusic.play();
	}


	void draw(sf::RenderWindow& window) {
		window.draw(bgSprite);

		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
			window.draw(menu[i]);
		}
	}

	void moveUp() {
		if (selectedItemIndex - 1 >= 0) {
			menu[selectedItemIndex].setFillColor(sf::Color::Black);
			selectedItemIndex--;
			menu[selectedItemIndex].setFillColor(sf::Color::Green);
		}
	}

	void moveDown() {
		if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
			menu[selectedItemIndex].setFillColor(sf::Color::Black);
			selectedItemIndex++;
			menu[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}
	void stopBackgroundMusic() {
		bgMusic.stop();
		
	}
	void pauseBackgroundMusic()
	{
		bgMusic.pause();
	}
	void playBackgroundMusic() {
		bgMusic.play();
	}

	int getSelectedItemIndex() {
		return selectedItemIndex;
	}

private:
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	int selectedItemIndex;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	sf::Music bgMusic;
	
};


int main()
{
	bool gamePaused = false; 
	bool win = false;//  gamePaused initilisé a false
	srand(time(0));
	//backgrouund
	sf::Texture t1, t3, t4;
	t1.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/background/bac.jpg");
	t3.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/background/end.png");
	
	t1.setSmooth(true);
	t3.setSmooth(true);

	//sf::Sprite background(t2);
	BackgroundMap back_m("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/background/0101.jpg", sf::Vector2f(20.0f, 740.0f), sf::Vector2u(500, WINDOW_HEIGHT));
	sf::Sprite background2(t3);
	  // Game Score -----------------------------------------------------------
	sf::RectangleShape scoreZone(sf::Vector2f(200, 90)); // un Rectangle noir pour afficher le texte de l'heure

	scoreZone.setFillColor(sf::Color::Black);
	scoreZone.setOutlineThickness(1.0f);
	scoreZone.setOutlineColor(sf::Color::White);
	scoreZone.setPosition(15,15);
	sf::Font font; // Police pour le texte du temps écoulé
	font.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/font/RoughenCornerRegular.ttf");
	sf::Text timeText;
	timeText.setFont(font);
	timeText.setCharacterSize(50);
	timeText.setFillColor(sf::Color::White);
	timeText.setPosition(18, 16);
	// Timer
	sf::Clock timer;
	timer.restart();
	//-----------------------------------------------------------------------------

	// player Sprite ...................................................
	sf::Texture LuffyTexture, Luffyfight1, Luffyfight2, luffyrun, LuffyTex, Luffyfight3, lufydie, luffyfight4, luffyfight5;
	
	LuffyTex.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/lufy000.png");
	LuffyTexture = LuffyTex;
	Luffy Luffy(&LuffyTexture, sf::Vector2u(5, 1), 0.08f, LUFFY_SPEED,jumpVelocity);
	luffyrun.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/l2.png");
	Luffyfight1.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/lufy22.png");
	Luffyfight2.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/lufy4.png");
	Luffyfight3.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/lufy3.png");
	luffyfight4.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/gomlufy.png");
	luffyfight5.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/flufy.png");
	lufydie.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/ddl.png");
	float deltaTime = 0.0f;

	sf::Clock playerClock;
	sf::Texture originalTexture;


	///alvedaa_______________________________________
	bool alveda_die = false;
	sf::Texture alvedatexture, alvedafight, team, alvedadie;
	alvedafight.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/alveda2.png");//mmmm
	alvedatexture.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/alveda4.png");//alveda
	alvedadie.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/alveda die.png");//alv-die
	Alveda alveda(&alvedatexture, sf::Vector2u(4, 1), 0.08f, alveda_speed,1400,700 );
	
	sf::Clock alvedaClock;
	////////////team
	team.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/team2.png");
	Alveda Team(&team, sf::Vector2u(1, 1), 0.08f, 0.0f, 1400, 700);

	
	
	//////////////morgan
	bool morgan_die = false;
	sf::Texture morgantexture, morganfight, morgandie, karnit, karnitre;
	morgandie.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/morgandie.png");
	morganfight.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/m1.png");
	morgantexture.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/morgan1.png");
	Morgan morgan(&morgantexture, sf::Vector2u(5, 1), 0.08f, morganSpeed, 1500, 700);
	
	
	/////arlong
	sf::Texture arlong, arlong1;
	arlong.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/arlong.png");
	arlong1.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/arlong3.png");
	Morgan Arlong(&arlong, sf::Vector2u(4, 1), 0.08f, morganSpeed, 1500, 700);

	///////smoker
	sf::Texture smoker, smoker1, smoker2;
	smoker.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/smoker.png");
	smoker1.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/smoker1.png");
	smoker2.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/smoker2.png");
	Morgan Smoker(&smoker, sf::Vector2u(5, 1), 0.08f, morganSpeed, 1500, 700);
	
	//////karnit
	sf::Texture karnitdie;
	bool karnit_die = false;
	karnitdie.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/kardie1.png");
	karnitre.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/karnirelade.png");
	Morgan Karnit(&karnitre, sf::Vector2u(4, 1), 0.08f, 75.0f, 1500, 700);


	////bagi__________
	sf::Texture bagitexture, bagifeet, bagidie;
	bagitexture.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/bagi1.png");
	bagidie.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/bagidie.png");
	Bagi bagi(&bagitexture, sf::Vector2u(3, 1), 0.08f, 400.0f, 1500, 700);
	sf::Sprite bagisprite(bagitexture);
	sf::Clock bagiClock;
	//
	bagifeet.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/caractere/156.png");
	Bagi feet(&bagifeet, sf::Vector2u(3, 1), 0.08f, 300.0f, 1500, 725);
	sf::Sprite feetsprite(bagifeet);
	

	/////heart zone _________________________________________________________________

	sf::Texture hearttexture;
	hearttexture.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/objects/meet.png");
	
	Heartmeet heart1(&hearttexture, 1450.0f, 5.0f);
	Heartmeet heart2(&hearttexture, 1550.0f, 5.0f);
	Heartmeet heart3(&hearttexture, 1650.0f, 5.0f);

	///ili chyatl3ou mil louta_______
	Heartmeet heart(&hearttexture, 300.0f, 500.0f);
	Heartmeet heart4(&hearttexture, 600.0f, 600.0f);
	///////teamm
	
	

	// knife______________________
	// Create knife textures
	sf::Texture knifeTexture;
	knifeTexture.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/objects/knife.png");
	// Initialize random seed
	std::srand(std::time(nullptr));
	Knife knives(&knifeTexture, sf::Vector2u(1, 1), 0.08f, WINDOW_WIDTH, WINDOW_HEIGHT, 20,40,8,10);
	sf::Clock knifeClock;

	////background end
	// Game Over Texture et Sprite

	sf::Texture gameOverTexture;
	gameOverTexture.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/background/gameov.jpg");

	sf::Sprite gameOverSprite;
	gameOverSprite.setTexture(gameOverTexture);
	gameOverSprite.setPosition(WINDOW_WIDTH / 2 - gameOverSprite.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - gameOverSprite.getGlobalBounds().height / 2);
	/////////////
	sf::Texture gamewinTexture;
	gamewinTexture.loadFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/images/background/ending.jpg");

	sf::Sprite gamewinSprite;
	gamewinSprite.setTexture(gamewinTexture);
	gamewinSprite.setPosition(WINDOW_WIDTH / 2 - gamewinSprite.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - gamewinSprite.getGlobalBounds().height / 2);
	/////////////
	//----------------------------------
	// gameOverSound Buffer
	sf::Music gameOverSoundBuffer;
	gameOverSoundBuffer.openFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/video-audio/ending-song.ogg");
	gameOverSoundBuffer.setLoop(true);
	//gameOverSoundBuffer.openFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/video-audio/gear 5.ogg");

	

	//----------------------------------
	// gameOverSound Buffer
	sf::Music runsound, jumpsound, kicksound, kicksound2;
	sf::Music bloodsound;
	bloodsound.openFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/video-audio/bloodsound0.ogg");
	bloodsound.setLoop(true);
	runsound.openFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/video-audio/lufy-run.ogg");
	jumpsound.openFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/video-audio/lufy-jump.ogg");
	kicksound2.openFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/video-audio/kick-sound.ogg");
	kicksound.openFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/video-audio/gomogomsound.ogg");
	kicksound.setLoop(true);
	jumpsound.setLoop(true);
	//////////////////////////////////
	sf::RenderWindow window(sf::VideoMode(1800,900), "Menu");
	
	Menu menu(window.getSize().x, window.getSize().y);
	
	sf::Music music;
	if (!music.openFromFile("C:/Users/LENOVO/source/repos/onepiecegame/onepiecegame/one piece game/mini jeu one piece/video-audio/royalty.ogg")) {
		std::cout << "Error loading background music!" << std::endl;
	}
	music.setLoop(true);
	


	menu.playBackgroundMusic();

	
	while (window.isOpen())
	{
		

		// The music will continue to play until the program exits
		
		//event
		sf::Event event;
		
		music.play();
		
		while (window.pollEvent(event))
		{
			
			
			switch (event.type)
			{
				
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Down:
					menu.moveUp();
					break;
				case sf::Keyboard::Up:
					menu.moveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.getSelectedItemIndex())
					{
					case 0:
					{
						
						std::cout << "Start button pressed!" << std::endl;

						sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "game");
						app.setFramerateLimit(60);

						float scrollSpeed = 100.0f; // Adjust the scroll speed
				    	sf::Clock clock;


					
						timer.restart();

						
						
						while (app.isOpen())
						{
							menu.pauseBackgroundMusic();
							
							
								// player deltatime ......................................
								deltaTime = playerClock.restart().asSeconds();
								// ......................................
								
								//event
				
								
								sf::Event event;
								while (app.pollEvent(event))
								{
									switch (event.type)
									{
									case sf::Event::Closed:
									{
										menu.playBackgroundMusic();
										app.close();
										break;
									}
									case sf::Event::KeyPressed:
									{
										
											if ((event.key.code == sf::Keyboard::Left) || (event.key.code == sf::Keyboard::Right))
											{
												LuffyTexture = luffyrun;
												Luffy.changeAnimation(&LuffyTexture, sf::Vector2u(5, 1), 0.08f, 1);
												jumpsound.pause();
												kicksound.pause();
												kicksound2.pause();
												bloodsound.pause();
												runsound.play();

											}
											if (event.key.code == sf::Keyboard::Up)
											{

												LuffyTexture = Luffyfight1;
												Luffy.changeAnimation(&LuffyTexture, sf::Vector2u(6, 1), 0.08f, 1);
												runsound.pause();
												kicksound.pause();
												kicksound2.pause();
												bloodsound.pause();
												jumpsound.play(); 

											}
											if (event.key.code == sf::Keyboard::W)
											{
												LuffyTexture = Luffyfight2;
												Luffy.changeAnimation(&LuffyTexture, sf::Vector2u(5, 1), 0.08f, 1);
												jumpsound.pause();
												runsound.pause();
												kicksound2.pause();
												
												kicksound.play();
												if (alveda.isNearLuffy(Luffy, 85.0f))
												{
													alveda_die = true;
													alvedatexture = alvedadie;
													alveda.changeAnimation(&alvedatexture, sf::Vector2u(1, 1), 0.08f, 1);
													bloodsound.play();
												}
												if (morgan.isNearLuffy(Luffy, 90.0f))
												{
													morgan_die = true;
													bloodsound.play();
													morgantexture = morgandie;
													morgan.changeAnimation(&morgantexture, sf::Vector2u(1, 1), 0.08f, 1);
												}
												if (Karnit.isNearLuffy(Luffy, 90.0f))
												{
													karnit_die = true;
													bloodsound.play();
													karnitre = karnitdie;
													Karnit.changeAnimation(&karnitre, sf::Vector2u(1, 1), 0.08f, 1);
												}
												
											}
											if (event.key.code == sf::Keyboard::Z)
											{
												LuffyTexture = Luffyfight3;
												Luffy.changeAnimation(&LuffyTexture, sf::Vector2u(3, 1), 0.08f, 1);
												jumpsound.pause();
												runsound.pause();
												kicksound.pause();
												//bloodsound.pause();
												kicksound2.play();
												if (Karnit.isNearLuffy(Luffy, 90.0f))
												{
													karnit_die = true;
													bloodsound.play();
													karnitre = karnitdie;
													Karnit.changeAnimation(&karnitre, sf::Vector2u(1, 1), 0.08f, 1);
												}
												if (morgan.isNearLuffy(Luffy, 90.0f))
												{
													morgan_die = true;
													morgantexture = morgandie;
													bloodsound.play();
													morgan.changeAnimation(&morgantexture, sf::Vector2u(1, 1), 0.08f, 1);
												}
												if (alveda.isNearLuffy(Luffy, 85.0f))
												{
													alveda_die = true;
													alvedatexture = alvedadie;
													bloodsound.play();
													alveda.changeAnimation(&alvedatexture, sf::Vector2u(1, 1), 0.08f, 1);
												}

											}
											if (event.key.code == sf::Keyboard::D)
											{
												LuffyTexture = luffyfight4;
												Luffy.changeAnimation(&LuffyTexture, sf::Vector2u(3, 1), 0.08f, 1);
												jumpsound.pause();
												runsound.pause();
												kicksound2.pause();
												//bloodsound.pause();
												kicksound.play();
												if (Karnit.isNearLuffy(Luffy, 90.0f))
												{
													karnit_die = true;
													bloodsound.play();
													karnitre = karnitdie;
													Karnit.changeAnimation(&karnitre, sf::Vector2u(1, 1), 0.08f, 1);
												}
												if (morgan.isNearLuffy(Luffy, 90.0f))
												{
													morgan_die = true;
													bloodsound.play();
													morgantexture = morgandie;
													morgan.changeAnimation(&morgantexture, sf::Vector2u(1, 1), 0.08f, 1);
												}
												if (alveda.isNearLuffy(Luffy, 85.0f))
												{
													alveda_die = true;
													bloodsound.play();
													alvedatexture = alvedadie;
													alveda.changeAnimation(&alvedatexture, sf::Vector2u(1, 1), 0.08f, 1);
												}
											}
											if (event.key.code == sf::Keyboard::X)
											{
												LuffyTexture = luffyfight5;
												Luffy.changeAnimation(&LuffyTexture, sf::Vector2u(2, 1), 0.08f, 1);
												jumpsound.pause();
												runsound.pause();
												kicksound.pause();
												//bloodsound.pause();
												kicksound2.play();
												if (Karnit.isNearLuffy(Luffy, 90.0f))
												{
													karnit_die = true;
													bloodsound.play();
													karnitre = karnitdie;
													Karnit.changeAnimation(&karnitre, sf::Vector2u(1, 1), 0.08f, 1);
												}
												if (morgan.isNearLuffy(Luffy, 90.0f))
												{
													morgan_die = true;
													bloodsound.play();
													morgantexture = morgandie;
													morgan.changeAnimation(&morgantexture, sf::Vector2u(1, 1), 0.08f, 1);
												}
												if (alveda.isNearLuffy(Luffy, 85.0f))
												{
													alveda_die = true;
													bloodsound.play();
													alvedatexture = alvedadie;
													alveda.changeAnimation(&alvedatexture, sf::Vector2u(1, 1), 0.08f, 1);
												}
											}
										
									}
									default:
										break;
									}
									
								}
						
								
								

								// Game Over update -----------------------
								if (gamePaused == false)
								{

									// Scroll left
									sf::Time d = clock.restart();



									// Compteur du temps écoulé


									int seconds = timer.getElapsedTime().asSeconds();

									std::stringstream time;
									time << "Time: " << seconds << "s";

									timeText.setString(time.str());
									///move the knives

									knives.move_knifes(app, WINDOW_WIDTH, WINDOW_HEIGHT, 20, 40, 10);
									// player animation ......................................					
								
									// Move the first heart meet to a new position and remove the knife

									
									int i = 0;
									bool collisionDetected = false;
									
									knives.checkCollisionAndErase(Luffy, heart1,bloodsound);
									

									if (Luffy.isNearbagi(bagi, 75.0f))
									{
										gamePaused = true;
										Luffy.die();
										jumpsound.pause();
										runsound.stop();
										kicksound.pause();
										kicksound2.pause();
										bloodsound.pause();
										music.stop();
										gameOverSoundBuffer.play();
									}
									if (Luffy.isNearbagi(feet, 75.0f))
									{
										heart3.moveheart(-1000, -1000);
										bloodsound.play();
										LuffyTexture = lufydie;
										Luffy.changeAnimation(&LuffyTexture, sf::Vector2u(2, 1), 0.08f, 1);
										
									}


									// Assuming heart1, heart2, and heart3 are Heartmeet objects

									if (alveda_die == false && alveda.isNearLuffy(Luffy,250.0f))
									{
										alvedatexture = alvedafight;
										alveda.changeAnimation(&alvedatexture, sf::Vector2u(2, 1), 0.08f, 1);
										
									}

									if (alveda_die==false && alveda.isNearLuffy(Luffy, 75.0f))
									{
										
											heart2.moveheart(-1000, -1000);
											bloodsound.play();
											LuffyTexture = lufydie;
											Luffy.changeAnimation(&LuffyTexture, sf::Vector2u(2, 1), 0.08f, 1);
											
										
									}

									////////////////////
									//

									if (morgan_die==false && morgan.isNearLuffy(Luffy, 300.0f))
									{
										morgantexture = morganfight;
										morgan.changeAnimation(&morgantexture, sf::Vector2u(5, 1), 0.08f, 1);
										
									}
									if (morgan_die==false && morgan.isNearLuffy(Luffy, 75.0f))
									{
										heart3.moveheart(-1000, -1000);
										bloodsound.play();
										LuffyTexture = lufydie;
										Luffy.changeAnimation(&LuffyTexture, sf::Vector2u(2, 1), 0.08f, 1);
										
									}
									///////
					
									//////
									if (Smoker.isNearLuffy(Luffy, 250.0f))
									{
										smoker = smoker1;
										Smoker.changeAnimation(&smoker, sf::Vector2u(5, 1), 0.08f, 1);

									}
									if (Smoker.isNearLuffy(Luffy, 75.0f))
									{
										gamePaused = true;
										Luffy.die();
										runsound.pause();
										jumpsound.pause();
										kicksound.pause();
										kicksound2.pause();
										bloodsound.pause();
										music.stop();
										gameOverSoundBuffer.play();
									}

									/*if (Smoker.isNearLuffy(Luffy, 300.0f))
									{
										smoker = smoker2;
										Smoker.changeAnimation(&smoker, sf::Vector2u(3, 1), 0.08f, 1);

									}*/
									
												
									//////
									if (Arlong.isNearLuffy(Luffy, 300.0f))
									{
										arlong = arlong1;
										Arlong.changeAnimation(&arlong, sf::Vector2u(4, 1), 0.08f, 1);

									}
								
									if (Arlong.isNearLuffy(Luffy, 75.0f))
									{
										heart2.moveheart(-1000, -1000);
										bloodsound.play();
										LuffyTexture = lufydie;
										Luffy.changeAnimation(&LuffyTexture, sf::Vector2u(2, 1), 0.08f, 1);
										
									}
									


									
									// If all heart meets have been relocated, handle game over logic
									if (heart1.ismoved() && heart2.ismoved() && heart3.ismoved()) {
										gamePaused = true;
										Luffy.die();
										jumpsound.pause();
										runsound.pause();
										kicksound.pause();
										kicksound2.pause();
										bloodsound.pause();
										music.stop();
										gameOverSoundBuffer.play();
									}
										
									
									
									/*if (Karnit.isNearLuffy(Luffy, 400.0f))
									{
										karnit= karnitre;
										Karnit.changeAnimation(&karnit, sf::Vector2u(4, 1), 0.08f, 1);

									}*/
									if (karnit_die==false && Karnit.isNearLuffy(Luffy, 75.0f))
									{
										heart3.moveheart(-1000, -1000);
										bloodsound.play();
										LuffyTexture = lufydie;
										Luffy.changeAnimation(&LuffyTexture, sf::Vector2u(2, 1), 0.08f, 1);
										
									}
									
									if (Team.isNearLuffy(Luffy, 75.0f))
									{

										Luffy.win();
										win = true;
										gamePaused = true;
										jumpsound.pause();
										runsound.stop();
										kicksound.pause();
										kicksound2.pause();
										bloodsound.pause();
										music.stop();
										gameOverSoundBuffer.play();
									}
		

								}
								int seconds = timer.getElapsedTime().asSeconds();
								app.clear();
								
								back_m.draw(app);
								
								
								if (gamePaused == false) {

									sf::RectangleShape  b = Luffy.getLuffyBody();
									back_m.update(b.getPosition());
									Luffy.update(deltaTime, app);
									knives.update(deltaTime, app);
								
									app.draw(scoreZone);
									app.draw(timeText);

									heart1.draw(app);
									heart2.draw(app);
									heart3.draw(app);
									//..............................
									knives.draw(app);
									
									Luffy.draw(app);
									

									if (!(seconds <= 23 || seconds > 60))
									{
										alveda.update(deltaTime, app);
										alveda.draw(app);
										
									}


									if (!(seconds <= 7 || seconds > 90))
									{
										bagi.update(deltaTime, app);
										
										bagi.draw(app);
										
									}
									if (!(seconds <= 33 || seconds > 90))
									{
										feet.update(deltaTime, app);
										feet.draw(app);
									}
									
									if (!(seconds <= 3 || seconds > 60))
									{
										morgan.update(deltaTime, app);
										morgan.draw(app);
										
									}
									if (!(seconds <= 14 || seconds > 60))
									{
										Arlong.update(deltaTime, app);
										Arlong.draw(app);

									}
									if (!(seconds <= 60 || seconds > 90))
									{
										Smoker.update(deltaTime, app);
										Smoker.draw(app);

									}
									if (!(seconds <= 35 || seconds > 70))
									{
										Karnit.update(deltaTime, app);
										Karnit.draw(app);

									}
									

									if (!(seconds <= 75))
									{
										Team.update(deltaTime,app);
										Team.draw(app);
										
									}
									
									if (seconds > 90)
									{
										
										Luffy.win();
										win = true;
										gamePaused = true;
										jumpsound.pause();
										runsound.stop();
										kicksound.pause();
										kicksound2.pause();
										bloodsound.pause();
										music.stop();
										gameOverSoundBuffer.play();
										
									}

								}
								else {
									// Display the game over sprite when the game is paused
									if (win == true)
									{
										app.draw(gamewinSprite);
									}
									else
									{
										app.draw(gameOverSprite);
										
									}
								}

								
								
								app.display();
								
								
							
						}

						break;
					}

					case 1:
						window.close();
						
						break;
					}
					break;
				}
				break;
			
			case sf::Event::Closed:
				
				window.close();
				break;
			}
		}
		
		window.clear();
		menu.draw(window);
		
		window.display();
		
	}

	return 0;
}





