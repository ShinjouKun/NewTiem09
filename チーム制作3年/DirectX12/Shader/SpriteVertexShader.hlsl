#include "SpliteShaderHeader.hlsli"

VSOutput VSmain(float4 pos:POSITION, float2 uv : TEXCOORD)
{
	VSOutput output;//ピクセルシェーダに渡す値
	output.svpos = mul(mat, pos);
	output.uv = uv;
	return output;
}