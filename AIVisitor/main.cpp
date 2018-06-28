#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));

    QString root = QCoreApplication::applicationDirPath();
	string strRoot = string(root.toLocal8Bit());
    MainWindow w(strRoot +"/labels.txt",strRoot+"/frozen_model.pb", strRoot + "/yolov3-obj.cfg", strRoot + "/yolov3-obj_7400.weights");
    w.setWindowIcon(QIcon(root + "/static/logo"));
    w.show();

    return a.exec();
}
