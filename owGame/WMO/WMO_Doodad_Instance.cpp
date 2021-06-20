#include "stdafx.h"

#ifdef USE_WMO_MODELS

#ifdef USE_M2_MODELS

// General
#include "WMO_Doodad_Instance.h"

// Additional
#include "WMO_Base_Instance.h"

CWMO_Doodad_Instance::CWMO_Doodad_Instance(IScene& Scene, const std::shared_ptr<CM2>& M2Object, uint32 _index, const SWMO_Doodad_PlacementInfo & _placement)
	: CM2_Base_Instance(Scene, M2Object)
	, m_Index(_index)
	, m_Placement(_placement)
	, m_PortalVisibilityState(true)
{
	setColor(glm::vec4(_placement.getColor()));
}

CWMO_Doodad_Instance::~CWMO_Doodad_Instance()
{}



//
// IPortalRoomObject
//
BoundingBox CWMO_Doodad_Instance::GetBoundingBox() const
{
	return GetComponentT<IColliderComponent>()->GetWorldBounds();
}



//
// SceneNode3D
//
void CWMO_Doodad_Instance::Initialize()
{
	__super::Initialize();

	SetLocalPosition(Fix_XZmY(m_Placement.position));
	SetLocalRotationQuaternion(glm::quat(m_Placement.orientation.w, -m_Placement.orientation.z, m_Placement.orientation.x, m_Placement.orientation.y));
	SetLocalScale(glm::vec3(m_Placement.scale, -m_Placement.scale, -m_Placement.scale));
}

void CWMO_Doodad_Instance::Accept(IVisitor* visitor)
{
	auto parentOfParent = std::dynamic_pointer_cast<CWMO_Base_Instance>(GetParent()->GetParent());
	if (parentOfParent->IsDoodadInSet(m_Index))
	{
		if (m_PortalVisibilityState)
		{
			return CM2_Base_Instance::Accept(visitor);
		}
	}
}

#endif

#endif
