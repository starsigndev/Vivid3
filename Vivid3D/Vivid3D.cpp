#include "Vivid3D.h"
#include <QtWidgets>

Vivid3D::Vivid3D(QWidget *parent)
    : QMainWindow(parent)
{
   // ui.setupUi(this);
    resize(1424, 750);
    setWindowTitle("Vivid3D - (c)Star Signal Games");
  //  dockScene = new QDockWidget("Scene", this);
  //  SetDockWidget(dockScene);

    mSceneView = new VOutput;

    setCentralWidget(mSceneView);
}

void Vivid3D::SetDockWidget(QDockWidget* dock) {

    dock->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);

}
Vivid3D::~Vivid3D()
{}
