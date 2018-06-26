#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include <qstandarditemmodel.h>
#include "excel.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),freeSpace(1)
{
	init();
	qRegisterMetaType<MyPair>("MyPair");

	QString root = QCoreApplication::applicationDirPath();

	this->setAutoFillBackground(false);
	QPalette palette = this->palette();
	palette.setBrush(QPalette::Window,
		QBrush(QPixmap(root + "/static/background.png").scaled(// 缩放背景图.
			this->size(),
			Qt::IgnoreAspectRatio,
			Qt::SmoothTransformation)));             // 使用平滑的缩放方式
	this->setPalette(palette);

	ui->setupUi(this);
	
	m_mainLayout = new QVBoxLayout(this);
	m_toplayout = new QHBoxLayout(this);

	m_titleWidget = new TitleBar(this);
	m_mainLayout->addWidget(m_titleWidget, 5, Qt::AlignTop);
	//m_mainLayout->addLayout(m_toplayout);

	setLayout(m_mainLayout);
	setFixedSize(700, 500);
	setWindowFlags(Qt::FramelessWindowHint);

	connect(m_titleWidget, SIGNAL(customShowMinWindow()), this, SLOT(showMinimized()));
	connect(m_titleWidget, SIGNAL(customCloseWindow()), this, SLOT(close()));
	connect(this, SIGNAL(Result(const MyPair&)), this, SLOT(updateTableView(const MyPair&)),Qt::QueuedConnection);
	// 加载CSS文件
	//QString strPath = QCoreApplication::applicationDirPath();
	QString strCssFile = root + "/static/default.css";
	QFile fCss(strCssFile);
	if (!fCss.open(QFile::ReadOnly))
	{
		qDebug("css File %s load false", strCssFile);
		return;
	}
	QString strCssContent(fCss.readAll());
	setStyleSheet(strCssContent);
	fCss.close();

	initTableView();
}
void MainWindow::asyOcr(const std::string imgPath, const int index)
{
	freeSpace.acquire();
	string name, num;
	ocr(imgPath, name, num);
	emit Result({ {name,num},index });
	freeSpace.release();
}

MainWindow::~MainWindow()
{
	delete ui;
	destroy();
}

void MainWindow::on_fileButton_clicked()
{
	pathList.clear(); // 清空之前的路径
	QString path = QFileDialog::getExistingDirectory();
	if (path.length() == 0) {
		qDebug("No select file!");
	}
	else {
		qDebug("You select %s", path);
	}
	int count = 0;

	QStringList files = getFileNames(path);
	for (QString str : files) {
		qDebug() << str;
		pathList.push_back(string(str.toLocal8Bit()));
	}

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
	ui->tableView->setColumnWidth(0, 210);
	ui->tableView->setColumnWidth(1, 210);
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
	model->setItem(index, 0, new QStandardItem(QString::fromLocal8Bit(data.first.c_str())));
	//设置字符颜色
	model->item(index, 0)->setForeground(QBrush(QColor(255, 0, 0)));
	//设置字符位置
	model->item(index, 0)->setTextAlignment(Qt::AlignCenter);
	model->setItem(index, 1, new QStandardItem(QString::fromLocal8Bit(data.second.c_str())));
}

void MainWindow::updateTableView(const MyPair& p)
{
	setTableView(p.first,p.second);
}
void MainWindow::on_checkButton_clicked()
{
	
	model->removeRows(0, model->rowCount());
	int count = 0;
	
	for (int i = 0; i<20; ++i)
	{
		qDebug("%s",pathList[i]);
		string name, num;
		QtConcurrent::run(this, &MainWindow::asyOcr, pathList[i], count++);

	}
}

void MainWindow::on_excelButton_clicked()
{
	QString fileName;
	fileName = QFileDialog::getSaveFileName(this,
		tr("Open Config"), "", tr("Config Files (*.xlsx)"));
	if (!fileName.isNull())
	{
		qDebug() << fileName;
	}
	else {
		qDebug() << "No select file!";
	}
	create_result_excel();

	vector<string> data;
	data.push_back("迅销商贸有限公司");
	data.push_back("91310000717867461E");
	open_excel_and_add_result(data);
	copy_and_save_file(fileName.toStdWString());
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

