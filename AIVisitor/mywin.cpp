#include "mywin.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include <qstandarditemmodel.h>

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_mainLayout = new QVBoxLayout(this);
    //m_toplayout = new QHBoxLayout(this);

    m_titleWidget = new TitleBar(this);
    m_mainLayout->addWidget(m_titleWidget, 0, Qt::AlignTop);
    //m_mainLayout->addLayout(m_toplayout);

    setLayout(m_mainLayout);
    setFixedSize(700, 500);
    setWindowFlags(Qt::FramelessWindowHint);
    connect(m_titleWidget, SIGNAL(customShowMinWindow()), this, SLOT(showMinimized()));
    connect(m_titleWidget, SIGNAL(customCloseWindow()), this, SLOT(close()));

}
