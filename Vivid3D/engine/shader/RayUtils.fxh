

RaytracingAccelerationStructure g_TLAS;
ConstantBuffer<Constants>       g_ConstantsCB;

struct Vertex {

	float3 position; //0
	float4 color; //3
	float3 texture; //7
	float3 normal; //10
	float3 binormal; //13
	float3 tangent; //16 
	float4 bone_ids; //19
	float4 bone_weights; //23
};

struct Triangle{

    uint3 Indices;

};

StructuredBuffer<Vertex> Vertices;
StructuredBuffer<Triangle> Triangles;

StructuredBuffer<uint4> Offsets;
StructuredBuffer<float4> LightsBuffer;

static const float PI = 3.14159265358979323846;
#define MAX_REFLECTION_DISTANCE 50.0 

static const int MAX_REFLECTION_RECURSION_DEPTH = 2;

PrimaryRayPayload CastPrimaryRay(RayDesc ray, uint Recursion)
{
    PrimaryRayPayload payload = {float3(0, 0, 0), 0.0, Recursion};

    // Manually terminate the recusrion as the driver doesn't check the recursion depth.
    if (Recursion >= g_ConstantsCB.MaxRecursion)
    {
        // set pink color for debugging
        payload.Color = float3(0,0,0);
        return payload;
    }
    TraceRay(g_TLAS,            // Acceleration structure
             RAY_FLAG_NONE,
             ~0,                // Instance inclusion mask - all instances are visible
             PRIMARY_RAY_INDEX, // Ray contribution to hit group index (aka ray type)
             HIT_GROUP_STRIDE,  // Multiplier for geometry contribution to hit
                                // group index (aka the number of ray types)
             PRIMARY_RAY_INDEX, // Miss shader index
             ray,
             payload);
    return payload;
}

float3 TraceReflectionRay(float3 rayOrigin, float3 rayDirection, int recursionDepth)
{
    if (recursionDepth >= MAX_REFLECTION_RECURSION_DEPTH)
        return float3(0.0, 0.0, 0.0); // Terminate recursion if max depth reached

    RayDesc reflectionRay;
    reflectionRay.Origin = rayOrigin + rayDirection * SMALL_OFFSET; // Offset to avoid self-intersection
    reflectionRay.Direction = rayDirection;
    reflectionRay.TMin = 0.01;
    reflectionRay.TMax = MAX_REFLECTION_DISTANCE;

    PrimaryRayPayload reflectionPayload;
    reflectionPayload.Recursion = recursionDepth;

    TraceRay(g_TLAS, RAY_FLAG_NONE, 0xFF, 0, 1, 0, reflectionRay, reflectionPayload);

    // Compute reflection color
    float3 reflectionColor = reflectionPayload.Color;

    return reflectionColor;
}
ShadowRayPayload CastShadow(RayDesc ray, uint Recursion)
{
    // By default initialize Shading with 0.
    // With RAY_FLAG_SKIP_CLOSEST_HIT_SHADER, only intersection and any-hit shaders are executed.
    // Any-hit shader is not used in this tutorial, intersection shader can not write to payload, 
    // so on intersection payload. Shading is always 0,
    // on miss shader payload.Shading will be initialized with 1.
    // With this flags shadow casting executed as fast as possible.
    ShadowRayPayload payload = {0.0, Recursion};
    
    // Manually terminate the recusrion as the driver doesn't check the recursion depth.
    if (Recursion >= g_ConstantsCB.MaxRecursion)
    {
        payload.Shading = 1.0;
        return payload;
    }
    TraceRay(g_TLAS,            // Acceleration structure
             RAY_FLAG_FORCE_OPAQUE | RAY_FLAG_SKIP_CLOSEST_HIT_SHADER | RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH,
             OPAQUE_GEOM_MASK,  // Instance inclusion mask - only opaque instances are visible
             SHADOW_RAY_INDEX,  // Ray contribution to hit group index (aka ray type)
             HIT_GROUP_STRIDE,  // Multiplier for geometry contribution to hit 
                                // group index (aka the number of ray types)
             SHADOW_RAY_INDEX,  // Miss shader index
             ray,
             payload);
    return payload;
}

// Calculate perpendicular to specified direction.
void GetRayPerpendicular(float3 dir, out float3 outLeft, out float3 outUp)
{
    const float3 a    = abs(dir);
    const float2 c    = float2(1.0, 0.0);
    const float3 axis = a.x < a.y ? (a.x < a.z ? c.xyy : c.yyx) :
                                    (a.y < a.z ? c.xyx : c.yyx);
    outLeft = normalize(cross(dir, axis));
    outUp   = normalize(cross(dir, outLeft));
}

// Returns a ray within a cone.
float3 DirectionWithinCone(float3 dir, float2 offset)
{
    float3 left, up;
    GetRayPerpendicular(dir, left, up);
    return normalize(dir + left * offset.x + up * offset.y);
}


float3 FresnelSchlick(float cosTheta, float3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;
    return NdotV / (NdotV * (1.0 - k) + k);
}

float GeometrySmith(float3 normal, float3 viewDir, float3 lightDir, float roughness)
{
    float NdotV = max(dot(normal, viewDir), 0.0);
    float NdotL = max(dot(normal, lightDir), 0.0);
    float ggx1 = GeometrySchlickGGX(NdotV, roughness);
    float ggx2 = GeometrySchlickGGX(NdotL, roughness);
    return ggx1 * ggx2;
}

float DistributionGGX(float3 normal, float3 halfVector, float roughness)
{
    float alpha = roughness * roughness;
    float alpha2 = alpha * alpha;
    float NdotH = max(dot(normal, halfVector), 0.0);
    float NdotH2 = NdotH * NdotH;

    float nom = alpha2;
    float denom = (NdotH2 * (alpha2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

float3 CalculateLighting(float3 fPos,float3 diffuse,float3 normal, float3 viewDir, float3 lightDir, float3 lightColor, float lightIntensity, float roughness, float metalness,int recursion)
{
      normal = normalize(normal);
    viewDir = normalize(viewDir);
    lightDir = normalize(lightDir);

    float3 halfVector = normalize(lightDir + viewDir);

    // Fresnel-Schlick approximation
    float3 F0 = lerp(float3(0.04, 0.04, 0.04), diffuse, metalness);
    float3 F = FresnelSchlick(max(dot(halfVector, viewDir), 0.0), F0);

    // Geometry function (Smith Schlick-GGX)
    float G = GeometrySmith(normal, viewDir, lightDir, roughness);

    // Normal Distribution Function (GGX)
    float D = DistributionGGX(normal, halfVector, roughness);

    // Specular and diffuse components
    float3 kS = F;
    float3 kD = (1.0 - kS) * (1.0 - metalness);

    float NdotL = max(dot(normal, lightDir), 0.0);
    float NdotV = max(dot(normal, viewDir), 0.0);
    
    // Specular BRDF
    float3 specular = (D * G * F) / max(4.0 * NdotV * NdotL, 0.001);

    // Calculate reflection
    float3 reflectDir = normalize(reflect(-viewDir, normal));   
    float3 envMapColor = float3(0.0, 0.0, 0.0);
    if (recursion < MAX_REFLECTION_RECURSION_DEPTH)
    {
        envMapColor = TraceReflectionRay(fPos, reflectDir, recursion + 1);
        // Apply Fresnel to reflection
        envMapColor *= F;
    }

    // Combine direct and indirect lighting
    float3 directLighting = lightIntensity * NdotL * (kD * diffuse / PI + specular);
    float3 indirectLighting = envMapColor;

    return directLighting + indirectLighting;
}




// Calculate lighting.
void LightingPass(inout float3 Color, float3 Pos, float3 Norm, uint Recursion)
{
   RayDesc ray;
    float3  col = float3(0.0, 0.0, 0.0);

    // Add a small offset to avoid self-intersections.
    ray.Origin = Pos + Norm * SMALL_OFFSET;
    ray.TMin   = 0.0;

    for (int i = 0; i < NUM_LIGHTS; ++i)
    {
        // Limit max ray length by distance to light source.
        ray.TMax = distance(g_ConstantsCB.LightPos[i].xyz, Pos) * 1.01;

        float3 rayDir = normalize(g_ConstantsCB.LightPos[i].xyz - Pos);
        float  NdotL   = max(0.0, dot(Norm, rayDir));

        // Optimization - don't trace rays if NdotL is zero or negative
        if (NdotL > 0.0)
        {
            // Cast multiple rays that are distributed within a cone.
            int   PCFSamples = Recursion > 1 ? min(1, g_ConstantsCB.ShadowPCF) : g_ConstantsCB.ShadowPCF;
            float shading    = 0.0;
            for (int j = 0; j < PCFSamples; ++j)
            {
                float2 offset = float2(g_ConstantsCB.DiscPoints[j / 2][(j % 2) * 2], g_ConstantsCB.DiscPoints[j / 2][(j % 2) * 2 + 1]);
                ray.Direction = DirectionWithinCone(rayDir, offset * 0.005);
                shading       += saturate(CastShadow(ray, Recursion).Shading);
            }
            
            shading = PCFSamples > 0 ? shading / float(PCFSamples) : 1.0;

            col += Color * g_ConstantsCB.LightColor[i].rgb * NdotL * shading;
        }
        col += Color * 0.125;
    }
    Color = col * (1.0 / float(NUM_LIGHTS)) + g_ConstantsCB.AmbientColor.rgb;
    
}
