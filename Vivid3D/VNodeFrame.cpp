#include "VNodeFrame.h"
#include <qdrag.h>
#include <qevent.h>
#include <qmimedata.h>
#include "Editor.h"
#include "SceneGraph.h"
#include "VTrackNode.h"
#include <qboxlayout.h>
#include "VTrackTimeLine.h"
#include "VTrackFrame.h"

VNodeFrame::VNodeFrame(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);
    setAcceptDrops(true);
}


void VNodeFrame::dragEnterEvent(QDragEnterEvent* event)
{
   // if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
  //  }
}

void VNodeFrame::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
   
    auto url = mimeData->text().toStdString();

    auto node = Editor::m_Graph->FindNode(url);

    int b = 5;

    auto lay = layout();

    VTrackNode* new_TrackNode = new VTrackNode;

    new_TrackNode->setMaximumWidth(size().width()-20);
    new_TrackNode->setMinimumWidth(size().width()-20);
    new_TrackNode->setMaximumHeight(60);
    new_TrackNode->setMinimumHeight(60);

    lay->addWidget(new_TrackNode);

    new_TrackNode->SetNode(node);

    Editor::m_TrackPanel->AddTimeLine(node);

   // new_track->setMinimumHeight(60);
   // new_track->setMaximumHeight(60);
   


    
    //if (mimeData->hasUrls()) {
       // QList<QUrl> urls = mimeData->urls();
       // for (const QUrl& url : urls) {
        //    qDebug() << "Dropped file path:" << url.toLocalFile();
            // Handle the dropped file(s) here
      //  }
      //  event->acceptProposedAction();
    //}
    nodes++;

    this->setMinimumHeight(nodes * 85);

}


VNodeFrame::~VNodeFrame()
{}
