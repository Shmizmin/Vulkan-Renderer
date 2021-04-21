Texture2D<float4> texSampler : register(t1);
SamplerState texSamplerState : register(s1);

struct PixelInput
{
	float4 inPosition : SV_Position;
	float3 inColor : COLOR;
	float2 inTexCoord : TEXCOORD;
	float3 inNormal : NORMAL;
};

float4 main(PixelInput input) : SV_Target
{
	float4 pos = input.inPosition;
	float3 prod = ((dot(input.inNormal, float3(1.0f, 0.2f, 0.0f)) + 1.0f) * 0.5f);
	
	float3 dp = pow(prod, 3);
	
	float4 col = float4(dp, 1.0f);
	
	return col * texSampler.Sample(texSamplerState, input.inTexCoord);
}