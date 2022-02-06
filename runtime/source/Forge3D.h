#pragma once
#include "ForgeEngine.h"

class Forge3D :public Forge::Layer
{
public:
	Forge3D();
	virtual ~Forge3D()=default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(Forge::Timestep ts) override;
	virtual void OnGUIRender() override;
	void OnEvent(Forge::Event& event)override;
private:
	Forge::Camera m_Cam;
	Forge::FRef<Forge::vertex_array> m_vertexArray;
	Forge::FRef<Forge::Texture2D>m_Texture2D;
	glm::vec4 CubeColor=glm::vec4(1.0f,0.0f,0.0f,1.0f);
};