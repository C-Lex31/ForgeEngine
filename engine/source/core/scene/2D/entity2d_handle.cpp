#include "frpch.h"
#include "entity2d_handle.h"

namespace Forge {
	Entity::Entity(entt::entity en, FScene2d* scn)
		:m_EntityHandle(en) , m_Scene(scn)
	{

	}
}
