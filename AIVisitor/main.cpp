#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));

    QString root = QCoreApplication::applicationDirPath();
    MainWindow w(root +"/labels.txt", root +"/frozen_model.pb", root + "/yolov3-obj.cfg", root + "/yolov3-obj_7400.weights");
    w.setWindowIcon(QIcon(root + "/static/logo"));
    w.show();

    return a.exec();
}
