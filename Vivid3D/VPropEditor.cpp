#include "VPropEditor.h"
#include "MaterialBase.h"
#include "qpushbutton.h"
#include "qdrag.h"
#include <QDragEnterEvent>
#include "Texture2D.h"
#include "qmimedata.h"
#include <QColor>
#include <qcolordialog.h>
#include <qtimer.h>

VPropEditor::VPropEditor(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_LO = new QVBoxLayout(this);
	m_LO->setAlignment(Qt::AlignTop);
	m_LO->setSpacing(15);
	setLayout(m_LO);

	QTimer* timer = new QTimer(this);
	QObject::connect(timer, &QTimer::timeout, [&]() {
			
		if (m_Node != nullptr) {

			if (m_BlockTimer) return;
			m_BlockRot = true;
			//update pos
			auto pos = m_Node->GetPosition();
			m_NodePosX->setValue(pos.x);
			m_NodePosY->setValue(pos.y);
			m_NodePosZ->setValue(pos.z);
			//update rot
			//return;
			auto rot = m_Node->GetRotationEU();
		//	m_NodeRotX->setValue(rot.y);
	//		m_NodeRotY->setValue(rot.x);
			//m_NodeRotZ->setValue(rot.z);
			m_BlockRot = false;


			
		}


		});

	// Start the timer with an interval of 1000 milliseconds (1 second)
	timer->start(1000);
}

void VPropEditor::UpdateNode() {

	m_BlockRot = true;
	auto rot = m_Node->GetRotationEU();
	m_NodeRotX->setValue(360-rot.x);
	m_NodeRotY->setValue(360-rot.y);
	m_NodeRotZ->setValue(360-rot.z);


	m_BlockRot = false;
}

void VPropEditor::SetMaterial(MaterialBase* material) {

	m_Material = material;

	QLabel* mat_edit_lab = new QLabel(std::string("Material:" + material->GetPath()).c_str());

	m_LO->addWidget(mat_edit_lab);

	QHBoxLayout* dif_box = new QHBoxLayout(this);

	auto dif_lab = new QLabel("Diffuse");

	m_DiffuseImg = new VImagePreview(this);
//	QPixmap pix = QPixmap(material->GetDiffuse()->GetPath().c_str());
	//QPixmap scaledPixmap = pix.scaled(64,64, Qt::KeepAspectRatio, Qt::SmoothTransformation);

	m_DiffuseImg->SetSize(64, 64);
	m_DiffuseImg->SetImage(material->GetDiffuse()->GetPath().c_str());
	QObject::connect(m_DiffuseImg, &VImagePreview::dropped, [&](const QString& filePath) {
		//qDebug() << "File dropped:" << filePath;
		m_Material->SetDiffuse(new Texture2D(filePath.toStdString()));
		});
	//m_DiffuseImg->setPixmap(scaledPixmap);
//	m_DiffuseImg->setFixedSize(64, 64);
	//m_DiffuseImg->setAcceptDrops(true);

	
	dif_box->addWidget(dif_lab);
	dif_box->addWidget(m_DiffuseImg);

	dif_box->setAlignment(Qt::AlignLeft);
	dif_box->setSpacing(15);

	auto dif_browse = new QPushButton("Browse");

	dif_box->addWidget(dif_browse);

	m_LO->addLayout(dif_box);

	auto spec_box = new QHBoxLayout(this);

	auto spec_lab = new QLabel("Spcular");

	m_SpecImg = new VImagePreview(this);
	//	QPixmap pix = QPixmap(material->GetDiffuse()->GetPath().c_str());
		//QPixmap scaledPixmap = pix.scaled(64,64, Qt::KeepAspectRatio, Qt::SmoothTransformation);

	m_SpecImg->SetSize(64, 64);
	m_SpecImg->SetImage(material->GetSpecular()->GetPath().c_str());
	QObject::connect(m_SpecImg, &VImagePreview::dropped, [&](const QString& filePath) {
		//qDebug() << "File dropped:" << filePath;
		m_Material->SetSpecular(new Texture2D(filePath.toStdString()));
		});



	spec_box->addWidget(spec_lab);
	spec_box->addWidget(m_SpecImg);

	spec_box->setAlignment(Qt::AlignLeft);
	spec_box->setSpacing(15);

	auto spec_browse = new QPushButton("Browse");

	spec_box->addWidget(spec_browse);

	m_LO->addLayout(spec_box);


	//---

	auto norm_box = new QHBoxLayout(this);

	auto norm_lab = new QLabel("Normals");

	m_NormImg = new VImagePreview(this);
	//	QPixmap pix = QPixmap(material->GetDiffuse()->GetPath().c_str());
		//QPixmap scaledPixmap = pix.scaled(64,64, Qt::KeepAspectRatio, Qt::SmoothTransformation);

	m_NormImg->SetSize(64, 64);
	m_NormImg->SetImage(material->GetNormal()->GetPath().c_str());
	QObject::connect(m_NormImg, &VImagePreview::dropped, [&](const QString& filePath) {
		//qDebug() << "File dropped:" << filePath;
		m_Material->SetNormals(new Texture2D(filePath.toStdString()));
		});
	

	norm_box->addWidget(norm_lab);
	norm_box->addWidget(m_NormImg);

	norm_box->setAlignment(Qt::AlignLeft);
	norm_box->setSpacing(15);

	auto norm_browse = new QPushButton("Browse");

	norm_box->addWidget(norm_browse);

	dif_lab->setMinimumWidth(55);
	spec_lab->setMinimumWidth(55);
	norm_lab->setMinimumWidth(55);
	dif_lab->setAlignment(Qt::AlignTop);
	spec_lab->setAlignment(Qt::AlignTop);
	norm_lab->setAlignment(Qt::AlignTop);

	m_LO->addLayout(norm_box);

	auto col_diff_box = new QHBoxLayout(this);

	auto col_dif_lab = new QLabel("Diffuse");

	col_dif_lab->setMinimumWidth(55);

	
	
	/*
	auto diff_lab = new QLabel();
	diff_lab->setAutoFillBackground(true);
	
	
	QColor dif_col;

	
	float4 col = m_Material->GetDiffuseColor();
	dif_col.setRgb(col.x * 255.0f, col.y * 255.0f, col.z * 255.05, 255);
	QPalette pal = diff_lab->palette();
	pal.setColor(QPalette::Window, dif_col);
	diff_lab->setPalette(pal);

	col_diff_box->addWidget(col_dif_lab);
	col_diff_box->addWidget(diff_lab);
	col_dif_lab->setAlignment(Qt::AlignTop);
	
	diff_lab->setMinimumWidth(16);
	diff_lab->setMinimumHeight(12);
	*/
	m_DiffCol = new VColorPreview;

	col_diff_box->addWidget(col_dif_lab);
	col_diff_box->addWidget(m_DiffCol);
	m_DiffCol->SetColor(m_Material->GetDiffuseColor());
	//diff_prev->setAcceptDrops()
	col_diff_box->setAlignment(Qt::AlignLeft);

	QPushButton* pick_diff = new QPushButton("Pick Color");
	col_diff_box->addWidget(pick_diff);
	pick_diff->setMinimumWidth(50);

	QObject::connect(pick_diff, &QPushButton::clicked, [&]() {
		//	qDebug() << "Button clicked!";
	//	m_Material->SaveMaterial(m_Material->GetPath());
		QColor color = QColorDialog::getColor(Qt::white, this, "Select Diffuse Color");
		if (color.isValid()) {
			//updateColor(color);
			m_DiffCol->SetColor(float4(color.redF(), color.greenF(), color.blueF(), 1.0));
			m_Material->SetDiffuseColor(float4(color.redF(), color.greenF(), color.blueF(), 1.0f));
		}
		});



	//------

	auto col_spec_box = new QHBoxLayout(this);

	auto col_spec_lab = new QLabel("Specular");

	col_spec_lab->setMinimumWidth(55);
		
	m_SpecCol = new VColorPreview;

	col_spec_box->addWidget(col_spec_lab);
	col_spec_box->addWidget(m_SpecCol);
	m_SpecCol->SetColor(m_Material->GetSpecularColor());
	//diff_prev->setAcceptDrops()
	col_spec_box->setAlignment(Qt::AlignLeft);

	QPushButton* pick_spec = new QPushButton("Pick Color");
	col_spec_box->addWidget(pick_spec);
	pick_spec->setMinimumWidth(50);
	//---------

	QObject::connect(pick_spec, &QPushButton::clicked, [&]() {
		//	qDebug() << "Button clicked!";
	//	m_Material->SaveMaterial(m_Material->GetPath());
		QColor color = QColorDialog::getColor(Qt::white, this, "Select Specular Color");
		if (color.isValid()) {
			//updateColor(color);
			m_SpecCol->SetColor(float4(color.redF(), color.greenF(), color.blueF(), 1.0));
			m_Material->SetSpecularColor(float4(color.redF(), color.greenF(), color.blueF(), 1.0f));
		}
		});

	


	QPushButton* save = new QPushButton("Apply");

	save->setMaximumWidth(80);

	QObject::connect(save, &QPushButton::clicked, [&]() {
	//	qDebug() << "Button clicked!";
		m_Material->SaveMaterial(m_Material->GetPath());
		});

	m_LO->addLayout(col_diff_box);
	m_LO->addLayout(col_spec_box);
	m_LO->addWidget(save);


}

void VPropEditor::SetNode(Node* node) {

	int b = 5;

	m_Node = node;

	QLabel* node_edit_lab = new QLabel(std::string("Node : " + node->GetName()).c_str());

	m_LO->addWidget(node_edit_lab);

	//Node::Position

	QHBoxLayout* pos_box = new QHBoxLayout(this);

	auto pos_lab = new QLabel("Position");

	auto xlab = new QLabel("X");
	auto ylab = new QLabel("Y");
	auto zlab = new QLabel("Z");

	m_NodePosX = new QDoubleSpinBox(this);
	m_NodePosY = new QDoubleSpinBox(this);
	m_NodePosZ = new QDoubleSpinBox(this);
	m_NodePosX->setSingleStep(0.1f);
	m_NodePosY->setSingleStep(0.1f);
	m_NodePosZ->setSingleStep(0.1f);
	m_NodePosX->setMinimumWidth(100);
	m_NodePosY->setMinimumWidth(100);
	m_NodePosZ->setMinimumWidth(100);


	float3 pos = node->GetPosition();
	m_NodePosX->setValue(pos.x);
	m_NodePosY->setValue(pos.y);
	m_NodePosZ->setValue(pos.z);

	m_NodePosX->setDecimals(2);
	m_NodePosX->setRange(-10000, 10000);

	m_NodePosY->setDecimals(2);
	m_NodePosY->setRange(-10000, 10000);

	m_NodePosZ->setDecimals(2);
	m_NodePosZ->setRange(-10000, 10000);

	// Position
	pos_box->addWidget(pos_lab);
	pos_box->addWidget(xlab);
	pos_box->addWidget(m_NodePosX);
	pos_box->addWidget(ylab);
	pos_box->addWidget(m_NodePosY);
	pos_box->addWidget(zlab);
	pos_box->addWidget(m_NodePosZ);

	//position events

	QObject::connect(m_NodePosX, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		[&](double value) {
			auto pos = m_Node->GetPosition();
			pos.x = value;
			m_Node->SetPosition(pos);

			//label->setText(QString("Value: %1").arg(value, 0, 'f', 2));
		});


	QObject::connect(m_NodePosY, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		[&](double value) {
			auto pos = m_Node->GetPosition();
			pos.y = value;
			m_Node->SetPosition(pos);

			//label->setText(QString("Value: %1").arg(value, 0, 'f', 2));
		});


	QObject::connect(m_NodePosZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		[&](double value) {
			auto pos = m_Node->GetPosition();
			pos.z = value;
			m_Node->SetPosition(pos);

			//label->setText(QString("Value: %1").arg(value, 0, 'f', 2));
		});

	pos_box->setAlignment(Qt::AlignLeft);
	pos_box->setSpacing(5);

	m_LO->addLayout(pos_box);

	//Rotation


	QHBoxLayout* rot_box = new QHBoxLayout(this);

	auto rot_lab = new QLabel("Rotation");

	xlab = new QLabel("P");
	ylab = new QLabel("Y");
	zlab = new QLabel("R");


	m_NodeRotX = new QDoubleSpinBox(this);
	m_NodeRotY = new QDoubleSpinBox(this);
	m_NodeRotZ = new QDoubleSpinBox(this);
	m_NodeRotX->setSingleStep(5);
	m_NodeRotY->setSingleStep(5);
	m_NodeRotZ->setSingleStep(5);
	m_NodeRotX->setMinimumWidth(100);
	m_NodeRotY->setMinimumWidth(100);
	m_NodeRotZ->setMinimumWidth(100);


	float3 rot = float3(0, 0, 0);// node->GetRotationEU();
	m_NodeRotX->setValue(rot.x);
	m_NodeRotY->setValue(rot.y);
	m_NodeRotZ->setValue(rot.z);

	m_NodeRotX->setDecimals(3);
	m_NodeRotX->setRange(-1000,1000);

	m_NodeRotY->setDecimals(3);
	m_NodeRotY->setRange(-1000,1000);

	m_NodeRotZ->setDecimals(3);
	m_NodeRotZ->setRange(-1000,10000);

	// Position
	rot_box->addWidget(rot_lab);
	rot_box->addWidget(xlab);
	rot_box->addWidget(m_NodeRotX);
	rot_box->addWidget(ylab);
	rot_box->addWidget(m_NodeRotY);
	rot_box->addWidget(zlab);
	rot_box->addWidget(m_NodeRotZ);

	QObject::connect(m_NodeRotX, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		[&](double value) {
			m_BlockTimer = true;
			if (m_BlockRot) return;
			auto rot = m_Node->GetRotationEU();
			rot.x = value;
			rot.y = m_NodeRotY->value();
			rot.z = m_NodeRotZ->value();
			
			m_Node->SetRotation(rot.x, rot.y, rot.z,true);
			m_BlockTimer = false;
			//label->setText(QString("Value: %1").arg(value, 0, 'f', 2));
		});


	QObject::connect(m_NodeRotY, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		[&](double value) {

			m_BlockTimer = true;
			if (m_BlockRot) return;
			auto rot = m_Node->GetRotationEU();
			rot.x = m_NodeRotX->value();
			rot.y = value;
			rot.z = m_NodeRotZ->value();


			m_Node->SetRotation(rot.x, rot.y, rot.z,true);
			m_BlockTimer = false;

			//label->setText(QString("Value: %1").arg(value, 0, 'f', 2));
		});


	QObject::connect(m_NodeRotZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		[&](double value) {
			if (m_BlockRot) return;
			auto rot = m_Node->GetRotationEU();
			rot.z = value;


			//auto rot = m_Node->GetRotationEU();
			rot.x = m_NodeRotX->value();
			rot.z = value;
			rot.y = m_NodeRotY->value();


			m_Node->SetRotation(rot.x, rot.y, rot.z, true);

			//m_Node->SetRotation(rot.x, rot.y, rot.z);


			//label->setText(QString("Value: %1").arg(value, 0, 'f', 2));
		});


	rot_box->setAlignment(Qt::AlignLeft);
	rot_box->setSpacing(5);

	m_LO->addLayout(rot_box);


}

VPropEditor::~VPropEditor()
{}
