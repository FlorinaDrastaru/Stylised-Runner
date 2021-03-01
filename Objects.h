#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Objects
{
	inline glm::mat3 Translate(float translateX, float translateY)
	{
		return glm::transpose(
			glm::mat3(1, 0, translateX,
				0, 1, translateY,
				0, 0, 1));
	}

	inline glm::mat3 Scale(float scaleX, float scaleY)
	{
		return glm::transpose(
			glm::mat3(scaleX, 0, 0,
				0, scaleY, 0,
				0, 0, 1));

	}

	inline glm::mat3 Rotate(float radians)
	{
		

		return glm::mat3(
			cos(radians), sin(radians), 0.f,
			-sin(radians), cos(radians), 0.f,
			0.f, 0.f, 1.f
		);
	}

	inline glm::mat4 RotateOX(float radians)
	{
		// TODO implement rotate matrix
		return glm::transpose(
			glm::mat4(1, 0, 0, 0,
				0, cos(radians), -sin(radians), 0,
				0, sin(radians), cos(radians), 0,
				0, 0, 0, 1)
		);
	}

	inline glm::mat4 RotateOY(float radians)
	{
		return glm::transpose(
			glm::mat4(cos(radians), 0, sin(radians), 0,
				0, 1, 0, 0,
				-sin(radians), 0, cos(radians), 0,
				0, 0, 0, 1)
		);
	}

	inline glm::mat4 RotateOZ(float radians)
	{
		// TODO implement rotate matrix
		return glm::transpose(
			glm::mat4(cos(radians), -sin(radians), 0, 0,
				sin(radians), cos(radians), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1)
		);
	}
	Mesh* CreateRectangle(std::string name, glm::vec3 color, bool fill = false);

}


