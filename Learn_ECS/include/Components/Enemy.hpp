#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>
#include <cstdio>
#include "Systems/EnemyAISystem.hpp"

struct Enemy
{
	std::pair<float, float> TargetLocation;
	std::vector<EnemyAISystem::Node> openList;
	std::vector<EnemyAISystem::Node*> closedList;
	bool pathFOUND = false;
};

#endif