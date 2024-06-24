#pragma once

#include <QWidget>
#include "ui_VTrackNode.h"

class Node;

class VTrackNode : public QWidget
{
	Q_OBJECT

public:
	VTrackNode(QWidget *parent = nullptr);
	~VTrackNode();
	void SetNode(Node* node);
protected:
	void paintEvent(QPaintEvent* event) override;

private:
	Ui::VTrackNodeClass ui;
	Node* m_Node = nullptr;
};
