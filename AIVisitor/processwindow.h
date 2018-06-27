#ifndef PROCESSWINDOW_H
#define PROCESSWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QAbstractItemView>
#include <QWidgetItem>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QIcon>
#include <QRegExp>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileIconProvider>
#include <QPixmap>
#include <vector>
#include <string>
#include <QDebug>
#include <QMouseEvent>
#include <QtConcurrent>
#include <QThread>
#include <QSemaphore>

#include <qdebug.h>
#include "titlebar.h"


class ProcessWindow : public QWidget
{
	Q_OBJECT

public:
	explicit ProcessWindow (QWidget *parent);
	~ProcessWindow() {}

private:
	QHBoxLayout * m_layout;
};

#endif // PROCESSWINDOW_H