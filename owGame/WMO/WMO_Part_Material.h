#pragma once

#ifdef USE_WMO_MODELS

#include "WMO_Headers.h"

// FORWARD BEGIN
class CWMO;
// FORWARD END

namespace
{
__declspec(align(16)) struct WMO_Part_MaterialMaterialProperties
{
	WMO_Part_MaterialMaterialProperties()
		: BlendMode(0)
		, MOCVExists(0)
	{}

	uint32 BlendMode;
	uint32 MOCVExists;
	glm::vec2   m_Pad;
	//-------------------------- ( 32 bytes )
};
}

class WMO_Part_Material 
	: public MaterialProxieT<WMO_Part_MaterialMaterialProperties>
{
public:
	WMO_Part_Material(IRenderDevice& RenderDevice, const CWMO& WMOModel, const SWMO_MaterialDef& WMOMaterialProto);
	virtual ~WMO_Part_Material();

	const std::shared_ptr<IDepthStencilState>& GetDepthStencilState() const { return m_DepthStencilState; }
	const std::shared_ptr<IBlendState>& GetBlendState() const { return m_BlendState; };
	const std::shared_ptr<IRasterizerState>& GetRasterizerState() const { return m_RasterizerState; };

    void UpdateConstantBuffer() const override;

private:
	
	MaterialProperties*            m_pProperties;

	std::shared_ptr<IDepthStencilState> m_DepthStencilState;
	std::shared_ptr<IBlendState>        m_BlendState;
	std::shared_ptr<IRasterizerState>   m_RasterizerState;

private:
	const CWMO& m_WMOModel;
};

#endif
