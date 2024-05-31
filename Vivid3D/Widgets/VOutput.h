#pragma once

#include <QWidget>
#include "ui_VOutput.h"

#ifndef ENGINE_DLL
#    define ENGINE_DLL 1
#endif

#ifndef D3D11_SUPPORTED
#    define D3D11_SUPPORTED 0
#endif

#ifndef D3D12_SUPPORTED
#    define D3D12_SUPPORTED 0
#endif

#ifndef GL_SUPPORTED
#    define GL_SUPPORTED 0
#endif

#ifndef VULKAN_SUPPORTED
#    define VULKAN_SUPPORTED 0
#endif

#ifndef METAL_SUPPORTED
#    define METAL_SUPPORTED 0
#endif

#if PLATFORM_WIN32
#    define GLFW_EXPOSE_NATIVE_WIN32 1
#endif

#if PLATFORM_LINUX
#    define GLFW_EXPOSE_NATIVE_X11 1
#endif

#if PLATFORM_MACOS
#    define GLFW_EXPOSE_NATIVE_COCOA 1
#endif

#if D3D11_SUPPORTED
#    include "Graphics/GraphicsEngineD3D11/interface/EngineFactoryD3D11.h"
#endif
#if D3D12_SUPPORTED
#    include "Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h"
#endif
#if GL_SUPPORTED
#    include "Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h"
#endif
#if VULKAN_SUPPORTED
#    include "Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h"
#endif
#if METAL_SUPPORTED
#    include "Graphics/GraphicsEngineMetal/interface/EngineFactoryMtl.h"
#endif

#ifdef GetObject
#    undef GetObject
#endif
#ifdef CreateWindow
#    undef CreateWindow
#endif


#include "RefCntAutoPtr.hpp"
#include "RenderDevice.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "BasicMath.hpp"
#include <QResizeEvent>
#include <QDebug>
#include "SceneGraph.h"
#include "Node.h"
#include "NodeEntity.h"
#include "Importer.h"


using namespace Diligent;


class VOutput : public QWidget
{
	Q_OBJECT

public:
	VOutput(QWidget *parent = nullptr);
	~VOutput();
	void CreateDX12();

	IEngineFactory* GetEngineFactory() { return m_pDevice->GetEngineFactory(); }
	IRenderDevice* GetDevice() { return m_pDevice; }
	IDeviceContext* GetContext() { return m_pImmediateContext; }
	ISwapChain* GetSwapChain() { return m_pSwapChain; }

protected:
	void resizeEvent(QResizeEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

private slots:
	void onMove();

private:
	Ui::VOutputClass ui;
	//Win32NativeWindow Window;
	RefCntAutoPtr<IRenderDevice>  m_pDevice;
	RefCntAutoPtr<IDeviceContext> m_pImmediateContext;
	RefCntAutoPtr<ISwapChain>     m_pSwapChain;
	RefCntAutoPtr<IShaderSourceInputStreamFactory> m_pShaderFactory;
	Importer* m_Import;
	SceneGraph* m_Graph1;
	NodeEntity* m_Node1;
	NodeCamera* m_EditCamera;
	NodeLight* m_Light1;
	float m_ViewPitch = 0;
	float m_ViewYaw = 0;
	bool m_CamRotate = false;
	QPoint m_MouseLast;
	bool m_MoveW, m_MoveA, m_MoveS, m_MoveD;
	bool m_MoveFast = false;
	QTimer* m_MoveTimer;
	QPoint m_MousePosition;
	NodeEntity* m_Gizmo = nullptr;
	NodeEntity* m_GizTranslate;
	NodeEntity* m_GizRotate;
	bool m_LockX, m_LockY, m_LockZ;

};
