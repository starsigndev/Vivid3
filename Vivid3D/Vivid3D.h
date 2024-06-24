#pragma once

#include <QtWidgets/QMainWindow>
#include "Widgets/VOutput.h"
#include "ui_Vivid3D.h"

class Vivid3D : public QMainWindow
{
    Q_OBJECT

public:
    Vivid3D(QWidget *parent = nullptr);
    ~Vivid3D();
    void SetDockWidget(QDockWidget* dock);
    void CreateCinema();

private:
    Ui::Vivid3DClass ui;
    //Docks
    QDockWidget* dockScene;
    QDockWidget* m_SceneGraph;
    QDockWidget* m_ContentBrowser;
    QDockWidget* m_PropEditor;
    QDockWidget* m_CinemaEditor;
    VOutput* mSceneView;

};
