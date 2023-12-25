#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "mainmenu.h"
#include <time.h>
#include <ctime>

using namespace sf;
using namespace std;

void  options(RenderWindow& window, Event& event, int& phase);
void GamePlay(RenderWindow& window,Event& event,int &phase);

int main()
{

	RenderWindow window(VideoMode(1000, 700), "METAL SLUGE", Style::None);
	
	MainMenu mainMenu(1000, 700);
	int phase = -1;
	Texture mainmenuV2, leaderboard;
	
	mainmenuV2.loadFromFile("backgroundV1.png");
	leaderboard.loadFromFile("backgroundV2.png");
	Sprite mainmenuV2_sprite, leaderboard_sprite , options_sprite;
	
	mainmenuV2_sprite.setTexture(mainmenuV2);
	leaderboard_sprite.setTexture(leaderboard);
	leaderboard_sprite.setPosition(Vector2f(0, 0));
	leaderboard_sprite.setScale(1.11, 1.05);
	mainmenuV2_sprite.setPosition(Vector2f(-170, 0));
	mainmenuV2_sprite.setScale(0.25, 0.3);


	while (window.isOpen())
	{
		//mainmenu
		Event event;
		if (phase == -1)
		{


			while (window.pollEvent(event))
			{
				if (event.type == Event::KeyReleased)
				{
					if (event.key.code == Keyboard::Escape)
						window.close();
					else if (event.key.code == Keyboard::Up)
						mainMenu.moveup();
					else if (event.key.code == Keyboard::Down)
						mainMenu.movedown();
					else if (event.key.code == Keyboard::Enter)
						phase = mainMenu.MainMenupressed();

				}

				if (event.key.code == Keyboard::Tab) {
					phase = -1;

				}

				window.clear();
				window.draw(mainmenuV2_sprite);
				mainMenu.draw(window);
				window.display();
			}
		}

		//game is on

		else if (phase == 0)
		{
			GamePlay(window, event, phase);
			
		}

		//options

		else if (phase == 1)
		{
			options (window, event, phase);
		}

		//leaderboard

		else if (phase == 2)
		{
			while (window.pollEvent(event))
			{
				if (Keyboard::isKeyPressed(Keyboard::Tab))				
				phase = -1;
				
			}
					window.clear();
					window.draw(leaderboard_sprite);
					window.display();
		}

		//exit

		else if (phase == 3)
		{
			while (window.pollEvent(event))
			{
				if (event.type == event.Closed)
					window.close();

			}
		}

	}

}
void GamePlay(RenderWindow& window, Event& event, int &phase )
{
	
	Clock animation_clock,animation_clockV2, animation_clockV3,animation_clockV4, animation_clockV5, animation_clockV6, animation_clockV7;
	Clock clock; // starts the clock
	Clock map;
	srand(time(NULL));
	bool Slashing = 0;
	bool shooting = 0;
	bool reload = 0;
	bool afk = 0; 
	bool alive = 1;
	bool sandbag_collision = 0;
	bool sandbagEX_collision = 0 ;
	bool enemyv1_alive = 1 , enemyV1=0;

	int bullet_counter = 0, sandbag_counter = 0;
	int player_animation_legs = 0, player_animation_staple = 0, player_animation_shot = 0, GOGO_animation = 0, sandbags_animation = 0, sandbagsEX_animation = 0
		, player_animation_reload = 0, player_animation_afk_top = 0, player_animation_afk_bot = 0, player_animation_slashing = 0, player_animation_dying = 0
		, enemyv1_animation_run = 0, enemyv1_animation_shoot = 0, enemyv1_animation_die = 0, enemyV1_animation_sceared = 0
		, enemyv2_animation_run = 0, enemyv2_animation_shoot = 0, enemyv2_animation_die = 0;

	Texture playerStaple, PlayerMoveLegs, PlayerShot, PlayerReloading, PlayerAFKTop, PlayerAFKBot, PLayerSlashing, PlayerDying,GOGO,SandBag, SandBagEX,EnemyV1Run
		,EnemyV1Shoot,EnemyV1die,EnemyV1sceared, EnemyV2Shoot, EnemyV2die, EnemyV2Run;
	playerStaple.loadFromFile("playerStaple.png");
	PlayerMoveLegs.loadFromFile("PlayerMoveLegs.png");
	PlayerShot.loadFromFile("PlayerShot.png");
	PlayerReloading.loadFromFile("PlayerReloading.png");
	PlayerAFKBot.loadFromFile("PlayerAfkLegs.png");
	PlayerAFKTop.loadFromFile("playerAFK.png");
	PLayerSlashing.loadFromFile("PlayerSlashing.png");
	PlayerDying.loadFromFile("playerdie.png");
	GOGO.loadFromFile("GOGO.png");
	SandBag.loadFromFile("SandBagsV2.png");
	SandBagEX.loadFromFile("SandBagsEX.png");
	EnemyV1Run.loadFromFile("enemyV1run.png");
	EnemyV1Shoot.loadFromFile("enemyV1shoot.png");
	EnemyV1die.loadFromFile("enemyV1dead.png");
	EnemyV1sceared.loadFromFile("enemyV1sceared.png");
	EnemyV2Run.loadFromFile("enemyV2run.png");
	EnemyV2Shoot.loadFromFile("enemyV2shoot.png");
	EnemyV2die.loadFromFile("enemyV2dead.png");
	



	Sprite PlayerMoveLegs_sprite, playerStaple_sprite, playerdying_sprite,GOGO_sprite,SandBag_Sprite,EnemyV1Alive_sprite, EnemyV1Dead_sprite
		, EnemyV1Alive_sprite2, EnemyV2Alive_sprite, EnemyV2Dead_sprite;

	//player

	playerStaple_sprite.setTexture(playerStaple);
	PlayerMoveLegs_sprite.setTexture(PlayerMoveLegs);
	playerdying_sprite.setTexture(PlayerDying);
	PlayerMoveLegs_sprite.setPosition(0, 21);
	PlayerMoveLegs_sprite.setScale(1.3, 1.3);

	//enterface

	GOGO_sprite.setTexture(GOGO);
	GOGO_sprite.setScale(1, 1);
	GOGO_sprite.setPosition(100, 200);


	//map

	SandBag_Sprite.setTexture(SandBag);
	SandBag_Sprite.setTextureRect(IntRect(sandbags_animation * 54.58, 0, 54.58, 64));
	SandBag_Sprite.setPosition(200, 200);

	//enemy
	EnemyV1Alive_sprite.setTexture(EnemyV1Run);
	EnemyV1Alive_sprite.setPosition(400, 400);
	EnemyV1Alive_sprite.setTextureRect(IntRect(enemyv1_animation_run * 45, 0, 45, 40));

	EnemyV2Alive_sprite.setTexture(EnemyV2Run);
	EnemyV2Alive_sprite.setPosition(600, 500);
	EnemyV2Alive_sprite.setTextureRect(IntRect(enemyv2_animation_run * 42, 0, 42, 38));

	EnemyV1Alive_sprite2.setTexture(EnemyV1Run);
	EnemyV1Alive_sprite2.setPosition(700, 300);
	EnemyV1Alive_sprite2 .setTextureRect(IntRect(enemyv1_animation_run * 45, 0, 45, 40));
	EnemyV1Dead_sprite.setTexture(EnemyV1die);
	

	float xaxis_move = 5;
	bool afktime = 0;
	PlayerMoveLegs_sprite.setTextureRect(IntRect(0, 0, 20, 20));
	playerStaple_sprite.setTextureRect(IntRect(0, 0, 32.75, 29));
	while (window.pollEvent(event))
	{

		while (window.isOpen())
		{


			Time time = map.getElapsedTime();
			//cout << bullet_counter;
			cout << time.asSeconds() << endl;


			//moving right
			if (Keyboard::isKeyPressed(Keyboard::D)&&alive==1)
			{
				PlayerMoveLegs_sprite.setTexture(PlayerMoveLegs);
				playerStaple_sprite.setTexture(playerStaple);
				playerStaple_sprite.setTextureRect(IntRect(player_animation_staple * 32.75, 0, 32.75, 29));
				playerStaple_sprite.setPosition(PlayerMoveLegs_sprite.getPosition().x, 0);
				map.restart();
				//slash & moving right
				if (Keyboard::isKeyPressed(Keyboard::F) && Slashing == 0 &&alive ==1)
				{

					playerStaple_sprite.setPosition(PlayerMoveLegs_sprite.getPosition().x-14, -16);
					map.restart();
					if (animation_clock.getElapsedTime().asSeconds() > 0.1)
					{
						animation_clock.restart();
						player_animation_slashing++;
						player_animation_slashing %= 6;
					}
					playerStaple_sprite.setTexture(PLayerSlashing);
					playerStaple_sprite.setTextureRect(IntRect(43.8 * player_animation_slashing, 0, 43.8, 45));
					Slashing = 1;
				}
				else if (Slashing == 1)
				{
					PlayerMoveLegs_sprite.setTexture(PlayerMoveLegs);
					playerStaple_sprite.setTexture(PLayerSlashing);
					playerStaple_sprite.setPosition(PlayerMoveLegs_sprite.getPosition().x-14, -16);
					if (animation_clock.getElapsedTime().asSeconds() > 0.1)
					{
						animation_clock.restart();
						player_animation_slashing++;
						if (player_animation_slashing == 6)
						{
							player_animation_slashing = 0;
							Slashing = 0;
						}
						player_animation_legs++;
						if (player_animation_legs == 5)
						{
							player_animation_legs = 0;
						}
					}
					playerStaple_sprite.setTextureRect(IntRect(43.8 * player_animation_slashing, 0, 43.8, 45));
					PlayerMoveLegs_sprite.setTextureRect(IntRect(player_animation_legs * 20, 0, 20, 20));
					PlayerMoveLegs_sprite.setScale(1.3, 1.3);

				}
				//shoot & moving right
				if (Keyboard::isKeyPressed(Keyboard::X) && shooting == 0 &&alive ==1 && bullet_counter<11)
				{
					player_animation_reload = 0;
					if (animation_clock.getElapsedTime().asSeconds() > 0.15)
					{
						animation_clock.restart();
						player_animation_shot++;
						player_animation_shot %= 3;
					}
					playerStaple_sprite.setTexture(PlayerShot);
					playerStaple_sprite.setTextureRect(IntRect(54.3 * player_animation_shot, 0, 54.3, 23));
					shooting = 1;

				}
				else if (shooting == 1 && bullet_counter < 11)
				{
					if (animation_clock.getElapsedTime().asSeconds() > 0.15)
					{
						animation_clock.restart();
						player_animation_shot++;
						if (player_animation_shot == 3)
						{
							player_animation_shot = 0;
							shooting = 0;
							bullet_counter++;
						}
						player_animation_legs++;
						if (player_animation_legs == 5)
						{
							player_animation_legs = 0;
						}
					}

					PlayerMoveLegs_sprite.setTextureRect(IntRect(player_animation_legs * 20, 0, 20, 20));
					PlayerMoveLegs_sprite.setScale(1.3, 1.3);
					playerStaple_sprite.setTexture(PlayerShot);
					playerStaple_sprite.setTextureRect(IntRect(54.3 * player_animation_shot, 0, 54.3, 23));
					
				}
				if (animation_clock.getElapsedTime().asSeconds() > 0.15)
				{
					animation_clock.restart();
					
					player_animation_legs++;
					if (player_animation_legs == 5)
					{
						player_animation_legs = 0;
					}
				}
				//reload &moving right
				if (bullet_counter >= 11)
				{
					if (animation_clock.getElapsedTime().asSeconds() > 0.15)
					{
						animation_clock.restart();
						player_animation_reload++;
						player_animation_reload %= 18;

					}
					playerStaple_sprite.setTexture(PlayerReloading);
					playerStaple_sprite.setTextureRect(IntRect(player_animation_reload * 39, 0, 39, 31));
					if (player_animation_reload == 17)
					{
						bullet_counter = 0;
					}
				}
				
				PlayerMoveLegs_sprite.setTextureRect(IntRect(player_animation_legs * 20, 0, 20, 20));
				PlayerMoveLegs_sprite.setScale(1.3, 1.3);
				playerStaple_sprite.setScale(1, 1);

				PlayerMoveLegs_sprite.move(Vector2f(xaxis_move, 0));
				playerStaple_sprite.move(Vector2f(xaxis_move, 0));
			 }
			//moving left
			else if (Keyboard::isKeyPressed(Keyboard::A)&&alive ==1)
			{
				PlayerMoveLegs_sprite.setTexture(PlayerMoveLegs);
				playerStaple_sprite.setTexture(playerStaple);
				playerStaple_sprite.setTextureRect(IntRect(player_animation_staple * 32.75, 0, 32.75, 29));
				playerStaple_sprite.setPosition(PlayerMoveLegs_sprite.getPosition().x, 0);
				map.restart();

				if (Keyboard::isKeyPressed(Keyboard::F) && Slashing == 0 &&alive ==1)
				{

					playerStaple_sprite.setPosition(PlayerMoveLegs_sprite.getPosition().x + 20, -16);
					map.restart();
					if (animation_clock.getElapsedTime().asSeconds() > 0.15)
					{
						animation_clock.restart();
						player_animation_slashing++;
						player_animation_slashing %= 6;
					}
					playerStaple_sprite.setTexture(PLayerSlashing);
					playerStaple_sprite.setTextureRect(IntRect(43.8 * player_animation_slashing, 0, 43.8, 45));
					Slashing = 1;
				}
				else if (Slashing == 1)
				{
					PlayerMoveLegs_sprite.setTexture(PlayerMoveLegs);
					playerStaple_sprite.setTexture(PLayerSlashing);
					playerStaple_sprite.setPosition(PlayerMoveLegs_sprite.getPosition().x + 20, -16);
					if (animation_clock.getElapsedTime().asSeconds() > 0.15)
					{
						animation_clock.restart();
						player_animation_slashing++;
						if (player_animation_slashing == 6)
						{
							player_animation_slashing = 0;
							Slashing = 0;
						}
						player_animation_legs++;
						if (player_animation_legs == 5)
						{
							player_animation_legs = 0;
						}
					}
					playerStaple_sprite.setTextureRect(IntRect(43.8 * player_animation_slashing, 0, 43.8, 45));
					PlayerMoveLegs_sprite.setTextureRect(IntRect(player_animation_legs * 20, 0, 20, 20));
					PlayerMoveLegs_sprite.setScale(-1.3, 1.3);

				}

				if (Keyboard::isKeyPressed(Keyboard::X) && shooting == 0 &&alive ==1&&bullet_counter<11)
				{
					player_animation_reload = 0;
					bullet_counter++;
					playerStaple_sprite.setPosition(PlayerMoveLegs_sprite.getPosition().x, 0);
					if (animation_clock.getElapsedTime().asSeconds() > 0.15)
					{
						animation_clock.restart();
						player_animation_shot++;
						player_animation_shot %= 3;
					}
					playerStaple_sprite.setTexture(PlayerShot);
					playerStaple_sprite.setTextureRect(IntRect(54.3 * player_animation_shot, 0, 54.3, 23));
					shooting = 1;

				}
				else if (shooting == 1 && bullet_counter < 11)
				{
					playerStaple_sprite.setPosition(PlayerMoveLegs_sprite.getPosition().x, 0);
					if (animation_clock.getElapsedTime().asSeconds() > 0.15)
					{
						animation_clock.restart();
						player_animation_shot++;
						if (player_animation_shot == 3)
						{
							player_animation_shot = 0;
							shooting = 0;
							

						}
						player_animation_legs++;
						if (player_animation_legs == 5)
						{
							player_animation_legs = 0;
						}
					}

					PlayerMoveLegs_sprite.setTextureRect(IntRect(player_animation_legs * 20, 0, 20, 20));
					PlayerMoveLegs_sprite.setScale(-1.3, 1.3);
					playerStaple_sprite.setTexture(PlayerShot);
					playerStaple_sprite.setTextureRect(IntRect(54.3 * player_animation_shot, 0, 54.3, 23));
				}
				if (animation_clock.getElapsedTime().asSeconds() > 0.15)
				{
					animation_clock.restart();

					player_animation_legs++;
					if (player_animation_legs == 5)
					{
						player_animation_legs = 0;
					}
				}

				PlayerMoveLegs_sprite.setTextureRect(IntRect(player_animation_legs * 20, 0, 20, 20));
				PlayerMoveLegs_sprite.setScale(-1.3, 1.3);
				playerStaple_sprite.setScale(-1, 1);

				PlayerMoveLegs_sprite.move(Vector2f(-xaxis_move, 0));
				playerStaple_sprite.move(Vector2f(-xaxis_move, 0));
			}
			//slashing
			else if (Keyboard::isKeyPressed(Keyboard::F) && Slashing == 0 && alive ==1)
			{
			playerStaple_sprite.setPosition(PlayerMoveLegs_sprite.getPosition().x, -16);
				map.restart();
				if (animation_clock.getElapsedTime().asSeconds() > 0.1)
				{
					animation_clock.restart();
					player_animation_slashing++;
					player_animation_slashing %= 6;
				}
				playerStaple_sprite.setTexture(PLayerSlashing);
				playerStaple_sprite.setTextureRect(IntRect(43.8 * player_animation_slashing, 0, 43.8, 45));
				Slashing = 1;
			}
			else
			{
				
				playerStaple_sprite.setPosition(PlayerMoveLegs_sprite.getPosition().x, 0);
				playerStaple_sprite.setTexture(playerStaple);
				playerStaple_sprite.setTextureRect(IntRect(player_animation_staple * 32.75, 0, 32.75, 29));

			}
			if (Slashing == 1)
			{
				playerStaple_sprite.setPosition(PlayerMoveLegs_sprite.getPosition().x, -16);
				if (animation_clock.getElapsedTime().asSeconds() > 0.1)
				{
					animation_clock.restart();
					player_animation_slashing++;
					if (player_animation_slashing == 6)
					{
						player_animation_slashing = 0;
						Slashing = 0;
					}
				}
				playerStaple_sprite.setTexture(PLayerSlashing);
				playerStaple_sprite.setTextureRect(IntRect(43.8 * player_animation_slashing, 0, 43.8, 45));
			
			}
	        //shooting
			else if (Keyboard::isKeyPressed(Keyboard::X) && shooting == 0 && alive ==1 && bullet_counter < 11)
			{
				player_animation_reload = 0;
				bullet_counter++;
				map.restart();
				if (animation_clock.getElapsedTime().asSeconds() > 0.15)
				{
					animation_clock.restart();
					player_animation_shot++;
					player_animation_shot %= 3;
				}
				playerStaple_sprite.setTexture(PlayerShot);
				playerStaple_sprite.setTextureRect(IntRect(54.3 * player_animation_shot, 0, 54.3, 23));
				shooting = 1;
			}
			else
			{
							
				playerStaple_sprite.setPosition(PlayerMoveLegs_sprite.getPosition().x, 0);
				playerStaple_sprite.setTexture(playerStaple);
				playerStaple_sprite.setTextureRect(IntRect(player_animation_staple * 32.75, 0, 32.75, 29));

			}
			if (shooting == 1 && bullet_counter < 11)
			{
				if (animation_clock.getElapsedTime().asSeconds() > 0.15)
				{
					animation_clock.restart();
					player_animation_shot++;
					if (player_animation_shot == 3)
					{
						player_animation_shot = 0;
						shooting = 0;
					}
				}
				playerStaple_sprite.setTexture(PlayerShot);
				playerStaple_sprite.setTextureRect(IntRect(54.3 * player_animation_shot, 0, 54.3, 23));
			}
				//afk		
			if (event.KeyReleased && alive==1)
			{
			
				if (time.asSeconds() >= 5)
				{
					if (animation_clock.getElapsedTime().asSeconds() > 0.15)
					{
						animation_clock.restart();
						player_animation_afk_top++;
						player_animation_afk_top %= 34;
						player_animation_afk_bot++;
						player_animation_afk_bot %= 4;
					}					
					playerStaple_sprite.setTexture(PlayerAFKTop);
					playerStaple_sprite.setTextureRect(IntRect(player_animation_afk_top * 32.5, 0, 32.5, 32));
					PlayerMoveLegs_sprite.setTexture(PlayerAFKBot);
					PlayerMoveLegs_sprite.setTextureRect(IntRect(player_animation_afk_bot * 23.8, 0, 23.8, 16));					
				}				

			}
			//dying
			if (Keyboard::isKeyPressed(Keyboard::K))
			{
				alive=0;
			}
			if (alive == 0)
			{
				playerdying_sprite.setPosition(playerStaple_sprite.getPosition().x, playerStaple_sprite.getPosition().y);
				if (animation_clock.getElapsedTime().asSeconds() > 0.15)
				{
					animation_clock.restart();
					player_animation_dying++;
					if (player_animation_dying==19)
					{
						player_animation_dying = 19;
					}
					playerdying_sprite.setTextureRect(IntRect(player_animation_dying * 38, 0, 38, 40));
					
				}
			}

			//realoding

			if (bullet_counter >= 11 &&reload==0)
			{
				map.restart();
				if (animation_clock.getElapsedTime().asSeconds() > 0.1)
				{
					animation_clock.restart();
					player_animation_reload++;
					player_animation_reload %= 18;

				}
				playerStaple_sprite.setTexture(PlayerReloading);
				playerStaple_sprite.setTextureRect(IntRect(player_animation_reload * 39, 0, 39, 31));
				if (player_animation_reload==17)
				{
					bullet_counter = 0;
				}
				reload = 1;
			}		
			if (reload==1)
			{
				if (animation_clock.getElapsedTime().asSeconds() > 0.1)
				{
					animation_clock.restart();
					player_animation_reload++;
					if (player_animation_reload==18)
					{
						player_animation_reload = 0;
						reload = 0;
					}

				}
				playerStaple_sprite.setTexture(PlayerReloading);
				playerStaple_sprite.setTextureRect(IntRect(player_animation_reload * 39, 0, 39, 31));
				if (player_animation_reload == 17)
				{
					
					bullet_counter = 0;
				}
			}
			//gogo

			if (animation_clockV2.getElapsedTime().asSeconds() > 0.1)
			{
				animation_clockV2.restart();
				GOGO_animation++;
				GOGO_animation %= 16;

			}
			GOGO_sprite.setTextureRect(IntRect(GOGO_animation * 32.93, 0, 32.93, 31));

			//sandbags
			if (Keyboard::isKeyPressed(Keyboard::P)&&sandbag_counter<4&& sandbag_collision==0)
			{
				
				if (animation_clockV3.getElapsedTime().asSeconds() > 0.03)
				{
					animation_clockV3.restart();
					sandbags_animation++;
					sandbags_animation %= 17;
				}
				SandBag_Sprite.setTexture(SandBag);
				SandBag_Sprite.setTextureRect(IntRect(sandbags_animation * 54.58, 0, 54.58, 64));
				sandbag_collision = 1;
			}
			if (sandbag_collision==1 && sandbag_counter < 4)
			{
				if (animation_clockV3.getElapsedTime().asSeconds() > 0.03)
				{
					animation_clockV3.restart();
					sandbags_animation++;
					if (sandbags_animation==17)
					{
						sandbags_animation = 0;
						sandbag_collision = 0;
						sandbag_counter++;
					}
				}
				SandBag_Sprite.setTexture(SandBag);
				SandBag_Sprite.setTextureRect(IntRect(sandbags_animation * 54.58, 0, 54.58, 64));			
			}
			if (sandbag_counter==3 && sandbagEX_collision==0)
			{
				if (animation_clockV3.getElapsedTime().asSeconds() > 0.1)
				{
					animation_clockV3.restart();
					sandbagsEX_animation++;
					sandbagsEX_animation %= 18;
				}
				SandBag_Sprite.setPosition(200, 150);
				SandBag_Sprite.setTexture(SandBagEX);
				SandBag_Sprite.setTextureRect(IntRect(sandbagsEX_animation * 83.3, 0, 83.3, 123));
				sandbagEX_collision = 1;
			}
			if (sandbagEX_collision==1&& sandbag_counter == 3)
			{
				if (animation_clockV3.getElapsedTime().asSeconds() > 0.1)
				{
					animation_clockV3.restart();
					sandbagsEX_animation++;
					if (sandbagsEX_animation==18)
					{						
						sandbagEX_collision = 0;
						SandBag_Sprite.setPosition(-100, -100);
					}
				}
				SandBag_Sprite.setPosition(200, 150);
				SandBag_Sprite.setTexture(SandBagEX);
				SandBag_Sprite.setTextureRect(IntRect(sandbagsEX_animation * 83.3, 0, 83.3, 123));
			}
			 //enemy!!
			if (enemyv1_alive==1&& EnemyV1Alive_sprite.getPosition().x-playerStaple_sprite.getPosition().x >=200)
			{
				EnemyV1Alive_sprite.setTexture(EnemyV1Run);
				if (animation_clockV5.getElapsedTime().asSeconds() > 0.15)
				{
					animation_clockV5.restart();
					enemyv1_animation_run++;
					enemyv1_animation_run %= 12;					
				}
				EnemyV1Alive_sprite.setTextureRect(IntRect(enemyv1_animation_run * 45, 0, 45, 40));
				EnemyV1Alive_sprite.move(-1, 0);
			}
			if(enemyv1_alive == 1&& EnemyV1Alive_sprite.getPosition().x - playerStaple_sprite.getPosition().x < 200 )
			{
				EnemyV1Alive_sprite.setTexture(EnemyV1Shoot);
				if (animation_clockV5.getElapsedTime().asSeconds() > 0.2)
				{
					animation_clockV5.restart();
					enemyv1_animation_shoot++;
					enemyv1_animation_shoot %= 3;

				}
				EnemyV1Alive_sprite.setTextureRect(IntRect(enemyv1_animation_shoot * 64, 0, 64, 44));
				
			}if (enemyv1_alive == 1 && enemyV1 == 0 && EnemyV1Alive_sprite2.getPosition().x - playerStaple_sprite.getPosition().x > 300)
			{
				EnemyV1Alive_sprite2.setTexture(EnemyV1Run);
				if (animation_clockV6.getElapsedTime().asSeconds() > 0.15)
				{
					animation_clockV6.restart();
					enemyv1_animation_run++;
					enemyv1_animation_run %= 12;
				}
				EnemyV1Alive_sprite2.setTextureRect(IntRect(enemyv1_animation_run * 45, 0, 45, 40));
				EnemyV1Alive_sprite2.move(-1, 0);
				
			}
			if (enemyv1_alive == 1 && EnemyV1Alive_sprite2.getPosition().x - playerStaple_sprite.getPosition().x < 300 &&  enemyV1 == 0)
			{
				EnemyV1Alive_sprite2.setTexture(EnemyV1sceared);
				if (animation_clockV6.getElapsedTime().asSeconds() > 0.15)
				{
					animation_clockV6.restart();
					enemyV1_animation_sceared++;
					enemyV1_animation_sceared %= 14;

				}
				EnemyV1Alive_sprite2.setTextureRect(IntRect(enemyV1_animation_sceared * 30, 0, 30, 39));
				EnemyV1Alive_sprite2.move(2, 0);
			}
			if (enemyv1_alive == 1 && EnemyV2Alive_sprite.getPosition().x - playerStaple_sprite.getPosition().x > 200)
			{
				EnemyV2Alive_sprite.setTexture(EnemyV2Run);
				if (animation_clockV7.getElapsedTime().asSeconds() > 0.15)
				{
					animation_clockV7.restart();
					enemyv2_animation_run++;
					enemyv2_animation_run %= 12;
				}
				EnemyV2Alive_sprite.setTextureRect(IntRect(enemyv2_animation_run * 42, 0, 42, 38));
				EnemyV2Alive_sprite.move(-1, 0);
			}
			if (enemyv1_alive == 1 && EnemyV2Alive_sprite.getPosition().x - playerStaple_sprite.getPosition().x < 200)
			{
				EnemyV2Alive_sprite.setTexture(EnemyV2Shoot);
				if (animation_clockV7.getElapsedTime().asSeconds() > 0.2)
				{
					animation_clockV7.restart();
					enemyv2_animation_shoot++;
					enemyv2_animation_shoot %= 10;

				}
				EnemyV2Alive_sprite.setTextureRect(IntRect(enemyv2_animation_shoot * 50, 0, 50, 45));

			}
			//npc's





			window.clear();
			if (alive==1)
			{
			window.draw(PlayerMoveLegs_sprite);
			window.draw(playerStaple_sprite);
			}
			if (alive==0)
			{
			window.draw(playerdying_sprite);
			}
			if (enemyv1_alive==1)
			{
			window.draw(EnemyV1Alive_sprite2);
			window.draw(EnemyV1Alive_sprite);
			window.draw(EnemyV2Alive_sprite);
			}
			if (enemyv1_alive == 0)
			{
				
				window.draw(EnemyV1Dead_sprite);
			}
			window.draw(GOGO_sprite);
			window.draw(SandBag_Sprite);
			window.setFramerateLimit(60);
			window.display();

		}
		if (Keyboard::isKeyPressed(Keyboard::Tab))
			phase = -1;

		

	}
	

}
void  options(RenderWindow& window, Event& event,int &phase) 
{
	Mouse mouse;
	
	//text
	Font font1;
	font1.loadFromFile("PiloEscribanoPublico-Regular.ttf");
	Text text[3];
	for (int i = 0; i < 3; i++)
	{
		text[i].setFont(font1);
		text[i].setFillColor(Color::Black);
	}	
	
	text[0].setCharacterSize(70);
	text[0].setPosition(75,45);
	text[0].setString("Movements");

	text[1].setCharacterSize(50);
	text[1].setPosition(65, 180);
	text[1].setString("A  to move Left ,,, D  to move Right \n SPACE  to Jump ,,, X  to Shoot");

	text[2].setCharacterSize(70);
	text[2].setPosition(75, 350);
	text[2].setString("volume");
	



	Texture options;
	options.loadFromFile("options.jpg");
	Sprite options_sprite;
	options_sprite.setTexture(options);
	options_sprite.setScale(0.625, 0.585);
	while (window.pollEvent(event))
	{
		cout << mouse.getPosition().x << "  " << mouse.getPosition().y << endl;
		if (event.type == event.Closed)
			window.close();
		
		window.clear();
		window.draw(options_sprite);
		for (int i = 0; i < 3; i++)
		{
			window.draw(text[i]);			
		}	
		window.display();
	}
	if (Keyboard::isKeyPressed(Keyboard::Tab))
		phase = -1;
}

	