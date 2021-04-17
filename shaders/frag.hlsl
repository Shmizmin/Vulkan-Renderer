Texture2D<float4> texSampler : register(t1);
SamplerState texSamplerState : register(s1);

struct PixelInput
{
	float4 inPosition : SV_Position;
	float3 inColor : COLOR;
	float2 inTexCoord : TEXCOORD;
};

float4 main(PixelInput input) : SV_Target
{
	float4 pos = input.inPosition;
	
	return texSampler.Sample(texSamplerState, input.inTexCoord);
}