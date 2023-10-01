Texture2D tex : register(t0);

sampler smp : register(s0);

cbuffer Transform : register(b0)
{
    matrix transform;
};

struct VertexInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

VertexOutput VSMain(VertexInput input)
{
    VertexOutput output;
    output.position = mul(transform, float4(input.position, 1.f));
    output.uv = input.uv;
    
    return output;
}

float4 PSMain(VertexOutput input) : SV_Target0
{
    float4 texColor = tex.Sample(smp, input.uv);
    return texColor;
}