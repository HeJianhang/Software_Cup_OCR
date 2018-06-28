#ifndef MAINWINDOW_H

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
#include <QThread>
#include <QSemaphore>
#include <qthreadpool.h>
#include<QProgressDialog>
#include <qdebug.h>
#include "titlebar.h"
#include "ocrRunnable.h"
#include <OCRDll.h>

#define MAINWINDOW_H

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(string path1, string path2, string path3, string path4,QWidget *parent = 0);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
public Q_SLOTS:
	bool close();
private slots:
    void on_fileButton_clicked();

    void on_checkButton_clicked();

    void on_excelButton_clicked();

	void updateTableView(const MyPair&);

	void doneOne();
	void showMessageBox(string ccontent);
private:
	StartRunnable* startRunnable;
	OCRRunnable** threadList;
	int count;
	QString root;
    Ui::MainWindow *ui;
	QProgressDialog *dialog;
    QPoint last;
	QStandardItemModel *model;
    std::vector<std::string> pathList;
    QStringList getFileNames(const QString &path);
    QHBoxLayout* m_toplayout;
    QVBoxLayout* m_mainLayout;
    TitleBar* m_titleWidget;
	void initTableView();
	void setTableView(const pair<std::string,std::string>& data, const int index);
	void initProcess();
	void cancelOcr();
};

#endif // MAINWINDOW_H
