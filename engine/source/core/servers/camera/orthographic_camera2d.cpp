#include "irpch.h"
#include "orthographic_camera2d.h"
#include <glm/gtc/matrix_transform.hpp>
namespace Iris {

	orthographic_camera2d::orthographic_camera2d(float left, float right, float bottom, float up)
		:m_ProjectionMatrix(glm::ortho(left,right,bottom,up,-1.0f,1.0f)),m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; // CAUTION DO NOT CHANGE ORDER 
	}

	void orthographic_camera2d::  RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
							  glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; // CAUTION DO NOT CHANGE ORDER 
	}


}