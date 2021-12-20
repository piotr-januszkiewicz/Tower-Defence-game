#include "Enemy.h"


Enemy::Enemy(double hp, double speed)
{
	Enemy_Healt_Points = hp;
	Enemy_Movement_Speed = speed;  
}


Sprite Enemy::enemy_spawn(Texture & EnemyTexture)
{
	Sprite EnSprite;
	EnSprite.setTexture(EnemyTexture);
	EnSprite.setPosition(219, 277);
	this->X = 219;
	this->Y = 277;

	return EnSprite;
}

Texture Enemy::create_enemy_texture()
{
	Image Enem;
	Enem.loadFromFile("enemy.png");
	Enem.createMaskFromColor(Color::White);
	Texture EnemyTexture;
	EnemyTexture.loadFromImage(Enem);

	return EnemyTexture;
}


bool Enemy::move(Sprite & EnSprite, std::vector<int> Turning_Directions, std::vector<int> coordinates, int & zmienna, float deltatime, float MovementSpeed)
{
	if (Turning_Directions[zmienna] == 1)
	{
		if (EnSprite.getPosition().y < coordinates[2 * zmienna + 1])
		{
			EnSprite.move(0, MovementSpeed * deltatime);
			this->X = EnSprite.getPosition().x;
			this->Y = EnSprite.getPosition().y;
		}

		if (EnSprite.getPosition().y >= coordinates[2 * zmienna + 1] && EnSprite.getPosition().y <= coordinates[2 * zmienna + 1] + 2)
			zmienna++;
	}
	else if (Turning_Directions[zmienna] == 2)
	{
		if (EnSprite.getPosition().x > coordinates[2 * zmienna])
		{
			this->X = EnSprite.getPosition().x;
			this->Y = EnSprite.getPosition().y;
			EnSprite.move(-MovementSpeed * deltatime, 0);
		}
		if (EnSprite.getPosition().x >= coordinates[2 * zmienna] && EnSprite.getPosition().x <= coordinates[2 * zmienna] + 2)
			zmienna++;
	}
	else if (Turning_Directions[zmienna] == 3)
	{
		if (EnSprite.getPosition().y > coordinates[2 * zmienna + 1])
		{
			this->X = EnSprite.getPosition().x;
			this->Y = EnSprite.getPosition().y;
			EnSprite.move(0, -MovementSpeed * deltatime);
		}
		if (EnSprite.getPosition().y >= coordinates[2 * zmienna + 1] && EnSprite.getPosition().y <= coordinates[2 * zmienna + 1] + 2)
			zmienna++;
	}
	else if (Turning_Directions[zmienna] == 4)
	{
		if (EnSprite.getPosition().x < coordinates[2 * zmienna])
		{
			this->X = EnSprite.getPosition().x;
			this->Y = EnSprite.getPosition().y;
			EnSprite.move(MovementSpeed * deltatime, 0);
		}
		if (EnSprite.getPosition().x >= coordinates[2 * zmienna] && EnSprite.getPosition().x <= coordinates[2 * zmienna] + 2)
			zmienna++;
	}

	bool Is_End = (EnSprite.getPosition().y <= 240 && EnSprite.getPosition().x > 1360) ? true : false;
	return Is_End;
}

