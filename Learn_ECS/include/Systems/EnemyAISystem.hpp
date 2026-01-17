#ifndef ENEMY_SYSTEM_HPP
#define ENEMY_SYSTEM_HPP

#include <Systems/ISystem.hpp>
#include <Components/Transform.hpp>
#include <Components/Enemy.hpp>
#include <cstdint>

class EnemyAISystem : public ISystem
{
public:
	struct Node
	{
		float posX, posY;
		Node* parent;
		float actualCost;
		float totalCost;
	};
	void Init();

	/**
	 * @brief Updates the physical properties of objects like position, velocity, and rotation.
	 */
	void Update();

private:
	void InitAStar(Enemy& enemy, Transform& transform);
	void AStar(Enemy& enemy, Transform& transform);
	std::vector<std::pair<Node, float>> GetNeighbours(Node& currentNode);
	float Heuristic(const Node& node, std::pair<float, float> targetLoc);
};
#endif