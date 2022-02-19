#pragma once
#include "scene_2d.h"
#include "entt.hpp"

namespace Forge {

	class Entity
	{
	public:
		Entity(entt::entity en , FScene2d* scn );
		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		}

	private:
		entt::entity m_EntityHandle;
		FScene2d* m_Scene;
	};


}