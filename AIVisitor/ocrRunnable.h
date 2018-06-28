#pragma once
#include <QtWidgets/QWidget>
#include <QRunnable> 
#include <iostream>
#include <QDebug>
#include <QSemaphore>
#include <OCRDll.h>
#include <qthreadpool.h>

#define THREAD_COUNT 5
using namespace std;
typedef std::pair<std::pair<std::string, std::string>, int> MyPair;

class OCRRunnable : public QObject, public QRunnable
{
	Q_OBJECT
public:
	OCRRunnable():isRunning(false), isToStop(false)
	{
		this->setAutoDelete(false);
	}
	// 自定义信号
signals:
	void Result(const MyPair&);
	void DoneOne();
public:
	bool isToStop;
	bool isRunning;
	void run();
	static int listCount;
	string imgPath;
	static QSemaphore freeSpace;
	static QSemaphore numLimitSingal;
};

class StartRunnable : public QObject, public QRunnable
{
	Q_OBJECT
public:
	StartRunnable() :isRunning(false),isToStop(false)
	{
		this->setAutoDelete(false);
	}

private:
	vector<string>* pathList;
	OCRRunnable** threadList;
	int allocateThreadSpace();
	
public:
	void run();
	bool isRunning;
	bool isToStop;
	static QSemaphore freeSpace;
	static QSemaphore numLimitSingal;
	void setPathList(vector<string>*);
	void setThreadList(OCRRunnable**);
	bool clear();
	void reset();
};