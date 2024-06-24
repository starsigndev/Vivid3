#pragma once

#include <QWidget>
#include "ui_VTimeTrack.h"

class VTimeTrack : public QWidget
{
	Q_OBJECT

public:
	VTimeTrack(QWidget *parent = nullptr);
	~VTimeTrack();
protected:
	void paintEvent(QPaintEvent* event) override;

private:
	Ui::VTimeTrackClass ui;
};
