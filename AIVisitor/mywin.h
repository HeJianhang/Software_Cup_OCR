#ifndef MYWIN_H
#define MYWIN_H

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

#include "titlebar.h"

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = 0);

private slots:

private:
    //QHBoxLayout* m_toplayout;
    QVBoxLayout* m_mainLayout;
    TitleBar* m_titleWidget;
};

#endif // MYWIN_H
