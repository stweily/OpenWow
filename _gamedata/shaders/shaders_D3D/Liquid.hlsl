#include "CommonInclude.hlsl"

struct VertexShaderInput
{
	float3 position : POSITION;
	float3 texCoord : TEXCOORD0;
};

struct VertexShaderOutput
{
	float4 positionVS : SV_POSITION;
	float4 positionWS : POSITION;
	float3 texCoord : TEXCOORD0;
};


static const uint LiquidType_Water = 0u;
static const uint LiquidType_Ocean = 1u;
static const uint LiquidType_Magma = 2u;
static const uint LiquidType_Slime = 3u;


// Uniforms
cbuffer Material : register(b4)
{
	float3 gColorLight;
	float gShallowAlpha;
	
	float3 gColorDark;
	float gDeepAlpha;
	
	uint gLiquidType;
	float3 __padding;
};


// Textures
Texture2D DiffuseTexture        : register(t0);


VertexShaderOutput VS_main(VertexShaderInput IN)
{
	const float4x4 mvp = mul(PF.Projection, mul(PF.View, PO.Model));
	
	VertexShaderOutput OUT;
	OUT.positionVS = mul(mvp, float4(IN.position, 1.0f));
	OUT.positionWS = float4(IN.position, 1.0f);
	OUT.texCoord = IN.texCoord;
	return OUT;
}

DefferedRenderPSOut PS_main(VertexShaderOutput IN) : SV_TARGET
{
	const float2 texCoord = float2(IN.texCoord.x, 1.0f - IN.texCoord.y);

	float4 diffuseColor = float4(0.0f, 0.3f, 1.0f, 1.0f);
	
	if ((gLiquidType == LiquidType_Water) || (gLiquidType == LiquidType_Ocean))
	{	
		float waterDepth = DiffuseTexture.Sample(LinearRepeatSampler, texCoord).a;

		float3 resultColor = float3(1.0f, 1.0f, 1.0f) * waterDepth;
		resultColor += gColorDark * (1.0f - waterDepth);
		
		diffuseColor = float4(resultColor, 0.5f + IN.texCoord.z);
	}
	else if ((gLiquidType == LiquidType_Magma) || (gLiquidType == LiquidType_Slime))
	{
		diffuseColor = DiffuseTexture.Sample(LinearRepeatSampler, texCoord);
	}
	
	DefferedRenderPSOut OUT;
	OUT.Diffuse = diffuseColor;
	OUT.Specular = float4(0.0f, 0.0f, 0.0f, 1.0f);
	OUT.NormalVS = float4(normalize(float3(0.0f, 1.0f, 0.0f)), 0.0f);
	return OUT;
}