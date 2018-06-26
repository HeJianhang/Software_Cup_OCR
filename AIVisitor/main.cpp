#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));

    QString root = QCoreApplication::applicationDirPath();

    MainWindow w;
    w.setWindowIcon(QIcon(root + "/static/logo"));
    w.show();

    return a.exec();
}
