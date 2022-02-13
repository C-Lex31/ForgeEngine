#include "frpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"

namespace Forge {

	Camera::Camera(float width, float height, glm::vec3 Position)
		//:m_ProjectionMatrix(glm::ortho(left, right, bottom, up, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		Camera::width = width;
		Camera::height = height;
		Camera::Position = Position;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; // CAUTION DO NOT CHANGE ORDER 
	}

	void Camera::CamInput(float sec)
	{
		if (input::isKeyPressed(KeyCode::LeftShift))
			CamTranslationSpeed = 3.3f;
		else 
			CamTranslationSpeed = 1.5f;
		if (input::isKeyPressed(KeyCode::W))
			Camera::Position += CamTranslationSpeed * Camera::m_Orientation * sec;

		if (input::isKeyPressed(KeyCode::S))
			Camera::Position += CamTranslationSpeed * (-Camera::m_Orientation) * sec;
		if (input::isKeyPressed(KeyCode::A))
			Camera::Position += CamTranslationSpeed * -glm::normalize(glm::cross((Camera::m_Orientation), Camera::up)) * sec;
		if (input::isKeyPressed(KeyCode::D))
			Camera::Position += CamTranslationSpeed * glm::normalize(glm::cross((Camera::m_Orientation), Camera::up)) * sec;
		if (input::isKeyPressed(KeyCode::E))
			Camera::Position += CamTranslationSpeed * Camera::up * sec;
		if (input::isKeyPressed(KeyCode::Q))
			Camera::Position += CamTranslationSpeed * -Camera::up * sec;

		if (input::isMouseButtonPressed(FR_MOUSE_BUTTON_RIGHT))
		{
			input::HideCursor();
			float xPos = input::GetMouseX();
			float yPos = input::GetMouseY();
			if (Camera::firstMouse)
			{
				lastX = xPos;
				lastY = yPos;
				Camera::firstMouse = false;
			}


			float xoffset = xPos - lastX;
			float yoffset = lastY - yPos;
			lastX = xPos;
			lastY = yPos;

			float sensitivity = 3.5f;
			xoffset *= sensitivity * sec;
			yoffset *= sensitivity * sec;

			yaw += xoffset;
			pitch += yoffset;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			direction.y = sin(glm::radians(pitch));
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			Camera::m_Orientation = glm::normalize(direction);
		}
		else { Camera::firstMouse = true; input::ShowCursor(); }
	}

	void Camera::RecalculateViewMatrix(float FOV,float nearPlane,float farPlane)
	{
	//	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
		//	glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

	//	m_ViewMatrix = glm::inverse(transform);
		m_ViewMatrix = glm::lookAt(Position, Position + m_Orientation, up);
		m_ProjectionMatrix = glm::perspective(glm::radians(FOV), width / height, nearPlane, farPlane);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; // CAUTION DO NOT CHANGE ORDER 
	}


}