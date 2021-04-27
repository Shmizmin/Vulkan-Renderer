Texture2D<float4> texSampler : register(t1);
SamplerState texSamplerState : register(s1);

float interp(float old_value, float old_bottom, float old_top, float new_bottom, float new_top)
{
	return (old_value - old_bottom) / (old_top - old_bottom) * (new_top - new_bottom) + new_bottom;
}

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
	float3 prod = interp(dot(input.inNormal, float3(1.0f, 0.2f, 0.0f)), -1.0f, 1.0f, 0.0f, 1.0f);
	
	float3 dp = pow(prod, 4.0f);
	
	float4 col = float4(dp, 1.0f);
	
	return col * texSampler.Sample(texSamplerState, input.inTexCoord);
}