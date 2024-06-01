#pragma once

#include <QWidget>
#include "ui_VContentView.h"

class ContentItem {
public:
	std::string m_Name = "";
	std::string m_FullPath = "";
	int m_DrawX, m_DrawY;
	bool m_Folder = false;
};

class VContentView : public QWidget
{
	Q_OBJECT

public:
	VContentView(QWidget *parent = nullptr);
	~VContentView();
	void Browse(std::string path);
	void UpdateView();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
private:
	Ui::VContentViewClass ui;
	ContentItem* m_OverItem = nullptr;
	std::vector<ContentItem*> m_Files;
	std::vector<ContentItem*> m_Folders;
	std::vector<ContentItem*> m_All;
};
