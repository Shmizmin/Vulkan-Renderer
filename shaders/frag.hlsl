Texture2D<float4> texSampler : register(t1);
SamplerState texSamplerState : register(s1);

struct PixelInput
{
	float3 inColor : COLOR;
	float2 inTexCoord : TEXCOORD;
};

float4 PSMain(PixelInput input) : SV_Target
{
	return texSampler.Sample(texSamplerState, input.inTexCoord);
}