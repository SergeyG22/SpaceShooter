#include "factory.h"
#include <iostream>
#include <SFML/Audio.hpp>

starship::starship():x(300), y(1000),move(false),dX(0.0)
{
	if (!texture_sh.loadFromFile("starship.png"))
	{
		std::cout << "texture loading error\n";
	}
	sprite_sh.setTexture(texture_sh);
	sprite_sh.setPosition(x,y);
	
	if (!laser_buffer.loadFromFile("laser_sound.wav"))
	{
		std::cout << "sound of laser loading error\n";
	}

	sound_laser.setBuffer(laser_buffer);
}


void starship::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
	target.draw(sprite_sh);
}

void starship::mouse_event(sf::RenderWindow& w,sf::Event& e)
{
	sf::Vector2i PixelPosition = sf::Mouse::getPosition(w);
	sf::Vector2f pos = w.mapPixelToCoords(PixelPosition);

	
		if (e.type == sf::Event::MouseButtonPressed)
		{
			if (e.key.code == sf::Mouse::Left)
			{
				if (sprite_sh.getGlobalBounds().contains(pos.x, pos.y))
				{							
						dX = pos.x - sprite_sh.getPosition().x;
						move = true;
				}
			}
		}

		if (e.type == sf::Event::MouseButtonReleased)
		{
			if (e.key.code == sf::Mouse::Left)
			{
					move = false;
			}
		}
	
		if (move)
		{
			if (pos.x > 55 && pos.x < 665)
			{
				sprite_sh.setPosition(pos.x - dX, y);
			}
		}
}

void starship::touch_event(sf::RenderWindow& w, sf::Event& e)
{
	
	sf::Vector2i PixelPosition = sf::Touch::getPosition(1,w);
	sf::Vector2f pos = w.mapPixelToCoords(PixelPosition);
	
	if (e.type == sf::Event::TouchBegan)
	{
		   
			if (sprite_sh.getGlobalBounds().contains(pos.x, pos.y))
			{				
				dX = pos.x - sprite_sh.getPosition().x;
				move = true;
			}		
	}

	if (e.type == sf::Event::TouchEnded)
	{		
			move = false;		
	}

	if (move)
	{
		if (pos.x > 55 && pos.x < 665)
		{
			sprite_sh.setPosition(pos.x - dX, y);
		}
	}

}


fone_space::fone_space()
{
	if (!texture_space_first.loadFromFile("fone_space.png"))
	{
		std::cout << "texture_first loading error\n";
	}
	sprite_space_first.setTexture(texture_space_first);

	if (!texture_space_second.loadFromFile("fone_space.png"))
	{
		std::cout << "texture_second loading error\n";
	}
	sprite_space_second.setTexture(texture_space_second);

	sprite_space_first.setPosition(0, 0);
	sprite_space_second.setPosition(0,-1519);
}



void fone_space::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
	target.draw(sprite_space_first);
	target.draw(sprite_space_second);
}

bullet::bullet(starship& a):p(nullptr)
{
	if (!texture_bullet.loadFromFile("bullet.png"))
	{
		std::cout << "texture loading error\n";
	}
	p = &a;
	sprite_bullet.setTexture(texture_bullet);
	sprite_bullet.setPosition(p->sprite_sh.getPosition().x+30, p->sprite_sh.getPosition().y+10);
}

void bullet::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(sprite_bullet);
}

