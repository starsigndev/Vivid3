#include "VSceneGraph.h"
#include "VTreeView.h"
#include <QVBoxLayout>
#include <qscrollarea.h>
#include "Node.h"
#include "Editor.h"
#include "SceneGraph.h"
VSceneGraph::VSceneGraph(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	VTreeView* tree = new VTreeView(this);

	QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setWidget(tree);
	scrollArea->setWidgetResizable(true);

	auto lo = new QVBoxLayout(this);



	lo->addWidget(scrollArea);

	setLayout(lo);
	m_Tree = tree;

	UpdateGraph();


}

void AddNode(TreeItem* item, Node* node) {

	item->m_Text = node->GetName();
	
	for (auto sub : node->GetNodes()) {

		TreeItem* new_item = new TreeItem;
		AddNode(new_item, sub);
		item->m_Items.push_back(new_item);

	}

}

void VSceneGraph::UpdateGraph() {

	auto item = new TreeItem;
	item->m_Text = "Scene Root";

	AddNode(item, Editor::m_Graph->GetRoot());

	m_Tree->SetRoot(item);

}

VSceneGraph::~VSceneGraph()
{}
