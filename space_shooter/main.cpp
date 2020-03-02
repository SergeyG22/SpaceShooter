#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <chrono>
#include <random>
#include <list>
#include "factory.h"


double random_number_generator(double, double);



int main()
{
	sf::RenderWindow window(sf::VideoMode(720, 1520), "space shooter");

	fone_space stars;	
	starship galactic;
	bullet bullet_v1(galactic);
	asteroid stone_version1;
	sf::Clock clock1;
	sf::Clock clock2;
	int the_time_between = (int)random_number_generator(5.0, 10.0);
	stone_version1.asteroid_field.push_back(std::shared_ptr<asteroid>(new asteroid(random_number_generator(100,620.0), 50, (float)random_number_generator(0.009, 0.03))));
	
	


	while (window.isOpen())
	{
		sf::Event event;
		float time1 = clock1.getElapsedTime().asMicroseconds();
		float time2 = clock2.getElapsedTime().asSeconds();
		
		time1 = time1 / 800;
		clock1.restart();
		


		while (window.pollEvent(event))
		{			
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		     	galactic.mouse_event(window,event,galactic);
				galactic.touch_event(window,event,galactic);								
		}
		window.clear();
		window.draw(stars);
		for (galactic.it = galactic.guns.begin(); galactic.it != galactic.guns.end();) 
		    {			
				window.draw((*galactic.it)->sprite_bullet);
				(*galactic.it)->sprite_bullet.move(sf::Vector2f(0, -1.5*time1));
				if ((*galactic.it)->sprite_bullet.getPosition().y < 0)         
				{					
					galactic.it = galactic.guns.erase(galactic.it);                              
				}
				else
				{
					galactic.it++;                                             
				}
			}

		if ((int)time2 == the_time_between )
		{
			for (int i = 0; i < (int)random_number_generator(1,4);++i)
			{
			//	std::cout <<"i=: " << i << '\n';
				stone_version1.asteroid_field.push_back(std::shared_ptr<asteroid>(new asteroid(random_number_generator(100, 620.0), 50, (float)random_number_generator(0.009, 0.03))));
			}
			the_time_between = (int)random_number_generator(5.0, 10.0);
			clock2.restart();
		}


		for (stone_version1.iterator = stone_version1.asteroid_field.begin(); stone_version1.iterator != stone_version1.asteroid_field.end();)
		{
			window.draw((*stone_version1.iterator)->sprite_stone);
			(*stone_version1.iterator)->update(time1);
			(*stone_version1.iterator)->sprite_stone.move(sf::Vector2f(0, random_number_generator(0.01, 0.05)* time1));			
			if ((*stone_version1.iterator)->sprite_stone.getPosition().y > 1520)
			{
				stone_version1.iterator = stone_version1.asteroid_field.erase(stone_version1.iterator);
				stone_version1.asteroid_field.push_back(std::shared_ptr<asteroid>(new asteroid(random_number_generator(100, 620.0), 50, (float)random_number_generator(0.009, 0.03))));
			}
			else
			{
				stone_version1.iterator++;
			}
		}

		stars.update(time1);
		window.draw(galactic);
		window.display();

	}

	return 0;
}

double random_number_generator(double a,double b)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double>dist(a, b);
	return dist(mt);
}










