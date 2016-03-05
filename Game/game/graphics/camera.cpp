// Includes:
#include "camera.h"

#include "opengl.h"

// GLM:
#include <glm/gtc/matrix_transform.hpp>

// C STDLIB:
#include <cmath>

// Namespaces:
namespace game
{
	namespace graphics
	{
		// Classes:

		// camera:

		// Constructor(s):
		camera::camera(const glm::vec3& pos, const glm::vec3& rot, GLfloat fieldOfView, glm::vec3 up, bool rot_in_radians) : position(pos), FOV(fieldOfView), worldUp(up)
		{
			if (!rot_in_radians)
			{
				for (auto i = 0; i < rotation.length(); i++)
				{
					rotation[i] = glm::radians(rot[i]);
				}
			}
			else
			{
				rotation = rot;
			}

			updateAngles();
		}

		// Methods:
		void camera::updateAngles()
		{
			glm::vec3 front;

			front.x = cos(rotation.y) * cos(rotation.x);
			front.y = sin(rotation.x);
			front.z = sin(rotation.y) * cos(rotation.x); // rotation.z

			this->front = glm::normalize(front);

			this->right = glm::normalize(glm::cross(this->front, this->worldUp));
			this->up = glm::normalize(glm::cross(this->right, this->front));

			return;
		}

		// Vectors:
		const glm::vec3& camera::getPosition() const
		{
			return this->position;
		}

		glm::vec3& camera::getPosition()
		{
			return this->position;
		}

		const glm::vec3& camera::getRotation() const
		{
			return this->rotation;
		}

		glm::vec3& camera::getRotation()
		{
			return this->rotation;
		}

		// Matrices:
		glm::mat4 camera::getProjectionMatrix(GLfloat aspect, GLfloat near, GLfloat far) const
		{
			return glm::perspective(FOV, aspect, near, far);
		}

		glm::mat4 camera::getProjectionMatrixFrom(GLfloat screenWidth, GLfloat screenHeight, GLfloat near, GLfloat far) const
		{
			return getProjectionMatrix((screenWidth / screenHeight), near, far);
		}

		glm::mat4 camera::getViewMatrix() const
		{
			return glm::lookAt(position, position + front, up);
		}

		// FOV:
		GLfloat camera::getFOV() const
		{
			return this->FOV;
		}

		void camera::setFOV(GLfloat FOV)
		{
			this->FOV = FOV;

			return;
		}
	}
}