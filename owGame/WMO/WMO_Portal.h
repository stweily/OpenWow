#pragma once

#ifdef USE_WMO_MODELS
#ifdef USE_WMO_PORTALS_CULLING

class CWMOPortalInstance
	: public IPortal
{
public:
	CWMOPortalInstance(const std::weak_ptr<IPortalRoom>& RoomInner, const std::weak_ptr<IPortalRoom>& RoomOuter, const std::vector<glm::vec3>& PortalVertices, const Plane& PortalPlane);
	virtual ~CWMOPortalInstance();

	const std::vector<glm::vec3>& GetVertices() const;

	// IPortal
	Frustum CreatePolyFrustum(glm::vec3 CameraPosition) const override final;
	bool IsVisible(const Frustum& Frustum) const override final;
	bool IsVisible(const std::vector<Plane>& Planes) const override final;
	bool IsPositive(const glm::vec3& CameraPosition) const override final;
	std::shared_ptr<IPortalRoom> GetInnerRoom() const override final;
	std::shared_ptr<IPortalRoom> GetOuterRoom() const override final;
	std::shared_ptr<IPortalRoom> GetRoomObject(glm::vec3 CameraPosition) const override final;

private:
	std::weak_ptr<IPortalRoom> m_RoomInner;
	std::weak_ptr<IPortalRoom> m_RoomOuter;
	std::vector<glm::vec3>     m_Vertices;
	Plane				       m_Plane;
};

#endif
#endif