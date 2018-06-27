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
	//init();
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
	connect(this, SIGNAL(Result(const MyPair&)), this, SLOT(updateTableView(const MyPair&)),Qt::QueuedConnection);
	// ����CSS�ļ�
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
	//ocr(imgPath, name, num);
	//emit Result({ {name,num},index });
	freeSpace.release();
}

MainWindow::~MainWindow()
{
	delete ui;
	destroy();
}

void MainWindow::on_fileButton_clicked()
{
	pathList.clear(); // ���֮ǰ��·��
	QString path = QFileDialog::getExistingDirectory();
	if (path.length() == 0) {
		qDebug("No select file!");
	}
	else {
		qDebug("You select %s", path);
	}

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
		filter = qfo.suffix(); //��ȡ��׺��
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
	// ���ñ�ͷ
	model = new QStandardItemModel();
	model->setColumnCount(2);
	model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("��ҵ����"));
	model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("��ҵע���"));
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
	ui->tableView->setColumnWidth(0, 300);
	ui->tableView->setColumnWidth(1, 290);
	ui->tableView->horizontalHeader()->setHighlightSections(false);
	ui->tableView->setFrameShape(QFrame::NoFrame);
	//ui->tableView->setItemDelegate(new NoFocusFrameDelegate());

	// �����������ݲ��ɱ༭
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//ɾ��������
	//model->removeRows(0,model->rowCount());
}

void MainWindow::setTableView(const pair<std::string, std::string>& data, const int index)
{
	model->setItem(index, 0, new QStandardItem(QString::fromLocal8Bit(data.first.c_str())));
	//�����ַ���ɫ
	model->item(index, 0)->setForeground(QBrush(QColor(255, 0, 0)));
	//�����ַ�λ��
	model->item(index, 0)->setTextAlignment(Qt::AlignCenter);
	model->setItem(index, 1, new QStandardItem(QString::fromLocal8Bit(data.second.c_str())));
}

void MainWindow::updateTableView(const MyPair& p)
{
	QCoreApplication::processEvents();//������涳�� 
	dialog->setValue(count);//���ý������ĵ�ǰֵ
	pair<string, string> pair;
	pair.first = "Ѹ����ó���޹�˾";
	pair.second = "91310000717867461E";
	setTableView(pair, count++);
}

void MainWindow::on_checkButton_clicked()
{
	model->removeRows(0, model->rowCount());
	count = 0;

	if (pathList.size() <= 0) 
	{
		QMessageBox message(QMessageBox::NoIcon, "", QString::fromLocal8Bit("û��ѡ���κ�ͼƬ�ļ�����ʽ��֧��*.jpg��*.jpeg��*.png����"));
		message.setButtonText(1, QString::fromLocal8Bit("ȷ��"));
		message.setWindowIcon(QIcon(root + "/static/logo"));
		QPalette palette = message.palette();
		palette.setBrush(QPalette::Window,
			QBrush(QPixmap(root + "/static/dialogbg.png")));
		message.setPalette(palette);
		message.exec();
		return;
	}

	dialog = new QProgressDialog(this);
	dialog->setRange(0, 10000);
	//dialog->setLabelText(QString::fromLocal8Bit("ʶ�����"));
	dialog->setCancelButtonText(QString::fromLocal8Bit("ȡ��"));
	//dialog->setGeometry((900-600)/2, (600-200)/2, 600, 160);
	dialog->setWindowModality(Qt::WindowModal);//���Ի�������Ϊģ̬��  
	dialog->setFixedSize(600, 160);
	dialog->setAutoClose(true);
	QPushButton *cbtn = new QPushButton(this);
	cbtn->setStyleSheet("QPushButton{min-width:80px;min-height:30px;color:white} ");
	cbtn->setText(QString::fromLocal8Bit("ȡ��"));
	dialog->setCancelButton(cbtn);
	QPalette palette = dialog->palette();
	palette.setBrush(QPalette::Window,
		QBrush(QPixmap(root + "/static/dialogbg.png")));
	dialog->setPalette(palette);
	dialog->show();

	for (int i = 0; i<pathList.size(); ++i)
	{
		qDebug("%s",pathList[i]);
		string name, num;
		//QtConcurrent::run(this, &MainWindow::asyOcr, pathList[i], count++);
		if (dialog->wasCanceled())
		{
			delete dialog;
			break;
		}
	}

	/*��ʾ���ƽ���
	for (int i = 0; i <= 10000; i++) {
		MyPair pair;
		updateTableView(pair);
		//QCoreApplication::processEvents();//������涳��  
		if (dialog->wasCanceled())
		{
			delete dialog;
			break;
		}
	}*/
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

	pair<string, string> tp;
	tp.first = "Ѹ����ó���޹�˾";
	tp.second = "91310000717867461E";
	open_excel_and_add_result(tp);
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

