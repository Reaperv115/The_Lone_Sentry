#pragma once
#include "vendor/glm/glm.hpp"
#include <iostream>

namespace Engine
{
	class CollisionDetection
	{
	public:
		static bool CheckCollision(const glm::vec3 posA, const glm::vec3 posB, float radiusA, float radiusB)
		{
			float distance = glm::distance(posA, posB);
			return distance < (radiusA + radiusB);
			/*bool collisionX = posA.x + radiusA >= posB.x &&
				posB.x + radiusB >= posA.x;
			bool collisionY = posA.y + radiusA >= posB.y &&
				posB.y + radiusB >= posA.y;
			return collisionX && collisionY;*/
		}
	};
}