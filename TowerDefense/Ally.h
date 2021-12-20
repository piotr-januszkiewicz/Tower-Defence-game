#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;

//polymorphic class with virtual method used for creating allies texture
class Ally
{
public:
		
	Sprite build(Texture & AllyTexture, int X, int Y);
	virtual Texture create_ally_texture() = 0;
};

//derived class: active version of an ally
class Ally_Active : public Ally
{
public:
	int Money_Worth;
	int Ally_Attack_Power;
	int X_Coordinate, Y_Coordinate;
	
	Ally_Active(int Power, int X, int Y);
	
	//creating allies texture. virtual method
	virtual Texture create_ally_texture();

	//attack method
	void attack(Enemy & enemy);
};

//derived class: passive version of an ally
class Ally_Passive : public Ally
{
public:
	int Money_Worth;
	int Ally_Production;
	int X_Coordinate, Y_Coordinate;
	
	Ally_Passive(int Production, int X, int Y);

	//creating allies texture. virtual method
	virtual Texture create_ally_texture();

}; 