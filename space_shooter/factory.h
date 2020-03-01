#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class starship:public sf::Drawable
{
	sf::Texture texture_sh;
	sf::SoundBuffer laser_buffer;
	float x;
	float y;
	float dX;
	bool move;	
public:
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;	
	void mouse_event(sf::RenderWindow&,sf::Event&);
	void touch_event(sf::RenderWindow&,sf::Event&);
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
	sf::Sprite sprite_stone;
	float frame;
public:
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;
	void update(float&);
	asteroid();
};