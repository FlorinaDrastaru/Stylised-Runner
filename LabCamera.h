#pragma once
#include <include/glm.h>
#include <include/math.h>

namespace Laborator
{
	class CameraTema2
	{
	public:
		CameraTema2::CameraTema2()
		{
			position = glm::vec3(0, 2, 5);
			forward = glm::vec3(0, 0, -1);
			up = glm::vec3(0, 1, 0);
			right = glm::vec3(1, 0, 0);
			distanceToTarget = 2;
		}

		CameraTema2::CameraTema2(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
		{
			Set(position, center, up);
		}

		CameraTema2::~CameraTema2()
		{ }

		// Update camera
		void Set(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
		{
			this->position = position;
			forward = glm::normalize(center - position);
			right = glm::cross(forward, up);
			this->up = glm::cross(right, forward);
		}

		void CameraTema2::MoveForward(float distance)
		{
			glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
			// movement will keep the camera at the same height always
			// Example: If you rotate up/down your head and walk forward you will still keep the same relative distance (height) to the ground!
			// Translate the camera using the DIR vector computed from forward
			position += distance * dir;
		}

		void CameraTema2::TranslateForward(float distance)
		{
			// TODO : Translate the camera using the "forward" vector
			position += distance * forward;
		}

		void CameraTema2::TranslateUpward(float distance)
		{
			// TODO : Translate the camera using the up vector
			position += distance * up;
		}

		void CameraTema2::TranslateRight(float distance)
		{
			// TODO
			// Translate the camera using the "right" vector
			// Usually translation using camera "right' is not very useful because if the camera is rotated around the "forward" vector 
			// translation over the right direction will have an undesired effect; the camera will get closer or farther from the ground
			// Using the projected right vector (onto the ground plane) makes more sense because we will keep the same distance from the ground plane
			position += distance * right;
		}

		void CameraTema2::RotateFirstPerson_OX(float angle)
		{
			// TODO
			// Compute the new "forward" and "up" vectors
			// Attention! Don't forget to normalize the vectors
			// Use glm::rotate()
			forward = glm::normalize(glm::vec3(
				glm::rotate(
					glm::mat4(1), angle, right) * glm::vec4(forward.x, forward.y, forward.z, 0)
			));
			up = glm::normalize(glm::cross(right, forward));
		}

		void CameraTema2::RotateFirstPerson_OY(float angle)
		{
			// TODO
			// Compute the new "forward", "up" and "right" vectors
			// Don't forget to normalize the vectors
			// Use glm::rotate()
			forward = glm::normalize(glm::vec3(
				glm::rotate(
					glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward.x, forward.y, forward.z, 0)
			));
			right = glm::normalize(glm::vec3(
				glm::rotate(
					glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(right.x, right.y, right.z, 0)
			));
			up = glm::normalize(glm::cross(right, forward));
		}

		void CameraTema2::RotateFirstPerson_OZ(float angle)
		{
			// TODO
			// Compute the new Right and Up, Forward stays the same
			// Don't forget to normalize the vectors
			right = glm::normalize(glm::vec3(
				glm::rotate(
					glm::mat4(1), angle, forward) * glm::vec4(right.x, right.y, right.z, 0)
			));
			up = glm::normalize(glm::cross(forward, right));

		}

		void CameraTema2::RotateThirdPerson_OX(float angle)
		{
			// TODO
			// Rotate the camera in Third Person mode - OX axis
			// Use distanceToTarget as translation distance
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OX(angle);
			TranslateForward(-distanceToTarget);
		}

		void CameraTema2::RotateThirdPerson_OY(float angle)
		{
			// TODO
			// Rotate the camera in Third Person mode - OY axis
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OY(angle);
			TranslateForward(-distanceToTarget);
		}

		void CameraTema2::RotateThirdPerson_OZ(float angle)
		{
			// TODO
			// Rotate the camera in Third Person mode - OZ axis
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OZ(angle);
			TranslateForward(-distanceToTarget);
		}

		glm::mat4 CameraTema2::GetViewMatrix()
		{
			// Returns the View Matrix
			return glm::lookAt(position, position + forward, up);
		}

		glm::vec3 CameraTema2::GetTargetPosition()
		{
			return position + forward * distanceToTarget;
		}

	public:
		float distanceToTarget;
		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;
	};
}
