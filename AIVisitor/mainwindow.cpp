#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include <qstandarditemmodel.h>
#include "excel.h"

using namespace std;

MainWindow::MainWindow(QString labelPath, QString modelPath, QString yoloCfgPath, QString yoloWeightPath,QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	init(string(labelPath.toLocal8Bit()), convert_wstring_to_utf8_string(modelPath.toStdWString()).c_str(), string(yoloCfgPath.toLocal8Bit()), string(yoloWeightPath.toLocal8Bit()));
	
	threadList = new OCRRunnable*[THREAD_COUNT];
	startRunnable = new StartRunnable();
	startRunnable->setThreadList(threadList);
	
	qRegisterMetaType<MyPair>("MyPair");

	root = QCoreApplication::applicationDirPath();

	this->setAutoFillBackground(false);
	QPalette palette = this->palette();
	palette.setBrush(QPalette::Window,
		QBrush(QPixmap(root + "/static/background.png")));
	this->setPalette(palette);

	ui->setupUi(this);
	
	m_mainLayout = new QVBoxLayout(this);
	m_toplayout = new QHBoxLayout(this);

	m_titleWidget = new TitleBar(this);
	m_mainLayout->addWidget(m_titleWidget, 5, Qt::AlignTop);
	//m_mainLayout->addLayout(m_toplayout);

	setLayout(m_mainLayout);
	setFixedSize(900, 600);
	setWindowFlags(Qt::FramelessWindowHint);

	connect(m_titleWidget, SIGNAL(customShowMinWindow()), this, SLOT(showMinimized()));
	connect(m_titleWidget, SIGNAL(customCloseWindow()), this, SLOT(close()));
	//connect(this, SIGNAL(ocrRunnable::Result(const MyPair&)), this, SLOT(updateTableView(const MyPair&)),Qt::QueuedConnection);
	for (int i = 0; i < THREAD_COUNT; ++i)
	{
		threadList[i] = new OCRRunnable();
		connect(threadList[i], SIGNAL(Result(const MyPair&)), this, SLOT(updateTableView(const MyPair&)), Qt::QueuedConnection);
		connect(threadList[i], SIGNAL(DoneOne()), this, SLOT(doneOne()), Qt::QueuedConnection);
	}
	// 加载CSS文件
	//QString strPath = QCoreApplication::applicationDirPath();
	QString strCssFile = root + "/static/default.css";
	QFile fCss(strCssFile);
	if (!fCss.open(QFile::ReadOnly))
	{
		//qDebug("css File %s load false", strCssFile);
		return;
	}
	QString strCssContent(fCss.readAll());
	setStyleSheet(strCssContent);
	fCss.close();

	initTableView();

	initProcess();

}

MainWindow::~MainWindow()
{
	delete startRunnable;
	for (int i = 0; i < THREAD_COUNT; ++i)
		delete threadList[i];
	delete[] threadList;
	delete dialog;
	delete ui;
	destroy();
}

void MainWindow::on_fileButton_clicked()
{
	if (!dialog->isHidden())
	{
		showMessageBox("正在识别中，请先取消！");
		return;
	}
	QString path = QFileDialog::getExistingDirectory();
	if (path.length() == 0) {
		//qDebug("No select file!");
	}
	else {
		//qDebug("You select %s", path);
		pathList.clear(); // 清空之前的路径
	}
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	QStringList files = getFileNames(path);
	for (QString str : files) {
		//qDebug() << str;
		pathList.push_back(string(str.toLocal8Bit()));
	}
	QApplication::restoreOverrideCursor();

}

QStringList MainWindow::getFileNames(const QString &path)
{
	QDir dir(path);
	QString filter;
	QFileInfoList fileInfos = dir.entryInfoList();
	QStringList files;
	for (QFileInfo qfo : fileInfos)
	{
		filter = qfo.suffix(); //获取后缀名
		if ((filter != "jpg") && (filter != "jpeg") && (filter != "png"))
		{
			continue;
		}
		files.append(qfo.absoluteFilePath());
	}

	return files;
}

void MainWindow::initTableView()
{
	
	// 设置表头
	model = new QStandardItemModel();
	model->setColumnCount(2);
	model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("企业名称"));
	model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("企业注册号"));
	ui->tableView->setModel(model);

	ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:#a91e25;"
		"color: white; padding-left: 4px;border: 1px solid #a91e25;}");
	ui->tableView->verticalHeader()->setStyleSheet("QHeaderView::section {background-color:#a91e25;"
		"color: white ;padding-left: 4px;border: 1px solid #a91e25;}");

	ui->tableView->setShowGrid(false);  // disable the table grid.
										//ui->tableView->verticalHeader()->hide();
	ui->tableView->horizontalHeader()->setDefaultSectionSize(180);
	ui->tableView->verticalHeader()->setDefaultSectionSize(40);  // set row height.
	QFont f = ui->tableView->font();
	f.setBold(true);
	ui->tableView->horizontalHeader()->setFont(f);
	ui->tableView->setColumnWidth(0, 360);
	ui->tableView->setColumnWidth(1, 250);
	ui->tableView->horizontalHeader()->setHighlightSections(false);
	ui->tableView->setFrameShape(QFrame::NoFrame);
	//ui->tableView->setItemDelegate(new NoFocusFrameDelegate());

	// 设置行内数据不可编辑
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//删除所有行
	//model->removeRows(0,model->rowCount());


}

void MainWindow::setTableView(const pair<std::string, std::string>& data, const int index)
{
	//qDebug()<<QString::fromStdString(data.first);
	//qDebug()<<index;
	model->setItem(index, 0, new QStandardItem(QString::fromLocal8Bit(data.first.c_str())));
	//设置字符颜色
	model->item(index, 0)->setForeground(QBrush(QColor(255, 0, 0)));
	//设置字符位置
	//model->item(index, 0)->setTextAlignment(Qt::AlignCenter);
	model->setItem(index, 1, new QStandardItem(QString::fromLocal8Bit(data.second.c_str())));
}

void MainWindow::updateTableView(const MyPair& p)
{
	setTableView(p.first, p.second);
}

void MainWindow::on_checkButton_clicked()
{
	if (pathList.size() <= 0)
	{
		showMessageBox("该目录不存在任何图片文件（格式仅支持*.jpg、*.jpeg、*.png）！");
		return;
	}
	else if (!dialog->isHidden())
	{
		showMessageBox("正在识别中，请先取消！");
		return;
	}
	if (startRunnable->isRunning)
	{
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
		startRunnable->clear();
		startRunnable->reset();
		QApplication::restoreOverrideCursor();
	}
	else
		startRunnable->reset();
	dialog->reset();
	dialog->setValue(0);
	dialog->setRange(0, pathList.size());
	model->removeRows(0, model->rowCount());
	count = 0;
	startRunnable->setPathList(&pathList);
	startRunnable->isRunning = true;
	QThreadPool::globalInstance()->start(startRunnable);
	if(pathList.size()>0)
		dialog->show();
}

void MainWindow::on_excelButton_clicked()
{
	if (!dialog->isHidden())
	{
		showMessageBox("正在识别中，请先取消！");
		return;
	}
	QString fileName;
	fileName = QFileDialog::getSaveFileName(this,
		tr("Open Config"), "", tr("Config Files (*.xlsx)"));
	if (!fileName.isNull())
	{
		//qDebug() << fileName;
	}
	else {
		return;
	}
	wstring str_fileName = fileName.toStdWString();


	create_result_excel(str_fileName, model);

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	last = e->globalPos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
	int dx = e->globalX() - last.x();
	int dy = e->globalY() - last.y();
	last = e->globalPos();
	move(x() + dx, y() + dy);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
	int dx = e->globalX() - last.x();
	int dy = e->globalY() - last.y();
	move(x() + dx, y() + dy);
}

bool MainWindow::close()
{
	if (!dialog->isHidden())
	{
		showMessageBox("正在识别中，请先取消！");
		return false;
	}
	else if (startRunnable->isRunning)
	{
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
		startRunnable->clear();
		QApplication::restoreOverrideCursor();
	}
	dialog->close();
	return QWidget::close();
}


void MainWindow::initProcess()
{
	dialog = new QProgressDialog(this);
	dialog->reset();
	dialog->setAttribute(Qt::WA_DeleteOnClose,false);
	//dialog->setLabelText(QString::fromLocal8Bit("识别进度"));
	dialog->setCancelButtonText(QString::fromLocal8Bit("取消"));
	//dialog->setGeometry((900-600)/2, (600-200)/2, 600, 160);
	//dialog->setWindowModality(Qt::WindowModal);//将对话框设置为模态的  
	dialog->setFixedSize(600, 160);
	dialog->setAutoClose(true);
	QPushButton *cbtn = new QPushButton(this);
	cbtn->setStyleSheet("QPushButton{min-width:80px;min-height:30px;color:white} ");
	cbtn->setText(QString::fromLocal8Bit("取消"));
	dialog->setCancelButton(cbtn);
	QPalette palette = dialog->palette();
	palette.setBrush(QPalette::Window,
		QBrush(QPixmap(root + "/static/dialogbg.png")));
	dialog->setPalette(palette);
	connect(dialog, &QProgressDialog::canceled, this, &MainWindow::cancelOcr);
	//connect(cbtn, &QPushButton::clicked, this, &MainWindow::cancelOcr);
}

void MainWindow::cancelOcr()
{
	if (startRunnable->isRunning)
	{
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
		startRunnable->clear();
		QApplication::restoreOverrideCursor();
	}
	dialog->hide();
}

void MainWindow::doneOne()
{
	if (!startRunnable->isToStop)
	{
		dialog->setValue(dialog->value() + 1);
		if (dialog->isHidden())
		{
			showMessageBox("识别完成！");
		}
	}
}

void MainWindow::showMessageBox(string content)
{

	QMessageBox message(QMessageBox::Warning, "", QString::fromLocal8Bit(content.c_str()));
	message.setButtonText(1, QString::fromLocal8Bit("确认"));
	message.setWindowIcon(QIcon(root + "/static/logo"));
	message.exec();
	return;
}