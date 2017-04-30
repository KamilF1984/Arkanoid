#include "GameLevels.hpp"
#include <fstream>
#include <sstream>
#include <iostream>


void GameLevel::Load(const char *file){// , int levelWidth, int levelHeight){
	
   this-> bricks.clear();
	// Load from file
	int tileCode;
	//GameLevel level;
	std::string line;
	std::ifstream fstream(file);//ifstream fileIn("plik.txt"); file jest wskaznikim na nazwe pliku,ktorą podaje na pierwszy element funkcji Load,jak plik istnieje to zwraca true
	std::vector<std::vector<int>> tileData;//macierz
	if (fstream)//if true
	{
		while (std::getline(fstream, line)) // Read each line from level file
		{
			std::istringstream sstream(line);//do bufora stringbuf jaki jest dostępny w obiekcie sstream klasy istringstream zapisywany jest plik linia po lini. Uzywany jest do parsowania napisów!
			std::vector<int> row;
			while (sstream >> tileCode) // Read each word seperated by spaces// tilecode jest intem bo wczytujemy inty. Powoduje to,że 
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		
		if (tileData.size() > 0)
		this->init(tileData);//, levelWidth, levelHeight);
		
	}


}

 void GameLevel::init(std::vector<std::vector<int>> tileData)//, int lvlWidth, int lvlHeight)
{
	// Calculate dimensions
	int height = tileData.size();
	int width = tileData[0].size();
	std::cout << height;
	std::cout << width;
	//float unit_width = videoWidth / static_cast<float>(width);
	float unit_width = 60;
	//float unit_height = videoHeight / height;
	float unit_height = 20;
	//std::cout << unit_width << std::endl;
	//std::cout << unit_height;
	sf::Color defColor;

	for (int x = 0; x <height; ++x)
	{
		for (int y = 0; y < width; ++y)
		{
		//	if (tileData[x][y] == 0)
			//	defColor = sf::Color::Black;
			if (tileData[x][y] == 1)
				defColor = sf::Color::Yellow;
		//	std::cout << "1";
			else 	if (tileData[x][y] == 2)
				defColor = sf::Color::Red;
			else if (tileData[x][y] == 3)
				defColor = sf::Color::Green;
			else if (tileData[x][y] == 4)
				defColor = sf::Color::Blue;
			else if (tileData[x][y] == 5)
				defColor = sf::Color::Magenta;
				

						   sf::Vector2f pos((unit_width+3) * (y+2)+22, (unit_height+3) * (x+5));
						   sf::Vector2f size(unit_width, unit_height);
			     			//this->bricks.push_back(Brick{(y + 1) * (static_cast<float>(60) + 3) + 22, (x + 2) * (static_cast<float>(20) + 3), defColor});
						   this->bricks.push_back(Brick{ pos,size, defColor });
				
				//
		}
	}
}