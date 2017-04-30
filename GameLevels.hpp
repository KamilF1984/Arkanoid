#pragma once
#include <vector>
#include "Brick.hpp"


class GameLevel
{
public:
	std::vector<Brick> bricks;

	GameLevel() { }
	// Loads level from file
	 void Load(const char * file);//, int levelWidth, int levelHeight);
	// Render level
	//void Draw(SpriteRenderer &renderer);
	// Check if the level is completed (all non-solid tiles are destroyed)
	//bool IsCompleted();
//private:
	// Initialize level from tile data
	  void init(std::vector<std::vector<int>> tileData);//, int levelWidth, int levelHeight);
}; 