#include "pch.h"
#include "SolarisRenderer.h"
#include "SceneGraph.h"
#include "RTMesh.h"
#include "Node.h"
#include "Mesh3D.h"
#include "Draw2D.h"
InstanceMatrix ConvertToInstanceMatrix(const float4x4& matrix)
{
	InstanceMatrix instanceMatrix;

	// Copy the first three rows of the float4x4 to the InstanceMatrix
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			instanceMatrix.data[row][col] = matrix[row][col];
		}
	}

	return instanceMatrix;
}

SolarisRenderer::SolarisRenderer() {

//	m_RTPipeline = new RTPipeline;

//	m_RayTracingSRB = m_RTPipeline->GetSRB();
	m_Draw = new Draw2D;
	BufferDesc BuffDesc;
	BuffDesc.Name = "Constant buffer";
	BuffDesc.Size = sizeof(m_Constants);
	BuffDesc.Usage = USAGE_DEFAULT;
	BuffDesc.BindFlags = BIND_UNIFORM_BUFFER;

	Engine::m_pDevice->CreateBuffer(BuffDesc, nullptr, &m_ConstantsCB);

	CreatePipeline();

	TextureDesc RTDesc = {};
	RTDesc.Name = "Color buffer";
	RTDesc.Type = RESOURCE_DIM_TEX_2D;
	RTDesc.Width = Engine::GetFrameWidth();
	RTDesc.Height = Engine::GetFrameHeight();
	RTDesc.BindFlags = BIND_UNORDERED_ACCESS | BIND_SHADER_RESOURCE;
	RTDesc.ClearValue.Format = m_ColorBufferFormat;
	RTDesc.Format = m_ColorBufferFormat;

	Engine::m_pDevice->CreateTexture(RTDesc, nullptr, &m_pColorRT);

	m_Constants.ClipPlanes = float2{ 0.1f, 100.0f };
	m_Constants.ShadowPCF = 1;
	m_Constants.MaxRecursion = std::min(Uint32{ 6 }, m_MaxRecursionDepth);

	// Sphere constants.
	m_Constants.SphereReflectionColorMask = { 0.81f, 1.0f, 0.45f };
	m_Constants.SphereReflectionBlur = 1;

	// Glass cube constants.
	m_Constants.GlassReflectionColorMask = { 0.22f, 0.83f, 0.93f };
	m_Constants.GlassAbsorption = 0.5f;
	m_Constants.GlassMaterialColor = { 0.33f, 0.93f, 0.29f };
	m_Constants.GlassIndexOfRefraction = { 1.5f, 1.02f };
	m_Constants.GlassEnableDispersion = 0;

	// Wavelength to RGB and index of refraction interpolation factor.
	m_Constants.DispersionSamples[0] = { 0.140000f, 0.000000f, 0.266667f, 0.53f };
	m_Constants.DispersionSamples[1] = { 0.130031f, 0.037556f, 0.612267f, 0.25f };
	m_Constants.DispersionSamples[2] = { 0.100123f, 0.213556f, 0.785067f, 0.16f };
	m_Constants.DispersionSamples[3] = { 0.050277f, 0.533556f, 0.785067f, 0.00f };
	m_Constants.DispersionSamples[4] = { 0.000000f, 0.843297f, 0.619682f, 0.13f };
	m_Constants.DispersionSamples[5] = { 0.000000f, 0.927410f, 0.431834f, 0.38f };
	m_Constants.DispersionSamples[6] = { 0.000000f, 0.972325f, 0.270893f, 0.27f };
	m_Constants.DispersionSamples[7] = { 0.000000f, 0.978042f, 0.136858f, 0.19f };
	m_Constants.DispersionSamples[8] = { 0.324000f, 0.944560f, 0.029730f, 0.47f };
	m_Constants.DispersionSamples[9] = { 0.777600f, 0.871879f, 0.000000f, 0.64f };
	m_Constants.DispersionSamples[10] = { 0.972000f, 0.762222f, 0.000000f, 0.77f };
	m_Constants.DispersionSamples[11] = { 0.971835f, 0.482222f, 0.000000f, 0.62f };
	m_Constants.DispersionSamples[12] = { 0.886744f, 0.202222f, 0.000000f, 0.73f };
	m_Constants.DispersionSamples[13] = { 0.715967f, 0.000000f, 0.000000f, 0.68f };
	m_Constants.DispersionSamples[14] = { 0.459920f, 0.000000f, 0.000000f, 0.91f };
	m_Constants.DispersionSamples[15] = { 0.218000f, 0.000000f, 0.000000f, 0.99f };
	m_Constants.DispersionSampleCount = 4;

	m_Constants.AmbientColor = float4(1.f, 1.f, 1.f, 0.f) * 0.015f;
	m_Constants.LightPos[0] = { 8.00f, +8.0f, +0.00f, 0.f };
	m_Constants.LightColor[0] = { 1.00f, +0.8f, +0.80f, 0.f };
	m_Constants.LightPos[1] = { 0.00f, +4.0f, -5.00f, 0.f };
	m_Constants.LightColor[1] = { 0.85f, +1.0f, +0.85f, 0.f };

	// Random points on disc.
	m_Constants.DiscPoints[0] = { +0.0f, +0.0f, +0.9f, -0.9f };
	m_Constants.DiscPoints[1] = { -0.8f, +1.0f, -1.1f, -0.8f };
	m_Constants.DiscPoints[2] = { +1.5f, +1.2f, -2.1f, +0.7f };
	m_Constants.DiscPoints[3] = { +0.1f, -2.2f, -0.2f, +2.4f };
	m_Constants.DiscPoints[4] = { +2.4f, -0.3f, -3.0f, +2.8f };
	m_Constants.DiscPoints[5] = { +2.0f, -2.6f, +0.7f, +3.5f };
	m_Constants.DiscPoints[6] = { -3.2f, -1.6f, +3.4f, +2.2f };
	m_Constants.DiscPoints[7] = { -1.8f, -3.2f, -1.1f, +3.6f };
}



void SolarisRenderer::PreRender()
{
	if (GetSceneGraph()->IsUpdated()) {

		CreateStructures();
		GetSceneGraph()->UpdateComplete();

	}

	if (m_RayTracedShadows) {

	}
	else {
		GetSceneGraph()->RenderShadows();
	}
}

void SolarisRenderer::Render() {

	//GetSceneGraph()->Render();
	//float3 CameraWorldPos = float3::MakeVector(m_Camera.GetWorldMatrix()[3]);
	//auto   CameraViewProj = m_Camera.GetViewMatrix() * m_Camera.GetProjMatrix();
	auto cam = GetSceneGraph()->GetCamera();

	if (m_Meshes.size() == 0) return;

	m_Constants.CameraPos = float4{ cam->GetPosition(), 1.0f};
	m_Constants.InvViewProj = (cam->GetWorldMatrix() * cam->GetProjection()).Inverse().Transpose();


	Engine::m_pImmediateContext->UpdateBuffer(m_ConstantsCB, 0, sizeof(m_Constants), &m_Constants, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	m_pRayTracingSRB->GetVariableByName(SHADER_TYPE_RAY_GEN, "g_ColorBuffer")->Set(m_pColorRT->GetDefaultView(TEXTURE_VIEW_UNORDERED_ACCESS));

	Engine::m_pImmediateContext->SetPipelineState(m_pRayTracingPSO);
	Engine::m_pImmediateContext->CommitShaderResources(m_pRayTracingSRB, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);


	TraceRaysAttribs Attribs;
	Attribs.DimensionX = m_pColorRT->GetDesc().Width;
	Attribs.DimensionY = m_pColorRT->GetDesc().Height;
	Attribs.pSBT = m_SBT;

	Engine::m_pImmediateContext->TraceRays(Attribs);

	ITextureView* view = m_pColorRT->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);


	m_Draw->Rect(new Texture2D(view), float2(0, Attribs.DimensionY), float2(Attribs.DimensionX, -(int)Attribs.DimensionY), float4(1, 1, 1, 1));


}

void SolarisRenderer::CreateStructures() {

	auto graph = GetSceneGraph();
	auto meshes = graph->GetRTMeshes();

	m_Meshes = meshes;

	if (m_Meshes.size() == 0) return;

	if (m_Meshes.size() > 0) {
		CreateTopLevel();
	}
	
	CreateSBT();

	UpdatePrimitives();

 }

void SolarisRenderer::UpdatePrimitives() {

	//HLSL::CubeAttribs Attribs;

	HLSL::CubeAttribs Attribs;


	for (auto m : m_Meshes) {

		int u = 0;

		for (auto v : m->GetMesh()->GetVertices())
		{

			Attribs.UVs[u] = { v.texture.x,v.texture.y,0,0 };
			Attribs.Normals[u] = { v.normal.x,v.normal.y,v.normal.z,0 };
			u++;
		}
		//Attribs.Primitives
		int tri = 0;
		for (auto t : m->GetMesh()->GetTris()) {

			Attribs.Primitives[tri] = uint4{ t.v0,t.v1,t.v2,0 };

		}


	}

	BufferDesc BuffDesc;
	BuffDesc.Name = "Cube Attribs";
	BuffDesc.Usage = USAGE_IMMUTABLE;
	BuffDesc.BindFlags = BIND_UNIFORM_BUFFER;
	BuffDesc.Size = sizeof(Attribs);

	BufferData BufData = { &Attribs, BuffDesc.Size };

	Engine::m_pDevice->CreateBuffer(BuffDesc, &BufData, &m_RenderAttribsCB);

	VERIFY_EXPR(m_CubeAttribsCB != nullptr);

	m_pRayTracingSRB->GetVariableByName(SHADER_TYPE_RAY_CLOSEST_HIT, "g_CubeAttribsCB")->Set(m_RenderAttribsCB);

}

void SolarisRenderer::CreateTopLevel() {


	TopLevelASDesc TLASDesc;
	TLASDesc.Name = "SCENE TLAS";
	TLASDesc.MaxInstanceCount = m_Meshes.size();
	TLASDesc.Flags = RAYTRACING_BUILD_AS_ALLOW_UPDATE | RAYTRACING_BUILD_AS_PREFER_FAST_TRACE;
	Engine::m_pDevice->CreateTLAS(TLASDesc, &m_TLAS);

	m_pRayTracingSRB->GetVariableByName(SHADER_TYPE_RAY_GEN, "g_TLAS")->Set(m_TLAS);
	m_pRayTracingSRB->GetVariableByName(SHADER_TYPE_RAY_CLOSEST_HIT, "g_TLAS")->Set(m_TLAS);
	if (!m_ScratchBuffer)
	{
		BufferDesc BuffDesc;
		BuffDesc.Name = "TLAS Scratch Buffer";
		BuffDesc.Usage = USAGE_DEFAULT;
		BuffDesc.BindFlags = BIND_RAY_TRACING;
		BuffDesc.Size = std::max(m_TLAS->GetScratchBufferSizes().Build, m_TLAS->GetScratchBufferSizes().Update);

		Engine::m_pDevice->CreateBuffer(BuffDesc, nullptr, &m_ScratchBuffer);
		VERIFY_EXPR(m_ScratchBuffer != nullptr);
	}

	if (!m_InstanceBuffer)
	{
		BufferDesc BuffDesc;
		BuffDesc.Name = "TLAS Instance Buffer";
		BuffDesc.Usage = USAGE_DEFAULT;
		BuffDesc.BindFlags = BIND_RAY_TRACING;
		BuffDesc.Size = TLAS_INSTANCE_DATA_SIZE * m_Meshes.size();

		Engine::m_pDevice->CreateBuffer(BuffDesc, nullptr, &m_InstanceBuffer);
		VERIFY_EXPR(m_InstanceBuffer != nullptr);
	}

	std::vector<TLASBuildInstanceData> Instances;

	int i = 0;
	for (auto m : m_Meshes) {

		TLASBuildInstanceData inst;

		auto name = m->GetName();
		char* myString = new char[strlen(name.c_str()) + 1];
		strcpy(myString, name.c_str());
		inst.InstanceName = myString;
		inst.CustomId = i;
		inst.pBLAS = m->GetBLAS();
		InstanceMatrix mat = ConvertToInstanceMatrix(m->GetNode()->GetWorldMatrix());
		inst.Transform = mat;
		inst.Mask = OPAQUE_GEOM_MASK;
		Instances.push_back(inst);

	}

	BuildTLASAttribs Attribs;
	Attribs.pTLAS = m_TLAS;
	Attribs.Update = false;

	// Scratch buffer will be used to store temporary data during TLAS build or update.
	// Previous content in the scratch buffer will be discarded.
	Attribs.pScratchBuffer = m_ScratchBuffer;

	// Instance buffer will store instance data during TLAS build or update.
	// Previous content in the instance buffer will be discarded.
	Attribs.pInstanceBuffer = m_InstanceBuffer;

	// Instances will be converted to the format that is required by the graphics driver and copied to the instance buffer.
	Attribs.pInstances = Instances.data();
	Attribs.InstanceCount = Instances.size();

	// Bind hit shaders per instance, it allows you to change the number of geometries in BLAS without invalidating the shader binding table.
	Attribs.BindingMode = HIT_GROUP_BINDING_MODE_PER_INSTANCE;
	Attribs.HitGroupStride = HIT_GROUP_STRIDE;

	// Allow engine to change resource states.
	Attribs.TLASTransitionMode = RESOURCE_STATE_TRANSITION_MODE_TRANSITION;
	Attribs.BLASTransitionMode = RESOURCE_STATE_TRANSITION_MODE_TRANSITION;
	Attribs.InstanceBufferTransitionMode = RESOURCE_STATE_TRANSITION_MODE_TRANSITION;
	Attribs.ScratchBufferTransitionMode = RESOURCE_STATE_TRANSITION_MODE_TRANSITION;

	Engine::m_pImmediateContext->BuildTLAS(Attribs);


}

void SolarisRenderer::CreateSBT() {

	ShaderBindingTableDesc SBTDesc;
	SBTDesc.Name = "SBT";
	SBTDesc.pPSO = m_pRayTracingPSO;


	Engine::m_pDevice->CreateSBT(SBTDesc, &m_SBT);
	VERIFY_EXPR(m_pSBT != nullptr);


	m_SBT->BindRayGenShader("Main");

	m_SBT->BindMissShader("PrimaryMiss", PRIMARY_RAY_INDEX);
	m_SBT->BindMissShader("ShadowMiss", SHADOW_RAY_INDEX);

	for (auto m : m_Meshes) {

		auto name = m->GetName();
		char* myString = new char[strlen(name.c_str()) + 1];
		strcpy(myString, name.c_str());

		m_SBT->BindHitGroupForInstance(m_TLAS,myString, PRIMARY_RAY_INDEX, "CubePrimaryHit");


	}


	// clang-format on


	// Hit groups for shadow ray.
	// null means no shaders are bound and hit shader invocation will be skipped.
	m_SBT->BindHitGroupForTLAS(m_TLAS, SHADOW_RAY_INDEX, nullptr);

	// We must specify the intersection shader for procedural geometry.
	//m_pSBT->BindHitGroupForInstance(m_pTLAS, "Sphere Instance", SHADOW_RAY_INDEX, "SphereShadowHit");

	// Update SBT with the shader groups we bound
	Engine::m_pImmediateContext->UpdateSBT(m_SBT);

}

void SolarisRenderer::CreatePipeline() {

	m_MaxRecursionDepth = std::min(m_MaxRecursionDepth, Engine::m_pDevice->GetAdapterInfo().RayTracing.MaxRecursionDepth);

	// Prepare ray tracing pipeline description.
	RayTracingPipelineStateCreateInfoX PSOCreateInfo;

	PSOCreateInfo.PSODesc.Name = "Ray tracing PSO";
	PSOCreateInfo.PSODesc.PipelineType = PIPELINE_TYPE_RAY_TRACING;

	// Define shader macros
	ShaderMacroHelper Macros;
	Macros.AddShaderMacro("NUM_TEXTURES", NumTextures);

	ShaderCreateInfo ShaderCI;
	// We will not be using combined texture samplers as they
	// are only required for compatibility with OpenGL, and ray
	// tracing is not supported in OpenGL backend.
	ShaderCI.Desc.UseCombinedTextureSamplers = false;

	ShaderCI.Macros = Macros;

	// Only new DXC compiler can compile HLSL ray tracing shaders.
	ShaderCI.ShaderCompiler = SHADER_COMPILER_DXC;

	// Shader model 6.3 is required for DXR 1.0, shader model 6.5 is required for DXR 1.1 and enables additional features.
	// Use 6.3 for compatibility with DXR 1.0 and VK_NV_ray_tracing.
	ShaderCI.HLSLVersion = { 6, 3 };
	ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;

	// Create a shader source stream factory to load shaders from files.
	RefCntAutoPtr<IShaderSourceInputStreamFactory> pShaderSourceFactory;
	//m_pEngineFactory->CreateDefaultShaderSourceStreamFactory(nullptr, &pShaderSourceFactory);
	ShaderCI.pShaderSourceStreamFactory = Engine::m_pShaderFactory;

	// Create ray generation shader.
	RefCntAutoPtr<IShader> pRayGen;
	{
		ShaderCI.Desc.ShaderType = SHADER_TYPE_RAY_GEN;
		ShaderCI.Desc.Name = "Ray tracing RG";
		ShaderCI.FilePath = "RayTrace.rgen";
		ShaderCI.EntryPoint = "main";
		Engine::m_pDevice->CreateShader(ShaderCI, &pRayGen);
		VERIFY_EXPR(pRayGen != nullptr);
	}

	// Create miss shaders.
	RefCntAutoPtr<IShader> pPrimaryMiss, pShadowMiss;
	{
		ShaderCI.Desc.ShaderType = SHADER_TYPE_RAY_MISS;
		ShaderCI.Desc.Name = "Primary ray miss shader";
		ShaderCI.FilePath = "PrimaryMiss.rmiss";
		ShaderCI.EntryPoint = "main";
		Engine::m_pDevice->CreateShader(ShaderCI, &pPrimaryMiss);
		VERIFY_EXPR(pPrimaryMiss != nullptr);

		ShaderCI.Desc.Name = "Shadow ray miss shader";
		ShaderCI.FilePath = "ShadowMiss.rmiss";
		ShaderCI.EntryPoint = "main";
		Engine::m_pDevice->CreateShader(ShaderCI, &pShadowMiss);
		VERIFY_EXPR(pShadowMiss != nullptr);
	}

	// Create closest hit shaders.
	RefCntAutoPtr<IShader> pCubePrimaryHit;
	{
		ShaderCI.Desc.ShaderType = SHADER_TYPE_RAY_CLOSEST_HIT;
		ShaderCI.Desc.Name = "Cube primary ray closest hit shader";
		ShaderCI.FilePath = "CubePrimaryHit.rchit";
		ShaderCI.EntryPoint = "main";
		Engine::m_pDevice->CreateShader(ShaderCI, &pCubePrimaryHit);
		VERIFY_EXPR(pCubePrimaryHit != nullptr);

		
	}



	// Setup shader groups

	// Ray generation shader is an entry point for a ray tracing pipeline.
	PSOCreateInfo.AddGeneralShader("Main", pRayGen);
	// Primary ray miss shader.
	PSOCreateInfo.AddGeneralShader("PrimaryMiss", pPrimaryMiss);
	// Shadow ray miss shader.
	PSOCreateInfo.AddGeneralShader("ShadowMiss", pShadowMiss);

	// Primary ray hit group for the textured cube.
	PSOCreateInfo.AddTriangleHitShader("CubePrimaryHit", pCubePrimaryHit);
	// Primary ray hit group for the ground.



	// Specify the maximum ray recursion depth.
	// WARNING: the driver does not track the recursion depth and it is the
	//          application's responsibility to not exceed the specified limit.
	//          The value is used to reserve the necessary stack size and
	//          exceeding it will likely result in driver crash.
	PSOCreateInfo.RayTracingPipeline.MaxRecursionDepth = static_cast<Uint8>(m_MaxRecursionDepth);

	// Per-shader data is not used.
	PSOCreateInfo.RayTracingPipeline.ShaderRecordSize = 0;

	// DirectX 12 only: set attribute and payload size. Values should be as small as possible to minimize the memory usage.
	PSOCreateInfo.MaxAttributeSize = std::max<Uint32>(sizeof(/*BuiltInTriangleIntersectionAttributes*/ float2), sizeof(HLSL::ProceduralGeomIntersectionAttribs));
	PSOCreateInfo.MaxPayloadSize = std::max<Uint32>(sizeof(HLSL::PrimaryRayPayload), sizeof(HLSL::ShadowRayPayload));

	// Define immutable sampler for g_Texture and g_GroundTexture. Immutable samplers should be used whenever possible
	SamplerDesc SamLinearWrapDesc{
		FILTER_TYPE_LINEAR, FILTER_TYPE_LINEAR, FILTER_TYPE_LINEAR,
		TEXTURE_ADDRESS_WRAP, TEXTURE_ADDRESS_WRAP, TEXTURE_ADDRESS_WRAP //
	};

	PipelineResourceLayoutDescX ResourceLayout;
	ResourceLayout.DefaultVariableType = SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE;
	ResourceLayout.AddImmutableSampler(SHADER_TYPE_RAY_CLOSEST_HIT, "g_SamLinearWrap", SamLinearWrapDesc);
	ResourceLayout
		.AddVariable(SHADER_TYPE_RAY_GEN | SHADER_TYPE_RAY_MISS | SHADER_TYPE_RAY_CLOSEST_HIT, "g_ConstantsCB", SHADER_RESOURCE_VARIABLE_TYPE_STATIC)
		.AddVariable(SHADER_TYPE_RAY_GEN, "g_ColorBuffer", SHADER_RESOURCE_VARIABLE_TYPE_DYNAMIC);

	PSOCreateInfo.PSODesc.ResourceLayout = ResourceLayout;

	Engine::m_pDevice->CreateRayTracingPipelineState(PSOCreateInfo, &m_pRayTracingPSO);
	VERIFY_EXPR(m_pRayTracingPSO != nullptr);


	m_pRayTracingPSO->GetStaticVariableByName(SHADER_TYPE_RAY_GEN, "g_ConstantsCB")->Set(m_ConstantsCB);
	m_pRayTracingPSO->GetStaticVariableByName(SHADER_TYPE_RAY_MISS, "g_ConstantsCB")->Set(m_ConstantsCB);
	m_pRayTracingPSO->GetStaticVariableByName(SHADER_TYPE_RAY_CLOSEST_HIT, "g_ConstantsCB")->Set(m_ConstantsCB);

	m_pRayTracingPSO->CreateShaderResourceBinding(&m_pRayTracingSRB, true);
	VERIFY_EXPR(m_pRayTracingSRB != nullptr);

}