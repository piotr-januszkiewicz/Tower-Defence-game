#include "Menu.h"

void Menu::load_from_save(Player & player, std::vector<Ally_Active> & ActiveAlly, std::vector<Ally_Passive> & PassiveAlly)
{
	std::string Line_From_File;
	int counter = 0;
	std::ifstream file("saves.txt", std::ios::in);
	if (file.good())
	{
		while (!file.eof())
		{
			getline(file, Line_From_File);
			std::size_t Pos = Line_From_File.find_first_of('/');
			while (Pos != std::string::npos)
			{
				std::string s = Line_From_File.substr(0, Pos);
				Line_From_File.erase(Line_From_File.begin(), Line_From_File.begin() + (Pos + 1));
				Pos = Line_From_File.find_first_of('/');
				if (counter == 0)
				{
					player.HP = std::atoi(s.c_str());
				}
				if (counter == 1)
				{
					player.Money = std::atoi(s.c_str());
				}
				if (counter == 2)
				{
					player.Round = std::atoi(s.c_str());
				}
				if(counter == 3)
				{
					int AlliesCount = std::atoi(s.c_str());
					player.Money += AlliesCount*200;
				}
				if (counter == 4)
				{
					int AlliesCount = std::atoi(s.c_str());
					player.Money += AlliesCount*150;
				}
				counter++;
			}
		}
	}
}

int Menu::DisplayGameMenu()
{
	RenderWindow window(VideoMode(1920, 1080), "TD");
	Map_1 Map;

	Image Menu;
	if (!Menu.loadFromFile("game_menu.jpg"))
		return -1;

	Player player;
	std::vector<Ally_Active> ActiveAlly;
	std::vector<Ally_Passive> PassiveAlly;

	Texture Game_Menu_Texture;
	Game_Menu_Texture.loadFromImage(Menu);

	Sprite sprite;
	sprite.setTexture(Game_Menu_Texture);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					if (event.mouseButton.x >= 720 && event.mouseButton.x <= 1200)
					{
						if (event.mouseButton.y >= 450 && event.mouseButton.y <= 550)
						{
							Map.DisplayMap_1(player, ActiveAlly, PassiveAlly);
						}

						if (event.mouseButton.y >= 550 && event.mouseButton.y <= 650)
						{
							load_from_save(player, ActiveAlly, PassiveAlly);
							Map.DisplayMap_1(player, ActiveAlly, PassiveAlly);
						}

						if (event.mouseButton.y >= 650 && event.mouseButton.y <= 750)
							window.close();
					}
				}
			}
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}
	return 0;
}