#include "VOutput.h"
#ifdef Q_OS_WIN
#include <windows.h>
#endif
#include "Engine.h"

VOutput::VOutput(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::lightGray); // Correct enum value
    setAutoFillBackground(true);
    setPalette(pal);
    CreateDX12();
    Engine::m_pDevice = m_pDevice;
    Engine::m_pSwapChain = m_pSwapChain;
    Engine::m_pImmediateContext = m_pImmediateContext;
    Engine::m_pShaderFactory = m_pShaderFactory;
    

    m_Import = new Importer;
    m_Graph1 = new SceneGraph;
    m_Node1 = (NodeEntity*)m_Import->ImportNode("test/mesh1.fbx");


}


void VOutput::CreateDX12() {

    WId wid = winId();
    HWND hwnd = reinterpret_cast<HWND>(wid);

#if PLATFORM_WIN32
    Win32NativeWindow Window{ hwnd };
#endif

    SwapChainDesc SCDesc;
#if ENGINE_DLL
        // Load the dll and import GetEngineFactoryD3D12() function
        auto* GetEngineFactoryD3D12 = LoadGraphicsEngineD3D12();
    #endif
    auto* pFactoryD3D12 = GetEngineFactoryD3D12();


    EngineD3D12CreateInfo EngineCI;
    pFactoryD3D12->CreateDeviceAndContextsD3D12(EngineCI, &m_pDevice, &m_pImmediateContext);
    pFactoryD3D12->CreateSwapChainD3D12(m_pDevice, m_pImmediateContext, SCDesc, FullScreenModeDesc{}, Window, &m_pSwapChain);
    pFactoryD3D12->CreateDefaultShaderSourceStreamFactory("engine\\shader\\", &m_pShaderFactory);

}

void VOutput::resizeEvent(QResizeEvent* event)
{
    // Call the base class implementation (optional, but good practice)
    QWidget::resizeEvent(event);

    // Handle the resize event
    QSize newSize = event->size();
    QSize oldSize = event->oldSize();
  //  if (pSelf->m_pSwapChain != nullptr)
     m_pSwapChain->Resize(static_cast<Uint32>(newSize.width()), static_cast<Uint32>(newSize.height()));
    // For demonstration, print the new size to the debug output
    qDebug() << "Widget resized from" << oldSize << "to" << newSize;
}

VOutput::~VOutput()
{}


void VOutput::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    // Perform rendering using DX12
    
    auto* pContext = GetContext();
    auto* pSwapchain = GetSwapChain();

    ITextureView* pRTV = pSwapchain->GetCurrentBackBufferRTV();
    pContext->SetRenderTargets(1, &pRTV, nullptr, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    const float ClearColor[4] = { 0.8f,0,0,1 };
    pContext->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_VERIFY);

    pContext->Flush();
    pSwapchain->Present();

}
