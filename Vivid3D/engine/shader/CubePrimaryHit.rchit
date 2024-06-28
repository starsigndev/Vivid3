
#include "structures.fxh"
#include "RayUtils.fxh"

StructuredBuffer<float4> UVsBuffer;
StructuredBuffer<float4> NormalsBuffer;//: register(t1);
StructuredBuffer<uint4>  PrimitivesBuffer;// : register(t2);
StructuredBuffer<uint4> Offsets;
Texture2D    g_CubeTextures[NUM_TEXTURES];
SamplerState g_SamLinearWrap;

[shader("closesthit")]
void main(inout PrimaryRayPayload payload, in BuiltInTriangleIntersectionAttributes attr)
{
    // Calculate triangle barycentrics.
    float3 barycentrics = float3(1.0 - attr.barycentrics.x - attr.barycentrics.y, attr.barycentrics.x, attr.barycentrics.y);


    uint real_i = PrimitiveIndex()+Offsets[InstanceID()].y;

    // Get vertex indices for primitive.
      uint3 primitive = PrimitivesBuffer[real_i].xyz;



    // Calculate texture coordinates.
    float2 uv = UVsBuffer[primitive.x].xy * barycentrics.x +
                UVsBuffer[primitive.y].xy * barycentrics.y +
                UVsBuffer[primitive.z].xy * barycentrics.z;

    // Calculate and transform triangle normal.
    float3 normal = NormalsBuffer[primitive.x].xyz * barycentrics.x +
                    NormalsBuffer[primitive.y].xyz * barycentrics.y +
                    NormalsBuffer[primitive.z].xyz * barycentrics.z;
    normal = normalize(mul((float3x3) ObjectToWorld3x4(), normal));

    // Sample texturing. Ray tracing shaders don't support LOD calculation, so we must specify LOD and apply filtering.
    payload.Color = g_CubeTextures[NonUniformResourceIndex(InstanceID())].SampleLevel(g_SamLinearWrap, uv, 0).rgb;
    payload.Depth = RayTCurrent();
    

    // Apply lighting.
    float3 rayOrigin = WorldRayOrigin() + WorldRayDirection() * RayTCurrent();
    LightingPass(payload.Color, rayOrigin, normal, payload.Recursion + 1);
}
