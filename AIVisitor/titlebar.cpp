#include "titlebar.h"
#include<QPainter>
#include<QPoint>
#include<QImage>
#include<QPixmap>
#include<QBitmap>
#include<QPen>
#include <QApplication>

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    QString root = QCoreApplication::applicationDirPath();

    m_layout = new QHBoxLayout(this);
    m_closeBtn = new CustomPushButton(this);
    m_minBtn = new CustomPushButton(this);
    m_winTitle = new QLabel(QStringLiteral("AI Visitor"), this);
    m_winTitle->setStyleSheet("color: black; font-size: 12px");

    m_closeBtn->setButtonBgrd(QString(root + "/static/Buttons/close"));
    m_minBtn->setButtonBgrd(QString(root + "/static/Buttons/min"));
    m_layout->addWidget(m_winTitle, 0, Qt::AlignCenter);
    m_layout->addStretch();
    m_layout->addWidget(m_minBtn, 0, Qt::AlignRight);
    m_layout->addWidget(m_closeBtn, 0, Qt::AlignRight);

    m_layout->setSpacing(0);
    m_layout->setContentsMargins(15, 0, 5, 0);
    setLayout(m_layout);
    setFixedSize(700, 30);

    connect(m_closeBtn, SIGNAL(clicked()), this, SIGNAL(customCloseWindow()));
    connect(m_minBtn, SIGNAL(clicked()), this, SIGNAL(customShowMinWindow()));
}

void TitleBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    //painter.drawPixmap(QRect(0, 0, width(), height()), QPixmap("background.png"));
    painter.drawRect(QRect(0, 0, width(), height()));
}
