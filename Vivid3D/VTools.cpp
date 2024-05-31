#include "VTools.h"
#include "Editor.h"

VTools::VTools(QWidget *parent)
	: QToolBar(parent)
{
	ui.setupUi(this);
	QAction* translate = addAction(QIcon("edit/icons/Translate.png"), "ActTranslate");
	QAction* rotate = addAction(QIcon("edit/icons/Rotate.png"), "ActRotate");
	QAction* scale = addAction(QIcon("edit/icons/Scale.png"), "ActScale");
	addSeparator();


	connect(translate, &QAction::triggered, [this]() {

		Editor::m_GizmoMode = GM_Translate;

		});

	connect(rotate, &QAction::triggered, [this]() {

		Editor::m_GizmoMode = GM_Rotate;

		});


}

VTools::~VTools()
{}
