#pragma once

#include <QWidget>
#include "ui_VPropEditor.h"
#include <QVBoxLayout>
#include <qlabel.h>
#include "VImagePreview.h"
#include "VColorPreview.h"
#include "qspinbox.h"
class MaterialBase;
class Node;


class VPropEditor : public QWidget
{
	Q_OBJECT

public:
	VPropEditor(QWidget *parent = nullptr);
	~VPropEditor();
	void SetMaterial(MaterialBase* material);
	void SetNode(Node* node);
	void UpdateNode();

private:
	Ui::VPropEditorClass ui;
	QVBoxLayout* m_LO;
	MaterialBase* m_Material;
	Node* m_Node;

	//Material Editor
	VImagePreview* m_DiffuseImg;
	VImagePreview* m_SpecImg;
	VImagePreview* m_NormImg;
	VColorPreview* m_DiffCol;
	VColorPreview* m_SpecCol;
	//Node
	QDoubleSpinBox* m_NodePosX;
	QDoubleSpinBox* m_NodePosY;
	QDoubleSpinBox* m_NodePosZ;
	QDoubleSpinBox* m_NodeRotX;
	QDoubleSpinBox* m_NodeRotY;
	QDoubleSpinBox* m_NodeRotZ;
	bool m_BlockRot = false;
	bool m_BlockTimer = false;

};
