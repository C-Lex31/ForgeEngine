#pragma once

#include <glm/glm.hpp>

namespace Iris {

	class orthographic_camera2d
	{
	public:
		orthographic_camera2d(float left, float right, float bottom, float up);

		const glm::vec3& GetCamPos() { return m_Position; }
		void SetCamPos(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		const float  GetCamRot() { return m_Rotation; }
		void SetCamRot(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = {0.0f,0.0f,0.0f};//sadly glm does not auto initialize stuff :(
		float m_Rotation = 0.0f;
	};

}
