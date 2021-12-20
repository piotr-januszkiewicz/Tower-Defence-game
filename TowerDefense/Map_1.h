#pragma once
#include <iostream>
#include <time.h>
#include <fstream>
#include <conio.h>
#include <vector>
#include <deque>
#include <sstream>
#include <list>
#include <chrono>
#include <math.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Ally.h"
#include "Player.h"

class Map_1
{
public:

void DisplayMap_1(Player & player, std::vector<Ally_Active> & ActiveAlly, std::vector<Ally_Passive> & PassiveAlly);

//creating Map sprite
Texture create_map1_texture();
Sprite create_map1_sprite(Texture & Map_1_Texture);

//overloaded function responsible for filling vectors with given data. Used e.g. to create many Enemies with different attributes 
template <class vector_type, class data_type>
void fill_vector(std::vector<vector_type> & Vector, int DataCount, data_type Data1, data_type Data2);

template <class vector_type, class data_type>
void fill_vector(std::vector<vector_type> & Vector, int DataCount, data_type Data);

template <class vector_type>
void fill_vector(std::vector<vector_type> & Vector, int DataCount);

//creates new ally. Could be used in future to create many more types of active allies
template <class entity_type>
void create_ally_entity(Event & event, int X_Coord, int Y_Coord, std::deque<Sprite> & sprites, std::vector<entity_type> & ally, Player & player, Texture & texture, Text & playersMoney);

//function calculating distance between ally and enemy
void value(float & DistanceAllyToEnemy, std::pair<Enemy, Ally_Active> Pair);

//used to load all coordinates needed for enemies to move
void take_coordinates_from_file(std::vector<int> & Turning_Directions, std::vector<int> & Coordinates);

//first text configuration. Include setting size, position and color of text
void configure_text(Text * textArray);

//function destroying ally
template <class Ally_Type>
void will_to_destroy(Event event, Player & player, std::vector<Ally_Type> & Objects, std::deque<Sprite> & Sprites);

//used to create enemies objects
void spawn_enemies(Player & player, std::vector<int> & Variables, std::vector<Enemy> & Enemies, std::vector<Sprite> & EnemySprites, std::vector<bool> & WantToDraw, Texture & EnemyTexture);

//saves game progress. For now it only saves round, hp, and money(both made from destroying enemies/winning rounds and allies worth)
void save_game(Player player, std::vector<Ally_Active> ActiveAlly, std::vector<Ally_Passive> PassiveAlly);

//proper function used indirect for attacking enemies
void attack_enemies(std::vector<Ally_Active> & ActiveAlly, std::vector<bool>EnemyInRange, std::vector<Enemy> & Enemies, std::vector<int> EnemiesForEachAlly);

//checking if round is still going
void is_round_ongoing(std::vector<bool>WantToDraw, std::shared_ptr<bool> & IsRoundOngoing);

//rewarding player and preparing game for next round. 
std::chrono::high_resolution_clock::time_point configure_for_next_round(Player & player, Text & PlayersMoney_Display, std::shared_ptr<bool> & IsRoundOngoing);

};



