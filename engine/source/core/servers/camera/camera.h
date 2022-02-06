#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "core/input/input.h"
#include "core/input/keycodes.h"
#include "core/input/mouse_button_codes.h"
namespace Forge {

	class Camera
	{
	public:
		Camera(float width, float height, glm::vec3 position);

	//	const glm::vec3& GetCamPos() { return m_Position; }
	//	void SetCamPos(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

	//	const float  GetCamRot() { return m_Rotation; }
	//	void SetCamRot(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		void CamInput(float sec);
		void RecalculateViewMatrix(float FOV=45.0f, float nearPlane=0.1f, float farPlane=500.0f);
		
	private:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix=glm::mat4(1.0f);
		glm::mat4 m_ViewProjectionMatrix;
		
		glm::vec3 Position;               //To use these components in ForgeEngine.cpp unit make them public and inline static
		glm::vec3 m_Orientation = { 0.0f,0.0f,-1.0f };
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		bool firstMouse = true;

		float m_Rotation = 0.0f;
		float width;
		float height;

		float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
		float pitch = 0.0f;
		float lastX = 1366.0 / 2.0;
		float lastY = 705.0 / 2.0;
		float CamTranslationSpeed = 1.0f;
	};

}
