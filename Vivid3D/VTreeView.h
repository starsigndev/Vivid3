#pragma once

#include <QWidget>
#include "ui_VTreeView.h"
#include <string>
#include <vector>
#include <QResizeEvent>
#include <QDebug>
struct TreeItem {

	std::string m_Text;
	std::vector<TreeItem*> m_Items;
	bool m_Open = true;
	TreeItem* AddItem(std::string text) {
		TreeItem* item = new TreeItem;
		item->m_Text = text;
		m_Items.push_back(item);
		return item;
	}

};

class VTreeView : public QWidget
{
	Q_OBJECT

public:
	VTreeView(QWidget *parent = nullptr);
	~VTreeView();

	int RenderItem(TreeItem* item, int x, int y);
	int CheckItem(TreeItem* item, int x, int y, int px, int py);
	void SetRoot(TreeItem* item) {
		m_Root = item;
	}

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	Ui::VTreeViewClass ui;
	TreeItem* m_Root;
	TreeItem* m_OverItem = nullptr;
};