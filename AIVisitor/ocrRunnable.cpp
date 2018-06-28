#include "ocrRunnable.h"

QSemaphore OCRRunnable::numLimitSingal(THREAD_COUNT);
int OCRRunnable::listCount = 0;
void OCRRunnable::run()
{
	isRunning = true;
	//freeSpace.acquire();
	//if (isToStop)
	//{
	//	freeSpace.release();
	//	isRunning = false;
	//	numLimitSingal.release();
	//	return;
	//}
	string name, num;
	ocr(imgPath, name, num);
	QString str = QString::fromStdString(name);
	QString str2 = QString::fromStdString(num);

	if ((name.length() > 1 || num.length() > 1) && !isToStop)
	{
		emit Result({ {name,num},listCount++ });
	}
	emit DoneOne();
	//freeSpace.release();
	isRunning = false;
	numLimitSingal.release();
}


void StartRunnable::run()
{
	isRunning = true;
	qDebug() << pathList->size();
	if (isToStop)
		return;
	OCRRunnable::listCount = 0;
	for (int i = 0; i<pathList->size(); ++i)
	{
		int index = allocateThreadSpace();
		if (isToStop)
		{
			return;
		}
		qDebug() << index;
		if (index >= 0)
		{
			threadList[index]->isRunning = true;
			threadList[index]->imgPath = (*pathList)[i];
			QThreadPool::globalInstance()->start(threadList[index]);
		}
	}
	isRunning = false;
}

void StartRunnable::setPathList(vector<string>* paths)
{
	pathList = paths;
}

void StartRunnable::setThreadList(OCRRunnable** ocrRunnables)
{
	threadList = ocrRunnables;
}

int StartRunnable::allocateThreadSpace()
{
	OCRRunnable::numLimitSingal.acquire();
	int index = -1;
	for (int i = 0; i < THREAD_COUNT; ++i)
	{
		if (!threadList[i]->isRunning)
		{
			index = i;
			break;
		}
	}

	return index;
}
bool StartRunnable::clear()
{
	if (isRunning)
	{
		isToStop = true;
		setIsStop(true);
		QThreadPool::globalInstance()->cancel(this);
		for (int i = 0; i < THREAD_COUNT; ++i)
		{
			threadList[i]->isToStop = true;
			QThreadPool::globalInstance()->cancel(this);
			//threadList[i]->isRunning = false;
		}
		QThreadPool::globalInstance()->clear();
		return QThreadPool::globalInstance()->waitForDone();
	}
}
void StartRunnable::reset()
{
	isToStop = false;
	setIsStop(false);
	for (int i = 0; i < THREAD_COUNT; ++i)
	{
		threadList[i]->isToStop = false;
	}
}
