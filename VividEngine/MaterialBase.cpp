#include "pch.h"
#include "MaterialBase.h"
#include "Engine.h"
#include <vector>

MaterialBase::MaterialBase() {

    Create();

}

void MaterialBase::Create() {

    SetVertexShader("basic.vsh");
    SetPixelShader("basic.psh");

    BasicUniform = CreateUniform(sizeof(float4x4),"Basic Uniform Buffer - MVP");

    GraphicsPipelineDesc gp;

    gp.SubpassIndex = 0;


    RasterizerStateDesc r_desc;

    
    r_desc.CullMode = CULL_MODE_NONE;


    DepthStencilStateDesc ds_desc;
    ds_desc.DepthEnable = true;
    ds_desc.DepthFunc = COMPARISON_FUNC_LESS_EQUAL;
    ds_desc.DepthWriteEnable = true;
   

    BlendStateDesc b_desc;

    b_desc.RenderTargets[0].BlendEnable = false;
    b_desc.RenderTargets[0].SrcBlend = BLEND_FACTOR::BLEND_FACTOR_SRC_ALPHA;
    b_desc.RenderTargets[0].DestBlend = BLEND_FACTOR::BLEND_FACTOR_INV_SRC_ALPHA;
    


    LayoutElement pos;
    LayoutElement color;
    LayoutElement tex;
    LayoutElement norm;
    LayoutElement binorm;
    LayoutElement tangent;

    std::vector<LayoutElement> elements;

    pos.InputIndex = 0;
    pos.NumComponents = 3;
    pos.ValueType = VALUE_TYPE::VT_FLOAT32;
    pos.IsNormalized = false;

    color.InputIndex = 1;
    color.NumComponents = 4;
    color.ValueType = VALUE_TYPE::VT_FLOAT32;
    color.IsNormalized = false;

    tex.InputIndex = 2;
    tex.NumComponents = 3;
    tex.ValueType = VALUE_TYPE::VT_FLOAT32;
    tex.IsNormalized = false;

    norm.InputIndex = 3;
    norm.NumComponents = 3;
    norm.ValueType = VALUE_TYPE::VT_FLOAT32;
    norm.IsNormalized = false;

    binorm.InputIndex = 4;
    binorm.NumComponents = 3;
    binorm.ValueType = VALUE_TYPE::VT_FLOAT32;
    binorm.IsNormalized = false;

    tangent.InputIndex = 5;
    tangent.NumComponents = 3;
    tangent.ValueType = VALUE_TYPE::VT_FLOAT32;
    tangent.IsNormalized = false;
    

    elements.push_back(pos);
    elements.push_back(color);
    elements.push_back(tex);
    elements.push_back(norm);
    elements.push_back(binorm);
    elements.push_back(tangent);

    InputLayoutDesc in_desc;
    in_desc.LayoutElements = elements.data();
    in_desc.NumElements = 6;


    gp.PrimitiveTopology = PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    gp.RasterizerDesc = r_desc;
    gp.DepthStencilDesc = ds_desc;
    gp.SmplDesc.Count = 1;
    gp.NumRenderTargets = 1;
    gp.BlendDesc = b_desc;
    gp.RTVFormats[0] = Engine::m_pSwapChain->GetDesc().ColorBufferFormat;
    gp.DSVFormat = Engine::m_pSwapChain->GetDesc().DepthBufferFormat;
    gp.InputLayout = in_desc;


    std::vector<ShaderResourceVariableDesc> vars;
    std::vector<ImmutableSamplerDesc> samplers;

    ShaderResourceVariableDesc v_tex;
    
    v_tex.ShaderStages = SHADER_TYPE_PIXEL;
    v_tex.Name = "v_Texture";
    v_tex.Type = SHADER_RESOURCE_VARIABLE_TYPE_DYNAMIC;
    vars.push_back(v_tex);

    ImmutableSamplerDesc v_sampler;

    SamplerDesc v_rsampler;
    v_rsampler.MinFilter = FILTER_TYPE::FILTER_TYPE_LINEAR;
    v_rsampler.MagFilter = FILTER_TYPE::FILTER_TYPE_LINEAR;
    v_rsampler.MipFilter = FILTER_TYPE::FILTER_TYPE_LINEAR;
    v_rsampler.AddressU = TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_WRAP;
    v_rsampler.AddressV = TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_WRAP;
    v_rsampler.AddressW = TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_CLAMP;
    v_rsampler.MaxAnisotropy = 8.0f;



    v_sampler.Desc = v_rsampler;
    v_sampler.SamplerOrTextureName = "v_Texture";
    v_sampler.ShaderStages = SHADER_TYPE_PIXEL;
       

    samplers.push_back(v_sampler);

    PipelineResourceLayoutDesc rl_desc;

    rl_desc.DefaultVariableType = SHADER_RESOURCE_VARIABLE_TYPE_STATIC;
    rl_desc.Variables = vars.data();
    rl_desc.ImmutableSamplers = samplers.data();
    rl_desc.NumVariables = 1;
    rl_desc.NumImmutableSamplers = 1;
    
    PipelineStateDesc pso_desc;

    pso_desc.Name = "Material Basic";
    pso_desc.ResourceLayout = rl_desc;




    GraphicsPipelineStateCreateInfo gp_desc;
    gp_desc.pVS = m_VS;
    gp_desc.pPS = m_PS;
    gp_desc.GraphicsPipeline = gp;
    gp_desc.PSODesc = pso_desc;
    

    //CreateUniform()

    RefCntAutoPtr<IPipelineState> ps;

    Engine::m_pDevice->CreateGraphicsPipelineState(gp_desc, &ps);

    m_Pipeline = ps;
    ps->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(BasicUniform);
    ps->CreateShaderResourceBinding(&m_SRB,true);

    

    //Engine::m_pDevice->CreateBuffer();
}

RefCntAutoPtr<IBuffer> MaterialBase::CreateUniform(int size, std::string path) {

    BufferDesc desc;
    desc.Name = path.c_str();
    desc.Size = size;
    desc.Usage = USAGE_DYNAMIC;
    desc.BindFlags = BIND_UNIFORM_BUFFER;
    desc.CPUAccessFlags = CPU_ACCESS_WRITE;

    RefCntAutoPtr<IBuffer> buffer;

    Engine::m_pDevice->CreateBuffer(desc, nullptr, &buffer);

    return buffer;

}

void MaterialBase::SetVertexShader(std::string path) {

    const char* filePath = path.c_str();

    // Allocate memory for the Diligent::Char* and copy the string
    size_t length = path.length();
    Char* diligentPath = new Char[length + 1]; // +1 for null terminator
    std::strcpy(diligentPath, filePath);

    ShaderDesc desc;

    desc.Name = diligentPath;
    desc.ShaderType = SHADER_TYPE_VERTEX;
    desc.UseCombinedTextureSamplers = true;
          

	ShaderCreateInfo info;
    info.FilePath = diligentPath;
    info.pShaderSourceStreamFactory = Engine::m_pShaderFactory;
    info.Desc = desc;
    info.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;

	Engine::m_pDevice->CreateShader(info, &m_VS);


}

void MaterialBase::SetPixelShader(std::string path) {

    const char* filePath = path.c_str();

    // Allocate memory for the Diligent::Char* and copy the string
    size_t length = path.length();
    Char* diligentPath = new Char[length + 1]; // +1 for null terminator
    std::strcpy(diligentPath, filePath);

    ShaderDesc desc;

    desc.Name = diligentPath;
    desc.ShaderType = SHADER_TYPE_PIXEL;
    desc.UseCombinedTextureSamplers = true;

    ShaderCreateInfo info;
    info.FilePath = diligentPath;
    info.pShaderSourceStreamFactory = Engine::m_pShaderFactory;
    info.Desc = desc;
    info.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;

    Engine::m_pDevice->CreateShader(info, &m_PS);

}