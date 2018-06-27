#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include<QProgressDialog>
#include <qdebug.h>
#include "titlebar.h"
#include "processwindow.h"
//#include <OCRDll.h>
#include <iostream>

using namespace std;
namespace Ui {

class MainWindow;
}

typedef pair<std::pair<std::string, std::string>, int> MyPair;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
	void Result(const MyPair&);
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void on_fileButton_clicked();

    void on_checkButton_clicked();

    void on_excelButton_clicked();

	void updateTableView(const MyPair&);
private:
	int count;
	QProgressDialog *dialog;
	QString root;
	QSemaphore freeSpace;
    Ui::MainWindow *ui;
	ProcessWindow *process_window;
    QPoint last;
	QStandardItemModel *model;
    std::vector<std::string> pathList;
    QStringList getFileNames(const QString &path);
    QHBoxLayout* m_toplayout;
    QVBoxLayout* m_mainLayout;
    TitleBar* m_titleWidget;
	void initTableView();
	void setTableView(const pair<std::string,std::string>& data, const int index);
	void asyOcr(const std::string, const int);
};

#endif // MAINWINDOW_H
