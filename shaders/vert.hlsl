cbuffer UniformBufferObject : register(b0)
{
	float4x4 model;
	float4x4 view;
	float4x4 proj;
};

struct VertexInput
{
	float3 inPosition : POSITION;
	float3 inColor : COLOR;
	float2 inTexCoord : TEXCOORD;
};

struct VertexOutput
{
	float4 outPosition : SV_Position;
	float3 outColor : COLOR;
	float2 outTextCoord : TEXCOORD;
};

VertexOutput main(VertexInput input)
{
	VertexOutput output;
	
	output.outPosition = mul(proj, mul(view, mul(model, float4(input.inPosition, 1.0f))));
	output.outColor = input.inColor;
	output.outTextCoord = input.inTexCoord;
	
	return output;
}