#include "frpch.h"
#include "scene_2d.h"
#include "components_2d.h"

namespace Forge {
	FScene2d::FScene2d()
	{
	}

	FScene2d::~FScene2d()
	{
	}
	entt::entity FScene2d::GenFEntity()
	{
		return m_Registry.create();
	}

	void FScene2d::OnSceneUpdate(Timestep ts)
	{
		auto group = m_Registry.group<Transform>(entt::get<SpriteRendererComponent>);

		for (auto entity : group)
		{
		//	auto& [_transform, mesh]
		}

	}

}