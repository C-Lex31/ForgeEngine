#pragma once


#include "entt.hpp"
#include "core/main/timestep.h"

namespace Forge {

	class FScene2d
	{
	public:
		FScene2d();
		~FScene2d();

		entt::entity GenFEntity();
		entt::registry& reg() { return m_Registry; }
		void OnSceneUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
		friend class Entity;
	};


}