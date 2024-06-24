#include "VTimeTrack.h"
#include <qpainter.h>
#include <qstatictext.h>

VTimeTrack::VTimeTrack(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}


void VTimeTrack::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	int cx = 9;
	QPen pen;
	pen.setColor(Qt::white);
	pen.setWidth(1);
	painter.setPen(pen);
	int sec = 0;

	for (int x = 0; x < size().width(); x = x + 8) {

		if (cx == 9) {

			
			painter.drawLine(QLine(x, 4, x, 8+15));
			painter.drawStaticText(QPoint(x+4, 0), QStaticText(std::to_string(sec).c_str()));
			sec++;
		}
		else if (cx == 4) {
			painter.drawLine(QLine(x, 10, x, (8 + 15)));
		}else{
			painter.drawLine(QLine(x,8+15, x, 8+12));
		}

		cx++;
		if (cx == 10) {
			cx = 0;
		}
	
	}

}

VTimeTrack::~VTimeTrack()
{}
