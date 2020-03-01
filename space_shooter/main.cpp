#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "factory.h"
#include <list>

int main()
{
	sf::RenderWindow window(sf::VideoMode(720, 1520), "space shooter");
	fone_space stars;
	
	starship galactic;
	bullet bullet_v1(galactic);
	sf::Clock clock;
		
	std::list<std::shared_ptr<bullet>>guns;
	auto it = guns.begin();
	

	while (window.isOpen())
	{
		sf::Event event;
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		while (window.pollEvent(event))
		{
			sf::Vector2i PixelPosition = sf::Touch::getPosition(1, window);
			sf::Vector2f pos = window.mapPixelToCoords(PixelPosition);
			
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
					{
						if (event.key.code == sf::Keyboard::Space)
						{					
							guns.push_back(std::shared_ptr<bullet>(new bullet(galactic)));
							galactic.sound_laser.play();
						}
					}
			if (event.type == sf::Event::TouchBegan)
		           	{
				         if (galactic.sprite_sh.getGlobalBounds().contains(pos.x, pos.y))
				         {
				           	guns.push_back(std::shared_ptr<bullet>(new bullet(galactic)));
				         }
		        	}
			
		     	galactic.mouse_event(window,event);
				galactic.touch_event(window,event);								
		}
		window.clear();
		window.draw(stars);
		for (it = guns.begin(); it != guns.end();) 
		    {			
				window.draw((*it)->sprite_bullet);
				(*it)->sprite_bullet.move(sf::Vector2f(0, -1.5*time));
				if ((*it)->sprite_bullet.getPosition().y < 0)         //1
				{					
					it = guns.erase(it);                              //2
				}
				else
				{
					it++;                                             //3
				}
			}
	
			stars.sprite_space_first.move(sf::Vector2f(0, 0.05 * time));
			stars.sprite_space_second.move(sf::Vector2f(0, 0.05 * time));
			if (stars.sprite_space_first.getPosition().y > 1519)
			{
				stars.sprite_space_first.setPosition(0,-1519);
			}

			if (stars.sprite_space_second.getPosition().y > 1519)
			{
				stars.sprite_space_second.setPosition(0,-1519);
			}


		window.draw(galactic);		
		window.display();

	}

	return 0;
}













//=====================
//	std::list<bullet>guns;
//	std::list<bullet>::iterator it = guns.begin();
//	std::list<bullet*>guns;
//	std::list<bullet*>::iterator it = guns.begin();
//=====================
//	guns.push_back(bullet(galactic));
//	guns.push_back(new bullet(galactic));	