#pragma once

// Includes:
#include "types.h"

// GLM:
#include <glm/glm.hpp>

// Namespaces:
namespace game
{
	namespace graphics
	{
		// Classes:
		class camera
		{
			public:
				// Constructor(s):
				camera(const glm::vec3& position=glm::vec3(), const glm::vec3& rotation=glm::vec3(0.0f, -90.0f, 0.0f), GLfloat FOV=45.0f, glm::vec3 up=glm::vec3(0.0f, 1.0f, 0.0f), bool rot_in_radians=false); //90.0f

				// Methods:
				void updateAngles();

				// Vectors:
				const glm::vec3& getPosition() const;
				glm::vec3& getPosition();

				const glm::vec3& getRotation() const;
				glm::vec3& getRotation();

				// Matrices:
				glm::mat4 getProjectionMatrix(GLfloat aspect, GLfloat near=0.1f, GLfloat far=1000.0f) const;
				glm::mat4 getProjectionMatrixFrom(GLfloat screenWidth, GLfloat screenHeight, GLfloat near = 0.1f, GLfloat far = 1000.0f) const;

				glm::mat4 getProjectionMatrixFrom(GLsizei screenWidth, GLsizei screenHeight, GLfloat near = 0.1f, GLfloat far = 1000.0f) const
				{
					return getProjectionMatrixFrom(static_cast<GLfloat>(screenWidth), static_cast<GLfloat>(screenHeight), near, far);
				}

				// This retrieves the current view-matrix of this camera.
				glm::mat4 getViewMatrix() const;

				// FOV:
				GLfloat getFOV() const;
				void setFOV(GLfloat FOV);
			protected:
				// Fields:
				glm::vec3 position;
				glm::vec3 rotation;

				glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
				glm::vec3 right;
				glm::vec3 up;

				glm::vec3 worldUp; // const

				GLfloat FOV;
		};
	}
}