#include <iostream>
#include <Systems/EnemyAISystem.hpp>
#include <Managers/EntityManager.hpp>
#include <Managers/ArchetypeManager.hpp>
#include <Managers/ComponentManager.hpp>
#include <Time.hpp>
#include <algorithm>
#include <cmath>

void EnemyAISystem::Init()
{}

void EnemyAISystem::Update()
{
	ArchetypeManager& am{ ArchetypeManager::GetInstance() };
	ArchetypeSet set{ am.GetArchetypeSet<Transform, Enemy>() };
	for (auto& arch : set)
	{
		auto& tv{ arch->GetComponentArray<Transform>() };
		auto& enemy{ arch->GetComponentArray<Enemy>() };
		for (size_t i{}; i < arch->GetEntityCount(); ++i)
		{
			Transform& transform{ std::any_cast<Transform&>(tv[i]) };
			Enemy& en{ std::any_cast<Enemy&>(enemy[i])};

			if (en.pathFOUND) continue;

			if ((transform.x == en.TargetLocation.first && transform.y == en.TargetLocation.second) || en.openList.empty())
			{
				InitAStar(en, transform);
			}
			AStar(en, transform);
		}
	}
}

void EnemyAISystem::InitAStar(Enemy& enemy, Transform& transform)
{
	Node start{ transform.x, transform.y, nullptr, 0, 0 };
	enemy.openList.push_back(start);
	enemy.closedList.clear();
}
void EnemyAISystem::AStar(Enemy& enemy, Transform& transform)
{
	while (!enemy.openList.empty())
	{
		size_t index = 0;
		float cheapestCost = enemy.openList[0].totalCost;
		for (size_t i = 1; i < enemy.openList.size(); i++)
		{
			if (enemy.openList[i].totalCost < cheapestCost)
			{
				cheapestCost = enemy.openList[i].totalCost;
				index = i;
			}
		}
		Node currentNode = enemy.openList[index];
		enemy.openList.erase(enemy.openList.begin() + index);

		if (currentNode.posX == enemy.TargetLocation.first && currentNode.posY == enemy.TargetLocation.second)
		{
			enemy.pathFOUND = true;
			return;
		}
		
		enemy.closedList.push_back(&currentNode);

		for (auto& neighbour : GetNeighbours(currentNode))
		{
			if (std::find(enemy.closedList.begin(), enemy.closedList.end(), neighbour) == enemy.closedList.end() &&
				std::find(enemy.openList.begin(), enemy.openList.end(), neighbour) == enemy.openList.end())
			{
				neighbour.first.actualCost = neighbour.first.parent->actualCost + neighbour.second;
				neighbour.first.totalCost = neighbour.first.actualCost + Heuristic(neighbour.first, enemy.TargetLocation);
				enemy.openList.push_back(neighbour.first);
			}
			else if(std::find(enemy.openList.begin(), enemy.openList.end(), neighbour) != enemy.openList.end() && neighbour.second < enemy.openList[0].
		}
	}
}

std::vector<std::pair<EnemyAISystem::Node, float>> EnemyAISystem::GetNeighbours(EnemyAISystem::Node& currentNode)
{
	std::vector<std::pair<Node, float>> neighbours;

	std::vector<std::pair<float, float>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

	for (size_t i = 0; i < directions.size(); i++)
	{
		std::pair<float, float> neighbourPos = { currentNode.posX + directions[i].first, currentNode.posY + directions[i].second};
		if (neighbourPos == collide with terrain) continue;
		float movementCost = 0;
		while (neighbourPos != collide with terrain)
		{
			neighbourPos.first += directions[i].first;
			neighbourPos.second += directions[i].second;
			movementCost++;
		}
		neighbourPos.first -= directions[i].first;
		neighbourPos.second -= directions[i].second;
		movementCost--;

		int possiblePaths = 0;

		for (size_t j = 0; j < directions.size(); i++)
		{
			if (i == j)
			{
				continue;
			}

			std::pair<float, float> neighbourSurroundingPos = { neighbourPos.first + directions[j].first, neighbourPos.second + directions[j].second };

			if (neighbourSurroundingPos != collide with terrain)
			{
				possiblePaths++;
			}
		}

		if (possiblePaths)
		{
			Node neighbourNode{ neighbourPos.first, neighbourPos.second, &currentNode, 0, 0 };
			std::pair<Node, float> temp{ neighbourNode, movementCost };
			neighbours.push_back(temp);
		}
		
	}
}

float EnemyAISystem::Heuristic(const Node& node, std::pair<float, float> targetLoc)
{
	float estimatedCostSQ = (node.posX - targetLoc.first) * (node.posX - targetLoc.first) +
		(node.posY - targetLoc.second) * (node.posY - targetLoc.second);
	float estimatedCost = sqrt(estimatedCostSQ);

	return estimatedCost;
}
