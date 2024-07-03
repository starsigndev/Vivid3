#include "VMainMenu.h"
#include "NodeTerrain.h"
#include "Editor.h"
#include "SceneGraph.h"
#include "Vivid3D.h"
#include <qfiledialog.h>
#include "Engine.h"
#include "VSceneGraph.h"
#include "RendererBase.h"

VMainMenu::VMainMenu(QWidget *parent)
	: QMenuBar(parent)
{
	ui.setupUi(this);

	QMenu* project = addMenu("Scene");
	QMenu* edit = addMenu("Edit");
	QMenu* create = addMenu("Create");
	QMenu* editors = addMenu("Editors");

	//project
	project->addAction("New Scene");
	project->addSeparator();
	auto load_Scene = project->addAction("Load Scene");

	auto save_Scene = project->addAction("Save Scene");

	project->addSeparator();
	project->addAction("Quit V3");

	connect(save_Scene, &QAction::triggered, [this]() {

		QString filePath = QFileDialog::getSaveFileName(this,
			tr("Save Scene"),
			QString(),
			tr("Scene Files (*.scene);"),
			nullptr);

		if (!filePath.isEmpty())
		{
			// Ensure the file has the .scene extension
			if (!filePath.endsWith(".scene", Qt::CaseInsensitive))
			{
				filePath += ".scene";
				
			}
			Editor::m_Graph->SaveScene(filePath.toStdString());
		}
		//auto terrain = new NodeTerrain(128, 128, 3, 4);
		//Editor::m_Graph->AddNode(terrain);

		});

	//
	connect(load_Scene, &QAction::triggered, [this]() {

		QString filePath = QFileDialog::getOpenFileName(this,
			tr("Save Scene"),
			QString(),
			tr("Scene Files (*.scene);"),
			nullptr
			);

		if (!filePath.isEmpty())
		{
			// Ensure the file has the .scene extension
			if (!filePath.endsWith(".scene", Qt::CaseInsensitive))
			{
				filePath += ".scene";


			}
			auto cam = Engine::m_Camera;
			auto lines = Editor::m_Graph->GetLines();
			Editor::m_Graph = new SceneGraph;
			Editor::m_Graph->LoadScene(filePath.toStdString());
			Engine::m_Camera = cam;
			Editor::m_Graph->SetCamera(cam);
			Editor::m_Graph->SetLines(lines);
			Editor::m_SceneGraph->UpdateGraph();
			Editor::m_Graph->Updated();
			Engine::m_ActiveRenderer->SetSceneGraph(Editor::m_Graph);

			
			//Editor::m_Graph->SaveScene(filePath.toStdString());
		}
		//auto terrain = new NodeTerrain(128, 128, 3, 4);
		//Editor::m_Graph->AddNode(terrain);

		});



	//Create
	auto create_terrain = create->addAction("Create Terrain");

	connect(create_terrain, &QAction::triggered, [this]() {

		auto terrain = new NodeTerrain(128, 128, 3, 4);
		Editor::m_Graph->AddNode(terrain);

		});

	//Editors

	auto edit_cine = editors->addAction("Cinema");

	connect(edit_cine, &QAction::triggered, [this]() {

		Editor::m_Main->CreateCinema();
		//auto terrain = new NodeTerrain(128, 128, 3, 4);
		//Editor::m_Graph->AddNode(terrain);

		});


}

VMainMenu::~VMainMenu()
{}
