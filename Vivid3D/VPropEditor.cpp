#include "VPropEditor.h"
#include "MaterialBase.h"
#include "qpushbutton.h"

VPropEditor::VPropEditor(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_LO = new QVBoxLayout(this);
	m_LO->setAlignment(Qt::AlignTop);
	m_LO->setSpacing(2);
	setLayout(m_LO);
}

void VPropEditor::SetMaterial(MaterialBase* material) {

	for (int i = 0; i < 5; i++) {

		auto but = new QPushButton("Test");
		m_LO->addWidget(but);
		but->setMinimumHeight(35);

	}

}

VPropEditor::~VPropEditor()
{}
