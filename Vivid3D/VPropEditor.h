#pragma once

#include <QWidget>
#include "ui_VPropEditor.h"
#include <QVBoxLayout>

class MaterialBase;

class VPropEditor : public QWidget
{
	Q_OBJECT

public:
	VPropEditor(QWidget *parent = nullptr);
	~VPropEditor();
	void SetMaterial(MaterialBase* material);

private:
	Ui::VPropEditorClass ui;
	QVBoxLayout* m_LO;
};
