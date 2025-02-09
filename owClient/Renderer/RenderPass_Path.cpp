#include "stdafx.h"

// General
#include "RenderPass_Path.h"

// Additional
#include "World/WorldServer.h"
#include "Objects/GameObjects/WoWGameObjectMOTransport.h"

CRenderPass_Path::CRenderPass_Path(IRenderDevice& RenderDevice, CWorldServer& WoWWorld)
	: RenderPassPipelined(RenderDevice)
	, m_ServerWorld(WoWWorld)
{
	m_PerObjectConstantBuffer = GetRenderDevice().GetObjectsFactory().CreateConstantBuffer(PerObject());
}

CRenderPass_Path::~CRenderPass_Path()
{}



//
// IRenderPass
//
void CRenderPass_Path::Render(RenderEventArgs & e)
{
	m_ServerWorld.Accept(this);
}



//
// IRenderPassPipelined
//
std::shared_ptr<IRenderPassPipelined> CRenderPass_Path::ConfigurePipeline(std::shared_ptr<IRenderTarget> RenderTarget)
{
	__super::ConfigurePipeline(RenderTarget);

	std::shared_ptr<IShader> vertexShader = GetRenderDevice().GetObjectsFactory().LoadShader(EShaderType::VertexShader, "3D/Debug.hlsl", "VS_main");
	vertexShader->LoadInputLayoutFromReflector();

	std::shared_ptr<IShader> pixelShader = GetRenderDevice().GetObjectsFactory().LoadShader(EShaderType::PixelShader, "3D/Debug.hlsl", "PS_main");
	
	//m_ShaderInstancesBufferParameter = &vertexShader->GetShaderParameterByName("Instances");
	//_ASSERT(m_ShaderInstancesBufferParameter->IsValid());

	m_MaterialDebug = MakeShared(MaterialDebug, GetRenderDevice());

	// PIPELINES
	GetPipeline().GetBlendState()->SetBlendMode(disableBlending);
	GetPipeline().GetDepthStencilState()->SetDepthMode(enableDepthWrites);
	GetPipeline().GetRasterizerState()->SetCullMode(IRasterizerState::CullMode::None);
	GetPipeline().GetRasterizerState()->SetFillMode(IRasterizerState::FillMode::Solid, IRasterizerState::FillMode::Solid);
	GetPipeline().SetRenderTarget(RenderTarget);
	GetPipeline().SetShader(vertexShader);
	GetPipeline().SetShader(pixelShader);

	return shared_from_this();
}

EVisitResult CRenderPass_Path::VisitWoW(const std::shared_ptr<CowServerWorldObject>& WoWWorldObject)
{
	std::vector<glm::vec3> pointsXYZ;

	if (auto woWGameObjectMOTransport = std::dynamic_pointer_cast<CowServerGameObject_MOTransport>(WoWWorldObject))
	{
		const auto& wowPath = woWGameObjectMOTransport->GetWoWPath();
		if (wowPath == nullptr)
			return EVisitResult::AllowVisitChilds;

		auto& wowWorld = woWGameObjectMOTransport->GetWoWWorld();

		uint32 mapID = UINT32_MAX;
		if (auto map = wowWorld.GetWorldClient().GetMap())
			mapID = map->GetMapID();

		const auto& wowPathNodes = wowPath->GetPathNodes();
		std::for_each(wowPathNodes.begin(), wowPathNodes.end(), [&pointsXYZ, mapID](const std::shared_ptr<CWoWPathNode>& PathNode) {
			if (mapID == PathNode->GetMapID())
			{
				glm::vec3 position = PathNode->GetPosition();
				position.y += 0.1f;
				pointsXYZ.push_back(position);
			}
		});
	}

	if (auto woWUnit = std::dynamic_pointer_cast<CowServerUnit>(WoWWorldObject))
	{
		const auto& wowPath = woWUnit->m_WoWPath;
		if (wowPath == nullptr)
			return EVisitResult::AllowVisitChilds;

		const auto& wowPathNodes = wowPath->GetPathNodes();
		std::for_each(wowPathNodes.begin(), wowPathNodes.end(), [&pointsXYZ](const std::shared_ptr<CWoWPathNode>& PathNode) {
			glm::vec3 position = PathNode->GetPosition();
			position.y += 0.1f;
			pointsXYZ.push_back(position);
		});
	}

	if (pointsXYZ.size() < 2)
		return EVisitResult::AllowVisitChilds;

	BindPerObjectData(PerObject());

	m_WaypointGeometry = GetRenderDevice().GetPrimitivesFactory().CreateLines(pointsXYZ);

	m_MaterialDebug->Bind(GetPipeline().GetPixelShaderPtr());
	m_WaypointGeometry->Render(GetPipeline().GetVertexShaderPtr());
	m_MaterialDebug->Unbind(GetPipeline().GetPixelShaderPtr());

	return EVisitResult::AllowVisitChilds;
}



//
// Protected
//
void CRenderPass_Path::BindPerObjectData(const PerObject& PerObject)
{
	m_PerObjectConstantBuffer->Set(PerObject);

	for (const auto& shaderIt : GetPipeline().GetShaders())
	{
		if (auto* perObjectParam = shaderIt.second->GetShaderParameterByName("PerObject"))
		{
			perObjectParam->SetConstantBuffer(m_PerObjectConstantBuffer);
			perObjectParam->Bind();
		}
	}
}