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
    m_Graph1->AddNode((Node*)m_Node1);
    m_Light1 = new NodeLight;
    m_Light1->SetPosition(float3(0, 8,0));
    m_Graph1->AddLight(m_Light1);
    
    auto cam = m_Graph1->GetCamera();
    cam->SetPosition(float3(0, 8,0));
    setMouseTracking(true);

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

    //SCDesc.ColorBufferFormat = TEX_FORMAT_RGBA16_FLOAT;


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
    Engine::m_FrameWidth = newSize.width();
    Engine::m_FrameHeight = newSize.height();
}


void VOutput::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Handle left mouse button press
       
    }
    else if (event->button() == Qt::RightButton)
    {
        m_CamRotate = true;
        // Handle right mouse button press
    }
    // Add other buttons if needed

    // Call base class implementation if necessary
    QWidget::mousePressEvent(event);
}

void VOutput::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
      
        // Handle left mouse button release
    }
    else if (event->button() == Qt::RightButton)
    {
        m_CamRotate = false;
        // Handle right mouse button release
    }
    // Add other buttons if needed

    // Call base class implementation if necessary
    QWidget::mouseReleaseEvent(event);
}
float ay = 0;

void VOutput::mouseMoveEvent(QMouseEvent* event)
{

  



    QPoint delta = event->pos() - m_MouseLast;
    m_MouseLast = event->pos();
    // Handle mouse move event
    // Use event->pos() or event->globalPos() to get the cursor position
    if (m_CamRotate) {
        m_ViewYaw += delta.x() * 0.2f;
        m_ViewPitch += delta.y() * 0.2f;

      //  update();
    }
    
    // Call base class implementation if necessary
    QWidget::mouseMoveEvent(event);
}


VOutput::~VOutput()
{}


void VOutput::paintEvent(QPaintEvent* event)
{
    //Q_UNUSED(event);

    // Perform rendering using DX12
    
    auto* pContext = GetContext();
    auto* pSwapchain = GetSwapChain();

    ITextureView* pRTV = pSwapchain->GetCurrentBackBufferRTV();

    pContext->SetRenderTargets(1, &pRTV,pSwapchain->GetDepthBufferDSV(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    const float ClearColor[4] = { 0.3f,0.1f,0.1f,1.0 };
    pContext->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_VERIFY);
    pContext->ClearDepthStencil(pSwapchain->GetDepthBufferDSV(), CLEAR_DEPTH_FLAG, 1.0f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    
    auto cam = m_Graph1->GetCamera();
    ay = ay + 0.1f;

  //  m_Node1->SetRotation(0, ay, 0);
    
    cam->SetRotation(m_ViewPitch, m_ViewYaw, 0);

    m_Graph1->Render();

    pContext->Flush();
 
    pContext->FinishFrame();
 //   pContext->Flush();
    pSwapchain->Present(1);
    update();
  //  QWidget::paintEvent(event);
}
