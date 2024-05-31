#pragma once

#include <QWidget>
#include "ui_VTools.h"
#include <qtoolbar.h>

class VTools : public QToolBar
{
	Q_OBJECT

public:
	VTools(QWidget *parent = nullptr);
	~VTools();

private:
	Ui::VToolsClass ui;
};
