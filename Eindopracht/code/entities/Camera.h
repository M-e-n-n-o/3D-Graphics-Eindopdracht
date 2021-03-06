#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"

namespace entities
{
	class Camera
	{
	private:
		const float SENSITIVITY = 0.1f;
		
		Entity& entityToFollow;
		const float distanceFromEntity = 20;
		float angleAroundEntity = 0;
		
		glm::vec3 position;
		glm::vec3 rotation;

	public:
		Camera(Entity& entityToFollow);

		void update(GLFWwindow* window);

		void invertPitch() { rotation.x = -rotation.x; }
		
		inline glm::vec3 getPosition() const { return position; }
		inline glm::vec3& getPositionRef() { return position; }
		inline glm::vec3 getRotation() const{ return rotation; }

	private:		
		void calculatePitch(GLFWwindow* window);
		void calculateAngle(GLFWwindow* window);
	};
}