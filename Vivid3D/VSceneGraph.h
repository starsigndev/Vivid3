#pragma once

#include <QWidget>
#include "ui_VSceneGraph.h"
#include <string>
#include <vector>

class VTreeView;


class VSceneGraph : public QWidget
{
	Q_OBJECT

public:
	VSceneGraph(QWidget *parent = nullptr);
	~VSceneGraph();
	void UpdateGraph();

private:
	Ui::VSceneGraphClass ui;
	VTreeView* m_Tree;

};
