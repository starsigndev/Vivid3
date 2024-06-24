#pragma once

#include <QWidget>
#include "ui_VTrackTimeLine.h"

class VTrackTimeLine : public QWidget
{
	Q_OBJECT

public:
	VTrackTimeLine(QWidget *parent = nullptr);
	~VTrackTimeLine();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	Ui::VTrackTimeLineClass ui;
};
