#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Map_1.h"
using namespace sf;

class Menu
{
public:
	int DisplayGameMenu();

	//function is responsible for loading save from file
	void load_from_save(Player & player, std::vector<Ally_Active> & ActiveAlly, std::vector<Ally_Passive> & PassiveAlly);

};

