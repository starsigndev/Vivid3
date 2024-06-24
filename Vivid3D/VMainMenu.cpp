#include "VMainMenu.h"
#include "NodeTerrain.h"
#include "Editor.h"
#include "SceneGraph.h"
#include "Vivid3D.h"

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
	project->addAction("Load Scene");
	project->addAction("Save Scene");
	project->addSeparator();
	project->addAction("Quit V3");

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
