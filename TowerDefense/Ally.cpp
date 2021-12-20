#include "Ally.h"

Sprite Ally::build(Texture & AllyTexture, int X, int Y)
{
	Sprite AllySprite;
	AllySprite.setTexture(AllyTexture);

	AllySprite.setPosition(X, Y);
	return AllySprite;
}

Ally_Active::Ally_Active(int Power, int X, int Y)
{
	this->Ally_Attack_Power = Power;
	this->X_Coordinate = X;
	this->Y_Coordinate = Y;
	this->Money_Worth = 200;
}

Ally_Passive::Ally_Passive(int Production, int X, int Y)
{
	this->Ally_Production = Production;
	this->X_Coordinate = X;
	this->Y_Coordinate = Y;
	this->Money_Worth = 150;
}


Texture Ally_Active::create_ally_texture()
{
	Image Active;
	Active.loadFromFile("active_unit.png");
	Texture ActiveTexture;
	ActiveTexture.loadFromImage(Active);

	return ActiveTexture;
}

void Ally_Active::attack(Enemy & enemy)
{
	enemy.Enemy_Healt_Points -= this->Ally_Attack_Power;
}

Texture Ally_Passive::create_ally_texture()
{
	Image Passive;
	Passive.loadFromFile("passive_unit.png");
	Texture PassiveTexture;
	PassiveTexture.loadFromImage(Passive);

	return PassiveTexture;
}

