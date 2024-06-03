#include "VImagePreview.h"

VImagePreview::VImagePreview(QWidget *parent)
	: QLabel(parent)
{
	ui.setupUi(this);
	setStyleSheet("border: 2px dashed #aaa;");
	setAcceptDrops(true);
}

void VImagePreview::SetSize(int w, int h) {

	m_PrevW = w;
	m_PrevH = h;

}

void VImagePreview::SetImage(std::string path) {

	QPixmap map = QPixmap(path.c_str());
	map = map.scaled(m_PrevW, m_PrevH);
	setPixmap(map);


}

void VImagePreview::dragEnterEvent(QDragEnterEvent* event) {
	if (event->mimeData()->hasUrls()) {
		event->acceptProposedAction();

	}
}

void VImagePreview::dropEvent(QDropEvent* event) {
	if (event->mimeData()->hasUrls()) {
		QList<QUrl> urls = event->mimeData()->urls();
		QString filePath;
		if (!urls.isEmpty() && urls.first().isLocalFile()) {
			filePath = urls.first().toLocalFile();
			//setPixmap(QPixmap(filePath));
			SetImage(filePath.toStdString());
			emit dropped(filePath); // Emit the custom dropped sig
		}
		event->acceptProposedAction();
	}
}



VImagePreview::~VImagePreview()
{}
