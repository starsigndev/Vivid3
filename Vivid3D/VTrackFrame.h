#pragma once

#include <QWidget>
#include "ui_VTrackFrame.h"
#include <qframe.h>

class Node;

class VTrackFrame : public QFrame
{
	Q_OBJECT

public:
	VTrackFrame(QWidget *parent = nullptr);
	~VTrackFrame();
	void AddTimeLine(Node* node);

private:
	Ui::VTrackFrameClass ui;
};
