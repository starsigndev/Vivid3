#include "pch.h"
#include "MaterialEmissive.h"
#include "Engine.h"
#include <vector>
#include "NodeLight.h"
#include "RenderTargetCube.h"
#include "Texture2D.h"

#include <Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <Graphics/GraphicsEngine/interface/DeviceContext.h>
#include <Graphics/GraphicsEngine/interface/Buffer.h>
#include <Graphics/GraphicsEngine/interface/SwapChain.h>
#include <Common/interface/RefCntAutoPtr.hpp>
#include <MapHelper.hpp> // Add this line
using namespace Diligent;
struct Constants {

    float4x4 g_MVP;
    float4x4 g_Proj;
    float4x4 g_Model;
    float4x4 g_View;
    float4x4 g_ModelInv;
    float4 viewPos;
    float4 lightPos;
    float4 lightProp;
    float4 lightDiff;
    float4 lightSpec;
    float4 renderProps;
    int4 lightMode;
    float4 lightDir;
    float4 viewDir;
    float4 lightCone;
    float4 matDiff;
    float4 matSpec;

};


MaterialEmissive::MaterialEmissive() {

    Create();
    m_Diffuse = new Texture2D("engine/white.png");
    m_Normal = new Texture2D("engine/normal.png");
    m_Specular = new Texture2D("engine/white.png");
}

void MaterialEmissive::Create() {

    //printf("Creating MeshLight.\n");
    SetVertexShader("mesh_emissive.vsh");
    SetPixelShader("mesh_emissive.psh");

    BasicUniform = CreateUniform(sizeof(Constants), "Constants Uniform Buffer - MVP");
    BasicUniform2 = CreateUniform(sizeof(Constants), "Constants Uniform Buffer - MVP");
    GraphicsPipelineDesc gp;




    RasterizerStateDesc r_desc;



    r_desc.CullMode = CULL_MODE_BACK;



    DepthStencilStateDesc ds_desc;
    ds_desc.DepthEnable = true;
    ds_desc.DepthFunc = COMPARISON_FUNC_LESS_EQUAL;
    ds_desc.DepthWriteEnable = true;


    BlendStateDesc b_desc;

    b_desc.RenderTargets[0].BlendEnable = false;
    b_desc.RenderTargets[0].SrcBlend = BLEND_FACTOR::BLEND_FACTOR_ONE;
    b_desc.RenderTargets[0].DestBlend = BLEND_FACTOR::BLEND_FACTOR_ZERO;



    InputLayoutDesc in_desc;

    LayoutElement LayoutElems[] =
    {
        // Attribute 0 - vertex position
        LayoutElement{0, 0, 3, VT_FLOAT32, False},
        // Attribute 1 - vertex color
        LayoutElement{1, 0, 4, VT_FLOAT32, False},
                LayoutElement{2, 0, 3, VT_FLOAT32, False},
                        LayoutElement{3, 0, 3, VT_FLOAT32, False},
                                LayoutElement{4, 0, 3, VT_FLOAT32, False},
                                        LayoutElement{5, 0, 3, VT_FLOAT32, False},
                                        LayoutElement(6,0,4,VT_FLOAT32,False),
                                        LayoutElement(7,0,4,VT_FLOAT32,False)
    };

    in_desc.LayoutElements = LayoutElems;
    in_desc.NumElements = 8;



    gp.PrimitiveTopology = PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    gp.RasterizerDesc = r_desc;
    //  gp.RasterizerDesc.CullMode = CULL_MODE_NONE;
    gp.DepthStencilDesc = ds_desc;
    gp.SmplDesc.Count = 4;

    //gp.SmplDesc.Quality = 1.0f;

    //gp.NumRenderTargets = 0;

    gp.BlendDesc = b_desc;
    gp.RTVFormats[0] = Engine::m_pSwapChain->GetDesc().ColorBufferFormat;
    gp.DSVFormat = Engine::m_pSwapChain->GetDesc().DepthBufferFormat;
    gp.InputLayout = in_desc;
    //gp.NumViewports = 1;


    gp.NumRenderTargets = 1;


    std::vector<ShaderResourceVariableDesc> vars;
    std::vector<ImmutableSamplerDesc> samplers;

    ShaderResourceVariableDesc v_tex;

    v_tex.ShaderStages = SHADER_TYPE_PIXEL;
    v_tex.Name = "g_Texture";
    v_tex.Type = SHADER_RESOURCE_VARIABLE_TYPE_DYNAMIC;
    vars.push_back(v_tex);

    ShaderResourceVariableDesc v_norm;

    v_norm.ShaderStages = SHADER_TYPE_PIXEL;
    v_norm.Name = "g_TextureNorm";
    v_norm.Type = SHADER_RESOURCE_VARIABLE_TYPE_DYNAMIC;
    vars.push_back(v_norm);

    ShaderResourceVariableDesc v_spec;

    v_spec.ShaderStages = SHADER_TYPE_PIXEL;
    v_spec.Name = "g_TextureSpec";
    v_spec.Type = SHADER_RESOURCE_VARIABLE_TYPE_DYNAMIC;
    vars.push_back(v_spec);

    v_tex.ShaderStages = SHADER_TYPE_PIXEL;
    v_tex.Name = "v_Shadow";
    v_tex.Type = SHADER_RESOURCE_VARIABLE_TYPE_DYNAMIC;
    vars.push_back(v_tex);

    ImmutableSamplerDesc v_sampler;

    SamplerDesc v_rsampler;
    v_rsampler.MinFilter = FILTER_TYPE::FILTER_TYPE_LINEAR;
    v_rsampler.MagFilter = FILTER_TYPE::FILTER_TYPE_LINEAR;
    v_rsampler.MipFilter = FILTER_TYPE::FILTER_TYPE_LINEAR;
    v_rsampler.AddressU = TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_WRAP;
    v_rsampler.AddressV = TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_WRAP;
    v_rsampler.AddressW = TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_WRAP;
    // v_rsampler.MaxAnisotropy = 1.0f;



    v_sampler.Desc = v_rsampler;
    v_sampler.SamplerOrTextureName = "g_Texture";
    v_sampler.ShaderStages = SHADER_TYPE_PIXEL;


    samplers.push_back(v_sampler);

    v_sampler.Desc = v_rsampler;
    v_sampler.SamplerOrTextureName = "g_TextureNorm";
    v_sampler.ShaderStages = SHADER_TYPE_PIXEL;

    samplers.push_back(v_sampler);

    v_sampler.Desc = v_rsampler;
    v_sampler.SamplerOrTextureName = "g_TextureSpec";
    v_sampler.ShaderStages = SHADER_TYPE_PIXEL;

    samplers.push_back(v_sampler);

    v_sampler.Desc = v_rsampler;
    v_sampler.SamplerOrTextureName = "v_Shadow";
    v_sampler.ShaderStages = SHADER_TYPE_PIXEL;

    samplers.push_back(v_sampler);

    PipelineResourceLayoutDesc rl_desc;

    rl_desc.DefaultVariableType = SHADER_RESOURCE_VARIABLE_TYPE_STATIC;
    rl_desc.Variables = vars.data();
    rl_desc.ImmutableSamplers = samplers.data();
    rl_desc.NumVariables = 4;

    rl_desc.NumImmutableSamplers = 4;


    PipelineStateDesc pso_desc;

    pso_desc.Name = "Material Basic";
    pso_desc.ResourceLayout = rl_desc;

    //    pso_desc.PipelineType = PIPELINE_TYPE_GRAPHICS;


    GraphicsPipelineStateCreateInfo gp_desc;
    gp_desc.pVS = m_VS;
    gp_desc.pPS = m_PS;
    gp_desc.GraphicsPipeline = gp;
    gp_desc.PSODesc = pso_desc;
    // gp_desc.ResourceSignaturesCount = 0;



     //CreateUniform()

    RefCntAutoPtr<IPipelineState> ps;

    Engine::m_pDevice->CreateGraphicsPipelineState(gp_desc, &ps);

    m_Pipeline = ps;
    m_Pipeline->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(BasicUniform);
    m_Pipeline->CreateShaderResourceBinding(&m_SRB, true);






}

void MaterialEmissive::Bind(bool sp) {

   
        m_SRB->GetVariableByName(SHADER_TYPE_PIXEL, "g_Texture")->Set(m_Emissive->GetView(), SET_SHADER_RESOURCE_FLAG_NONE);
 
    if (sp) {

        MapHelper<Constants> map_data(Engine::m_pImmediateContext, BasicUniform2, MAP_WRITE, MAP_FLAG_DISCARD);
        float FOVRadians = 45.0f * (3.14159265358979323846f / 180.0f);


        auto light = Engine::m_Light;

        float4x4 mvp = Engine::m_Camera->GetProjection(); //float4x4::Projection(FOVRadians, 1024.0f / 760.0f,0.01,1001,false);


        float4x4 view = Engine::m_Camera->GetWorldMatrix();  //float4x4::Translation(float3(0,1.0f,-5)).Inverse();

        float4x4 model = Engine::m_Node->GetWorldMatrix();

        float4x4 id = float4x4::Identity().Inverse();

        //mvp = mvp*id;

        //mvp.Transpose();


        mvp = model * view * mvp;


        map_data[0].g_MVP = mvp.Transpose();
        map_data[0].g_Model = model.Transpose();
        map_data[0].g_ModelInv = model.Inverse().Transpose();
        map_data[0].g_Proj = Engine::m_Camera->GetProjection().Transpose();
        map_data[0].g_View = view.Transpose();
        map_data[0].lightDiff = light->GetDiffuse();
        map_data[0].lightPos = float4(light->GetPosition(), 1.0f);
        map_data[0].lightSpec = float4(light->GetSpecular(), 1.0f);
        map_data[0].matDiff = float4(1, 1, 1, 1);
        map_data[0].matSpec = float4(1, 1, 1, 1);
        map_data[0].viewPos = float4(Engine::m_Camera->GetPosition(), 1.0);
        map_data[0].lightProp = float4(light->GetRange(), 0, 0, 0);
    }
    else {
        MapHelper<Constants> map_data(Engine::m_pImmediateContext, BasicUniform, MAP_WRITE, MAP_FLAG_DISCARD);
        float FOVRadians = 45.0f * (3.14159265358979323846f / 180.0f);


        auto light = Engine::m_Light;

        float4x4 mvp = Engine::m_Camera->GetProjection(); //float4x4::Projection(FOVRadians, 1024.0f / 760.0f,0.01,1001,false);


        float4x4 view = Engine::m_Camera->GetWorldMatrix();  //float4x4::Translation(float3(0,1.0f,-5)).Inverse();

        float4x4 model = Engine::m_Node->GetWorldMatrix();

        float4x4 id = float4x4::Identity().Inverse();

        //mvp = mvp*id;

        //mvp.Transpose();


        mvp = model * view * mvp;


        map_data[0].g_MVP = mvp.Transpose();
        map_data[0].g_Model = model.Transpose();
        map_data[0].g_ModelInv = model.Inverse().Transpose();
        map_data[0].g_Proj = Engine::m_Camera->GetProjection().Transpose();
        map_data[0].g_View = view.Transpose();
        map_data[0].lightDiff = light->GetDiffuse();
        map_data[0].lightPos = float4(light->GetPosition(), 1.0f);
        map_data[0].lightSpec = float4(light->GetSpecular(), 1.0f);
        map_data[0].matDiff = float4(1, 1, 1, 1);
        map_data[0].matSpec = float4(1, 1, 1, 1);
        map_data[0].viewPos = float4(Engine::m_Camera->GetPosition(), 1.0);
        map_data[0].lightProp = float4(light->GetRange(), 0, 0, 0);

    }


    //map_data.Unmap();

    if (sp) {
        Engine::m_pImmediateContext->SetPipelineState(m_SecondPassPipeline);
    }
    else {
        Engine::m_pImmediateContext->SetPipelineState(m_Pipeline);
    }
}