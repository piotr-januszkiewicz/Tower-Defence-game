#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace sf;

class Enemy
{
public:
	double Enemy_Healt_Points;
	double Enemy_Movement_Speed;
	int X, Y;

	Enemy(double hp, double speed);
	
	//creating Enemy sprite
	Sprite enemy_spawn(Texture & EnemyTexture);
	Texture create_enemy_texture();

	//function responsible for making Enemy move. Also checks if object reached end of the path
	bool move(Sprite & EnSprite, std::vector<int> Turning_Directions, std::vector<int> coordinates, int & zmienna, float deltatime, float MovementSpeed);
};

