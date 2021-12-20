#include "Map_1.h"

Texture Map_1::create_map1_texture()
{
	Image map1;
	map1.loadFromFile("Map_1.png");
	Texture Map_1_Texture;
	Map_1_Texture.loadFromImage(map1);
	return Map_1_Texture;
}

Sprite Map_1::create_map1_sprite(Texture & Map_1_Texture)
{
	Sprite Map_1_Sprite;
	Map_1_Sprite.setTexture(Map_1_Texture);
	return Map_1_Sprite;
}

void Map_1::take_coordinates_from_file(std::vector<int> & Turning_Directions, std::vector<int> & Coordinates)
{
	std::string Line_From_File;
	short int counter = 0;
	std::ifstream file("Map_1_Coords.txt", std::ios::in);
	if (file.good())
	{
		while (!file.eof())
		{
			getline(file, Line_From_File);
			std::size_t Pos = Line_From_File.find_first_of(',');
			while (Pos != std::string::npos)
			{
				std::string s = Line_From_File.substr(0, Pos);
				Line_From_File.erase(Line_From_File.begin(),Line_From_File.begin() + (Pos+1));
				Pos = Line_From_File.find_first_of(',');

				if(counter == 0)
					Turning_Directions.push_back(std::stoi(s));
				if (counter == 1)
					Coordinates.push_back(std::stoi(s));
			}
			counter++;
		}
	}
}

template <class vector_type, class data_type>
void Map_1::fill_vector(std::vector<vector_type> & Vector, int DataCount, data_type Data1, data_type Data2)
{
	for (int i = 0; i < DataCount; i++)
		Vector.push_back({ Data1,Data2 });
}

template <class vector_type, class data_type>
void Map_1::fill_vector(std::vector<vector_type> & Vector, int DataCount, data_type Data)
{
	for (int i = 0; i < DataCount; i++)
		Vector.push_back(Data);
}

template <class vector_type>
void Map_1::fill_vector(std::vector<vector_type> & Vector, int DataCount)
{
	for (int i = 0; i < DataCount; i++)
		Vector.push_back(0);
}

template <class entity_type>
void Map_1::create_ally_entity(Event & event, int X_Coord, int Y_Coord, std::deque<Sprite> & sprites, std::vector<entity_type> & ally, Player & player, Texture & texture, Text & playersMoney)
{
	if (event.mouseButton.button == Mouse::Left)
	{
		if (event.type == Event::MouseButtonPressed)
		{				
			entity_type newAlly({ 1,  X_Coord, Y_Coord });

			if (player.Money >= newAlly.Money_Worth)
			{
				player.Money -= newAlly.Money_Worth;
				sprites.push_back(newAlly.build(texture, X_Coord, Y_Coord));
				ally.push_back(newAlly);
			}
			else playersMoney.setFillColor(Color::Red);
		}
	}
}

void Map_1::configure_text(Text * textArray)
{
	textArray[0].setPosition(1674, 99);
	textArray[0].setCharacterSize(40);
	textArray[0].setFillColor(Color::Red);

	textArray[1].setPosition(1718, 99);
	textArray[1].setCharacterSize(40);
	textArray[1].setFillColor(Color::Red);

	textArray[2].setCharacterSize(40);
	textArray[2].setFillColor(Color::Green);
	textArray[2].setPosition(1684, 249);

	textArray[3].setCharacterSize(40);
	textArray[3].setFillColor(Color::Yellow);
	textArray[3].setPosition(1759, 340);
}

void Map_1::value(float & DistanceAllyToEnemy, std::pair<Enemy, Ally_Active> Pair)
{
	float Value = ((Pair.first.X - Pair.second.X_Coordinate) * (Pair.first.X - Pair.second.X_Coordinate)) + ((Pair.first.Y - Pair.second.Y_Coordinate) * (Pair.first.Y - Pair.second.Y_Coordinate));
	DistanceAllyToEnemy = sqrt(Value);
}

template <class Ally_Type>
void Map_1::will_to_destroy(Event event, Player & player, std::vector<Ally_Type> & Objects, std::deque<Sprite> & Sprites)
{
	for (int i = 0; i < Objects.size(); i++)
		if (event.mouseButton.x >= Objects[i].X_Coordinate && event.mouseButton.x <= (Objects[i].X_Coordinate + 100) && event.mouseButton.y >= Objects[i].Y_Coordinate && event.mouseButton.y <= (Objects[i].Y_Coordinate + 100))
		{
			player.Money += (Objects[i].Money_Worth * 3 / 4);
			Objects.erase(Objects.begin() + i);
			Sprites.erase(Sprites.begin() + i);
		}
}

void  Map_1::spawn_enemies(Player & player, std::vector<int> & Variables, std::vector<Enemy> & Enemies, std::vector<Sprite> & EnemySprites, std::vector<bool> & WantToDraw, Texture & EnemyTexture)
{
	Variables.clear();
	Enemies.clear();
	EnemySprites.clear();
	WantToDraw.clear();
	switch (player.Round)
	{
		case 1:
		{
			fill_vector(Variables, 50);
			fill_vector(Enemies, 50, 2.0, 0.8);
			fill_vector(WantToDraw, 50, 1);
			for (int i = 0; i < 50; i++)
				EnemySprites.push_back(Enemies[i].enemy_spawn(EnemyTexture));
			break;
		}
		case 2:
		{
			fill_vector(Variables, 60);
			fill_vector(Enemies, 60, 2.0, 0.8);
			fill_vector(WantToDraw, 60, 1);
			for (int i = 0; i < 60; i++)
				EnemySprites.push_back(Enemies[i].enemy_spawn(EnemyTexture));
			break;
		}
		case 3:
		{
			fill_vector(Variables, 60);
			fill_vector(Enemies, 40, 2.0, 0.8);
			fill_vector(Enemies, 20, 2.0, 1.8);
			fill_vector(WantToDraw, 60, 1);
			for (int i = 0; i < 60; i++)
				EnemySprites.push_back(Enemies[i].enemy_spawn(EnemyTexture));
			break;
		}
		case 4:
		{
			fill_vector(Variables, 60);
			fill_vector(Enemies, 40, 4.0, 1.0);
			fill_vector(Enemies, 20, 2.0, 2.0);
			fill_vector(WantToDraw, 60, 1);
			for (int i = 0; i < 60; i++)
				EnemySprites.push_back(Enemies[i].enemy_spawn(EnemyTexture));
			break;
		}
		case 5:
		{
			fill_vector(Variables, 80);
			fill_vector(Enemies, 40, 4.0, 1.2);
			fill_vector(Enemies, 40, 2.0, 2.2);
			fill_vector(WantToDraw, 80, 1);
			for (int i = 0; i < 80; i++)
				EnemySprites.push_back(Enemies[i].enemy_spawn(EnemyTexture));
			break;
		}
		default: break;
	}
}

void Map_1::save_game(Player player, std::vector<Ally_Active> ActiveAlly, std::vector<Ally_Passive> PassiveAlly)
{
	std::ofstream file("saves.txt", std::ios::out);
	if (file)
	{
		file << player.HP << '/' << player.Money << '/' << player.Round << '/';
		file << ActiveAlly.size() << '/';
		file << PassiveAlly.size() << '/';

	}
}

void Map_1::attack_enemies(std::vector<Ally_Active> & ActiveAlly, std::vector<bool>EnemyInRange, std::vector<Enemy> & Enemies, std::vector<int> EnemiesForEachAlly)
{
	for (int i = 0; i < ActiveAlly.size(); i++)
	{
		if (EnemyInRange[i])
		{
			ActiveAlly[i].attack(Enemies[EnemiesForEachAlly[i]]);
		}
	}
}

void Map_1::is_round_ongoing(std::vector<bool>WantToDraw, std::shared_ptr<bool> & IsRoundOngoing)
{
	int EnemyDestroyedCount = 0;
	for (int i = 0; i < WantToDraw.size(); i++)
	{
		if (WantToDraw[i] == false)
			EnemyDestroyedCount++;
		if (EnemyDestroyedCount == WantToDraw.size())
		{
			*IsRoundOngoing = false;
			std::cout << *IsRoundOngoing;
		}
	}
}

std::chrono::high_resolution_clock::time_point Map_1::configure_for_next_round(Player & player, Text & PlayersMoney_Display, std::shared_ptr<bool> & IsRoundOngoing)
{
	player.Round++;
	player.Money += 200;
	PlayersMoney_Display.setString(std::string(std::to_string(player.Round)));
	*IsRoundOngoing = true;
	return std::chrono::high_resolution_clock::now();
}


void Map_1::DisplayMap_1(Player & player, std::vector<Ally_Active> & ActiveAlly, std::vector<Ally_Passive> & PassiveAlly)
{
	RenderWindow window1(VideoMode(1920, 1080), "TD");
	
	//important variables: 
	Map_1 map;
	Clock clock;
	std::shared_ptr<bool> IsRoundOngoing (new bool(true));

	//creating ally texture and deque for allies sprites
	Ally_Active ally1(0, 0, 0);
	Ally_Passive ally2(0, 0, 0);

	std::deque<Sprite> Ally_Active_Sprites, Ally_Passive_Sprites;

	Texture ActiveAllyTexture = ally1.create_ally_texture(), PassiveAllyTexture = ally2.create_ally_texture();

	//creating enemy texture and all necessary containers: for storing current moving direction(variables), targets for allies(EnemiesForEachAlly),
	//enemies display status(WantToDraw - yes/no), whether enemy is in range(EnemyInRange), Enemy info(HP, speed, x, y - Enemies),
	//and enemies' sprites(EnemySprites)
	Enemy enemy(0, 0);
	Texture EnemyTexture = enemy.create_enemy_texture();

	std::vector<int> variables, EnemiesForEachAlly;
	std::vector<bool>WantToDraw, EnemyInRange;
	std::vector<Enemy> Enemies;
	std::vector<Sprite> EnemySprites;

	//evokes function that spawn enemies based on level
	spawn_enemies(player, variables, Enemies, EnemySprites, WantToDraw, EnemyTexture);

	//creating important texts: Players HP(P_HP), Max HP(Max_HP), Money in Players' pocket(PlayersMoney) and level(Round)
	Font font;
	font.loadFromFile("arial.ttf");

	Text P_HP(std::string(std::to_string(player.HP)), font), Max_HP("/20", font), PlayersMoney(std::string(std::to_string(player.Money)), font), Round(std::string(std::to_string(player.Round)), font);
	Text ArrayOfTexts[4] = { P_HP, Max_HP, PlayersMoney, Round};

	//text configuration: position, size, color
	configure_text(ArrayOfTexts);

	//creating maps' texture and sprite
	Texture Map_1_Texture = map.create_map1_texture();
	Sprite Map_1_Sprite = map.create_map1_sprite(Map_1_Texture);

	//variable used to make enemies move - using linear function changing in time
	float deltatime = clock.restart().asSeconds();

	//upload movement directions from file
	std::vector<int>Coordinates, Turning_Directions;
	take_coordinates_from_file(Turning_Directions, Coordinates);

	//defying starting coordinates. It must be done in case user forget to choose a position for ally to create (could cause trouble) 
	int X_Coord = 0, Y_Coord = 0;

	//checkpoint for games clock - used to have a reference point
	std::chrono::high_resolution_clock::time_point BegginingOfMap = std::chrono::high_resolution_clock::now();

	while (window1.isOpen())
	{
		Event event;

		//checking if every enemy is undrawable therefore if round is over 
		is_round_ongoing(WantToDraw, IsRoundOngoing);
		
		if (!*IsRoundOngoing)
		{
			BegginingOfMap = configure_for_next_round(player,ArrayOfTexts[3],IsRoundOngoing);
			spawn_enemies(player, variables, Enemies, EnemySprites, WantToDraw, EnemyTexture);
		}

			//mid program text configuration: used for eventual updates during game
			ArrayOfTexts[0].setString(std::string(std::to_string(player.HP)));
			ArrayOfTexts[2].setString(std::string(std::to_string(player.Money)));

			//MOVEMENT SECTION

			//checkpoint for games clock
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < Enemies.size(); i++)
			{
				//checking if time between last checkpoint and begin of window is greater than i+1 seconds. After that enemy is allowed to move
				//but if Enemy is destroyed WantToDraw is set to false therefore destroyed enemy won't be able to move
				if (std::chrono::duration_cast<std::chrono::duration<int>>(t2 - BegginingOfMap).count() > (i + 1) && WantToDraw[i])
				{
					if (WantToDraw[i])
					{
						//moving function with verification if enemy reached the end
						bool Is_End = Enemies[i].move(EnemySprites[i], Turning_Directions, Coordinates, variables[i], deltatime, Enemies[i].Enemy_Movement_Speed);
						//if enemy reaches end of path players HP is reduced by 2 and this enemy is set not to be drawn
						if (Is_End)
						{
							player.HP -= 2;
							WantToDraw[i] = false;
						}
					}
				}
			}
			//END OF MOVEMENT SECTION

			//DEFYING USERS ACTIONS SECTION
			while (window1.pollEvent(event))
			{
				//colours price text green: used for flash effect when user doesn't have enoug money to buy an ally 
				ArrayOfTexts[2].setFillColor(Color::Green);

				if (event.mouseButton.button == Mouse::Left)
				{
					if (event.type == Event::MouseButtonPressed)
					{
						//border for users interaction when placing allies. Should be expanded in future in order to avoid putting object into path
						if (X_Coord != 0 && Y_Coord != 0 && X_Coord <= 1510)
						{
							//creating attacking ally
							if (event.mouseButton.x >= 1755 && event.mouseButton.x <= 1855 && event.mouseButton.y >= 433 && event.mouseButton.y <= 533)
							{
								create_ally_entity(event, X_Coord, Y_Coord, Ally_Active_Sprites, ActiveAlly, player, ActiveAllyTexture, ArrayOfTexts[2]);
								EnemyInRange.push_back(0);
								EnemiesForEachAlly.push_back(0);

							}
							//creating ally which makes money
							else if (event.mouseButton.x >= 1573 && event.mouseButton.x <= 1671 && event.mouseButton.y >= 432 && event.mouseButton.y <= 531)
							{
								create_ally_entity(event, X_Coord, Y_Coord, Ally_Passive_Sprites, PassiveAlly, player, PassiveAllyTexture, ArrayOfTexts[2]);
							}
						}
						//saving game progress. Should be expanded with allies positions 
						if (event.mouseButton.x >= 1760 && event.mouseButton.x <= 1856 && event.mouseButton.y >= 905 && event.mouseButton.y <= 951)
							save_game(player, ActiveAlly, PassiveAlly);
						//closing game
						if ((event.mouseButton.x >= 1758 && event.mouseButton.x <= 1854 && event.mouseButton.y >= 970 && event.mouseButton.y <= 1017) || player.Round>5)
							window1.close();

						//checking if user want to destroy any ally in area
						will_to_destroy(event, player, ActiveAlly, Ally_Active_Sprites);
						will_to_destroy(event, player, PassiveAlly, Ally_Passive_Sprites);

						//used when creating ally entity. Sets their position so that their centre is exactly at users cursor
						X_Coord = event.mouseButton.x - 50;
						Y_Coord = event.mouseButton.y - 50;
					}
				}
				//closing window if top right X is pressed
				if (event.type == Event::Closed)
					window1.close();
			}
			//END OF DEFYING USERS ACTIONS SECTION

			//ATTACK ENEMIES SECTION
			{
				for (int i = 0; i < ActiveAlly.size(); i++)
				{
					//vector set to store ids of enemies in range
					std::vector<int> EnemiesInRange;

					for (int j = 0; j < Enemies.size(); j++)
					{
						//first tried to use threads... but i failed. anyway pair managed to stay. stores information of two entities between
						//whom distance will be calculated
						std::pair<Enemy, Ally_Active> PairForDistanceCalculation = { Enemies[j], ActiveAlly[i] };
						//my one and only DATE: Distance Ally To Enemy
						float DistanceAllyToEnemy = 0;
						
						if (WantToDraw[j])
						{
							//calculating distance between Ally and Enemy passed by pair
							value(DistanceAllyToEnemy, PairForDistanceCalculation);

							//if distance betweeen Ally and Enemy is less than 200px attack begins: id of enemy is passed
							//to vector and signal EntityInRange is set to true. Otherwise it is updated to false
							if (DistanceAllyToEnemy <= 200)
								EnemiesInRange.push_back(j);
							
							//There is a chance that attacked Enemy should be destroyed. It is checked here
							if (Enemies[j].Enemy_Healt_Points <= 0)
							{
								WantToDraw[j] = false;
								player.Money += 1;
							}
						}
					}
					//this is a part where firest Enemy in range is chosen to attack
					if (EnemiesInRange.size() > 0)
					{
						//tells a specified attacking ally that there is enemy in range and can attack 
						EnemyInRange[i] = true;
						//pointer to integer which is id of a first ally in range. For now it stores first value from vector
						std::unique_ptr<int> FirstEntity(new int(EnemiesInRange[0]));

						//if there is an enemy with lower id it means it is closer in queue to the end of path
						for (int j = 1; j < EnemiesInRange.size(); j++)
						{
							if (EnemiesInRange[j] < *FirstEntity)
								*FirstEntity = EnemiesInRange[j];
						}
						//Enemy for an ally is passed: the one chosen from the loop above
						EnemiesForEachAlly[i] = *FirstEntity;
					}
					else EnemyInRange[i] = false;
				}

				//checkpoint for games clock
				std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();

				//checking if time between beggining of map and last checkpoint is a multiple of 100000 nanoseconds
				//which is 0.0001 seconds. It is very low but many values are just passed by without being checked
				if (std::chrono::duration_cast<std::chrono::nanoseconds>(t3 - BegginingOfMap).count() % 100000 == 0)
					attack_enemies(ActiveAlly,EnemyInRange, Enemies, EnemiesForEachAlly);
			}
			//END OF ATTACK ENEMIES SECTION

			//checkpoint for games clock
			std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();
			
			//checking if time between beggining of map and last checkpoint is a multiple of 500000 nanoseconds
			//which is 0.0005 seconds.
			if (std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - BegginingOfMap).count() % 500000 <= 1)
				player.Money += 5 * PassiveAlly.size();

			//end of game condition
			if (player.HP <= 0)
				window1.close();

			//DRAWING SECTION
			window1.clear();
			window1.draw(Map_1_Sprite);
			for (int i = 0; i < 4; i++)
				window1.draw(ArrayOfTexts[i]);
			for (int i = 0; i < Ally_Active_Sprites.size(); i++)
				window1.draw(Ally_Active_Sprites[i]);
			for (int i = 0; i < Ally_Passive_Sprites.size(); i++)
				window1.draw(Ally_Passive_Sprites[i]);
			for (int i = 0; i < WantToDraw.size(); i++)
				if (WantToDraw[i])
					window1.draw(EnemySprites[i]);
		
		window1.display();
		//END OF DRAWING SECTION
	}
}
