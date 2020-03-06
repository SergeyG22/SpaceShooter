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
	explosions explosion;
	sf::Clock clock1;
	sf::Clock clock2;
	int the_time_between = (int)random_number_generator(5.0, 10.0);
	
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

				for (stone_version1.iterator = stone_version1.asteroid_field.begin(); stone_version1.iterator != stone_version1.asteroid_field.end();)
				{
					if ((*galactic.it)->sprite_bullet.getGlobalBounds().intersects((*stone_version1.iterator)->sprite_stone.getGlobalBounds()))
					{
					    (*galactic.it)->bullet_visibility = true;
						explosion.list_e.push_back(std::shared_ptr<explosions>(new explosions((*stone_version1.iterator)->sprite_stone.getPosition().x,(*stone_version1.iterator)->sprite_stone.getPosition().y)));	
						stone_version1.iterator = stone_version1.asteroid_field.erase(stone_version1.iterator);
						
					}
					else
					{					     	
			    		stone_version1.iterator++;					
					}
				}
				
						
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
			for (int i = 0; i < (int)random_number_generator(1,8);++i)
			{				
				stone_version1.asteroid_field.push_back(std::shared_ptr<asteroid>(new asteroid(random_number_generator(100, 620.0), 50, (float)random_number_generator(0.009, 0.03))));
			}
			the_time_between = (int)random_number_generator(5.0, 10.0);
			clock2.restart();
		}


		for (stone_version1.iterator = stone_version1.asteroid_field.begin(); stone_version1.iterator != stone_version1.asteroid_field.end();)
		{
			window.draw((*stone_version1.iterator)->sprite_stone);
			(*stone_version1.iterator)->update(time1);
			(*stone_version1.iterator)->sprite_stone.move(sf::Vector2f((*stone_version1.iterator)->angle_of_movement, (*stone_version1.iterator)->speed * time1));

			if ((*stone_version1.iterator)->sprite_stone.getPosition().y > 1520)
			{
				stone_version1.iterator = stone_version1.asteroid_field.erase(stone_version1.iterator);
				stone_version1.asteroid_field.push_back(std::shared_ptr<asteroid>(new asteroid(random_number_generator(100, 620.0), 50, (float)random_number_generator(0.009, 0.03))));
			}
			if ((*stone_version1.iterator)->sprite_stone.getPosition().x < 0)
			{
				stone_version1.iterator = stone_version1.asteroid_field.erase(stone_version1.iterator);
				stone_version1.asteroid_field.push_back(std::shared_ptr<asteroid>(new asteroid(random_number_generator(100, 620.0), 50, (float)random_number_generator(0.009, 0.03))));
			}
			if ((*stone_version1.iterator)->sprite_stone.getPosition().x > 720)
			{
				stone_version1.iterator = stone_version1.asteroid_field.erase(stone_version1.iterator);
				stone_version1.asteroid_field.push_back(std::shared_ptr<asteroid>(new asteroid(random_number_generator(100, 620.0), 50, (float)random_number_generator(0.009, 0.03))));
			}
			else
			{
				stone_version1.iterator++;
			}
		}

		for (explosion.it_explosions = explosion.list_e.begin(); explosion.it_explosions != explosion.list_e.end();)
		{
			if ((*explosion.it_explosions)->selector)   
			{
				(*explosion.it_explosions)->update(time1, (*explosion.it_explosions)->selector);
				window.draw((*explosion.it_explosions)->explosions_s);				
			}

			if ((*explosion.it_explosions)->selector == false)
			{
				explosion.it_explosions = explosion.list_e.erase(explosion.it_explosions);
			}
			else
			{
				explosion.it_explosions++;
			}
		}

		for (galactic.it = galactic.guns.begin(); galactic.it != galactic.guns.end();)
		{
			if ((*galactic.it)->bullet_visibility)
			{
				galactic.it = galactic.guns.erase(galactic.it);
			}
			else
			{
				galactic.it++;
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










