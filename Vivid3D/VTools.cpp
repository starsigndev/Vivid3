#include "VTools.h"
#include "Editor.h"
#include "qcombobox.h"

VTools::VTools(QWidget* parent)
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



	QComboBox* space = new QComboBox(this);

	space->addItem("Local");
	space->addItem("Global");
	space->setMinimumWidth(80);

	addWidget(space);


	connect(space, QOverload<int>::of(&QComboBox::currentIndexChanged),
		[this](int index) {
			//label->setText(QString("Selected Option: %1").arg(index + 1));
			if (index == 0) {
				Editor::m_SpaceMode = SM_Local;
			}
			else {
				Editor::m_SpaceMode = SM_Global;
			}
		});

		//&MainWindow::onComboBoxIndexChanged);
	QAction* run = addAction(QIcon("edit/icons/runicon.png"), "ActRun");
	QAction* stop = addAction(QIcon("edit/icons/stopicon.png"), "ActStop");


	connect(run, &QAction::triggered, [this]() {

		Editor::BeginPlay();

		});

	connect(stop, &QAction::triggered, [this]() {

		Editor::Stop();

		});
}

VTools::~VTools()
{}
