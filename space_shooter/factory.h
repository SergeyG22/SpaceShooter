#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <chrono>
#include <random>

class bullet;

class starship:public sf::Drawable
{
	sf::Texture texture_sh;
	sf::SoundBuffer laser_buffer;
	float x;
	float y;
	float dX;
	bool move;	
public:
	std::list<std::shared_ptr<bullet>>guns;
	std::list<std::shared_ptr<bullet>>::iterator it = guns.begin();
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;	
	void mouse_event(sf::RenderWindow&,sf::Event&,starship&);
	void touch_event(sf::RenderWindow&,sf::Event&,starship&);
	sf::Sprite sprite_sh;
	sf::Sound sound_laser;
	starship();	
};

class fone_space :public sf::Drawable
{
	sf::Texture texture_space_first;
	sf::Texture texture_space_second;
public:
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;
	sf::Sprite sprite_space_first;
	sf::Sprite sprite_space_second;
	fone_space();
	void update(float&);
};

class bullet :public sf::Drawable
{
	sf::Texture texture_bullet;
	starship* p;
public:
	sf::Sprite sprite_bullet;
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;
	bullet(starship&);
};

class asteroid:public sf::Drawable
{
	sf::Texture texture_stone;	
	float frame;
	float rotate;                //speed of rotate 
	float x;
	float y;
	std::random_device rd;
public:
	std::list<std::shared_ptr<asteroid>>asteroid_field;
	std::list<std::shared_ptr<asteroid>>::iterator iterator = asteroid_field.begin();
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;
	sf::Sprite sprite_stone;
	void update(float&);
	asteroid(float,float,float);
	asteroid():x(300),y(800),frame(0),rotate(0.009){ };
};