#include "VTrackFrame.h"
#include "VTrackTimeLine.h"
#include <qboxlayout.h>

VTrackFrame::VTrackFrame(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);
}

VTrackFrame::~VTrackFrame()
{}

void VTrackFrame::AddTimeLine(Node* node) {

    auto lay = layout();

    VTrackTimeLine* new_Track = new VTrackTimeLine;

    //new_Track->setMaximumWidth(size().width() - 20);
    //new_Track->setMinimumWidth(size().width() - 20);
    new_Track->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    new_Track->setMaximumHeight(60);
    new_Track->setMinimumHeight(60);

    lay->addWidget(new_Track);

}