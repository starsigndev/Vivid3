#include "Vivid3D.h"
#include <QtWidgets>
#include "VSceneGraph.h"
#include "VContentBrowser.h"
#include "VTools.h"

Vivid3D::Vivid3D(QWidget *parent)
    : QMainWindow(parent)
{
   // ui.setupUi(this);
    resize(1424, 750);
    setWindowTitle("Vivid3D - (c)Star Signal Games");
  //  dockScene = new QDockWidget("Scene", this);
  //  SetDockWidget(dockScene);

    mSceneView = new VOutput;

   

    m_SceneGraph = new QDockWidget("Scene Graph", this);
    m_SceneGraph->setWidget(new VSceneGraph);
    SetDockWidget(m_SceneGraph);
    addDockWidget(Qt::LeftDockWidgetArea, m_SceneGraph);
    m_SceneGraph->setMinimumWidth(300);

    setCentralWidget(mSceneView);

    addToolBar(Qt::TopToolBarArea, new VTools(this));

    m_ContentBrowser = new QDockWidget("Content Browser", this);
    m_ContentBrowser->setWidget(new VContentBrowser);
    SetDockWidget(m_ContentBrowser);
    addDockWidget(Qt::BottomDockWidgetArea, m_ContentBrowser);
    m_ContentBrowser->setMinimumWidth(300);
    m_ContentBrowser->setMinimumHeight(250);



}

void Vivid3D::SetDockWidget(QDockWidget* dock) {

    dock->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);

}
Vivid3D::~Vivid3D()
{}
