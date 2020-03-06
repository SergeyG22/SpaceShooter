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

void starship::mouse_event(sf::RenderWindow& w,sf::Event& e,starship& galactic)
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

		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Space)
			{
				guns.push_back(std::shared_ptr<bullet>(new bullet(galactic)));
				galactic.sound_laser.play();
			}
		}
}

void starship::touch_event(sf::RenderWindow& w, sf::Event& e,starship& galactic)
{
	
	sf::Vector2i PixelPosition = sf::Touch::getPosition(0,w);
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

	if (e.type == sf::Event::TouchBegan)
					{
						 if (galactic.sprite_sh.getGlobalBounds().contains(pos.x, pos.y))
						 {
							guns.push_back(std::shared_ptr<bullet>(new bullet(galactic)));
							galactic.sound_laser.play();
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

void fone_space::update(float& t)
{
	sprite_space_first.move(sf::Vector2f(0, 0.05 * t));
	sprite_space_second.move(sf::Vector2f(0, 0.05 * t));
	if (sprite_space_first.getPosition().y > 1519)
	{
		sprite_space_first.setPosition(0, -1519);
	}

	if (sprite_space_second.getPosition().y > 1519)
	{
		sprite_space_second.setPosition(0, -1519);
	}

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

asteroid::asteroid(float x_position,float y_position,float r) :frame(0),x(x_position),y(y_position),rotate(r)
{

	std::mt19937 mt(rd());
	std::uniform_real_distribution<double>distA(0,5);          // текстура обьекта
	std::uniform_real_distribution<double>distB(0.5, 0.9);    // размер обьекта
	std::uniform_real_distribution<double>distC(0.05, 0.1);   // скорость обьекта
	std::uniform_real_distribution<double>distE(-0.2, 0.2);   // угол направления движения
	speed = float(distC(mt));
	angle_of_movement = distE(mt);
	
	switch ((int)distA(mt))
	{
	case 0: 
	{	
		if (!texture_stone.loadFromFile("asteroid_version_1a.png")) { std::cout << "texture loading error\n"; }
		break;
	}
	case 1:
	{   
		if (!texture_stone.loadFromFile("asteroid_version_1b.png")) { std::cout << "texture loading error\n"; }
		break;
	}
	case 2:
	{   if (!texture_stone.loadFromFile("asteroid_version_1c.png")) {  std::cout << "texture loading error\n"; }
		break;
	}
	case 3:
	{   if (!texture_stone.loadFromFile("asteroid_version_2a.png")) { std::cout << "texture loading error\n"; }
	break;
	}
	case 4:
	{   if (!texture_stone.loadFromFile("asteroid_version_2b.png")) { std::cout << "texture loading error\n"; }
	break;
	}


	}
	float size = float(distB(mt));
	sprite_stone.setScale(size, size);
	sprite_stone.setTexture(texture_stone);
	sprite_stone.setTextureRect(sf::IntRect(0,0,100,100));
	sprite_stone.setPosition(x,y);
}

void asteroid::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(sprite_stone);
}

void asteroid::update(float& time)
{
	frame += rotate * time;                         // rotate 0.009 в идеале
	if (frame > 20) { frame -= 20; }
	sprite_stone.setTextureRect(sf::IntRect(100 * int(frame), 0,100, 100));
}

explosions::explosions(float a,float b):frame(0)
{
	
	if (!explosions_t.loadFromFile("type_A.png")) 
	{ 
		std::cout << "texture loading error\n";
	}
	explosions_s.setTexture(explosions_t);
	explosions_s.setTextureRect(sf::IntRect(0, 0, 51, 50));
	explosions_s.setPosition(a, b);
}

bool explosions::update(float& t,bool& selector)
{
	if (selector)
	{
		frame += 0.01 * t;
		if (frame > 20) { frame -= 20;
		selector = false;
		}
		explosions_s.setTextureRect(sf::IntRect(50 * int(frame), 0, 51, 50));
	}
	return selector;
}



void explosions::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(explosions_s);
}