#include <algorithm>
#include "Toolbox.h"

#include <ctime>

namespace toolbox
{
	glm::mat4 CreateModelMatrix(glm::vec3 translation, glm::vec3 rotation, float scale)
	{
		glm::mat4 matrix(1.0f);
		matrix = glm::translate(matrix, translation);
		matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
		return matrix;
	}

	glm::mat4 CreateViewMatrix(entities::Camera& camera)
	{
		glm::mat4 matrix(1.0f);
		matrix = glm::rotate(matrix, glm::radians(camera.getRotation().x), glm::vec3(1, 0, 0));
		matrix = glm::rotate(matrix, glm::radians(camera.getRotation().y), glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, glm::radians(camera.getRotation().z), glm::vec3(0, 0, 1));
		const glm::vec3 negativeCamPos = glm::vec3(-camera.getPosition().x, -camera.getPosition().y, -camera.getPosition().z);
		matrix = glm::translate(matrix, negativeCamPos);
		return matrix;
	}

	float Clamp(float value, float min, float max)
	{
		return std::max(min, std::min(value, max));
	}

	int Random(const int min, const int max)
	{
		static bool first = true;
		if (first)
		{
			srand(time(0));
			first = false;
		}
		return min + rand() % ((max + 1) - min);
	}
}
