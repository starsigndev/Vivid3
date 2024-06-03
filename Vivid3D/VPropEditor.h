#pragma once

#include <QWidget>
#include "ui_VPropEditor.h"
#include <QVBoxLayout>
#include <qlabel.h>
#include "VImagePreview.h"
#include "VColorPreview.h"
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
	MaterialBase* m_Material;

	//Material Editor
	VImagePreview* m_DiffuseImg;
	VImagePreview* m_SpecImg;
	VImagePreview* m_NormImg;

};
