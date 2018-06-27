#include "processwindow.h"

ProcessWindow::ProcessWindow(QWidget *parent)
	: QWidget(parent)
{
	QString root = QCoreApplication::applicationDirPath();

	m_layout = new QHBoxLayout(this);

	m_layout->setSpacing(0);
	m_layout->setContentsMargins(15, 0, 5, 0);
	setLayout(m_layout);
	setFixedSize(700, 30);
}