#include "screentimerecorder.h"
#include "screentimemonitor.h"
#include "jsondatahandler.h"
#include "idatahandler.h"
#include <QDebug>

static const int Record_Time_Out = 5000;

ScreenTimeRecorder* ScreenTimeRecorder::mInstance = nullptr;
QMutex ScreenTimeRecorder::mInstanceMutex;

class ScreenTimeRecorderPrivate
{
public:
    ScreenTimeRecorderPrivate():
        mDataUpdated(false),
        mState(ScreenTimeRecorder::State::Paused),
        mDataHandler(new JsonDataHandler()){}

    bool                         mDataUpdated;
    ScreenTimeRecorder::State    mState;
    QTimer*                      mRecordTimer;
    QScopedPointer<IDataHandler> mDataHandler;
    Data                         mWinScreenTime;
    ScreenTimeMonitor            mScreenMonitor;
};

ScreenTimeRecorder::ScreenTimeRecorder():
    mData(new ScreenTimeRecorderPrivate())
{
    mData->mRecordTimer = new QTimer(this);
    mData->mDataHandler->setFilePath("D:/");
    loadData();
}

ScreenTimeRecorder *ScreenTimeRecorder::getInstance()
{
    QMutexLocker locker(&mInstanceMutex);
    if (!mInstance)
        mInstance = new ScreenTimeRecorder();
    locker.unlock();
    return mInstance;
}

ScreenTimeRecorder::State ScreenTimeRecorder::state() const
{
    return mData->mState;
}

void ScreenTimeRecorder::setState(const ScreenTimeRecorder::State state)
{
    if(state == mData->mState) return;
    mData->mState = state;
    onStateChanged();
}

void ScreenTimeRecorder::addRecordScreen(const QStringList screenList)
{
    QStringList screenFilter;
    foreach(const QString screen,screenList)
    {
        if(mData->mWinScreenTime.find(screen) != mData->mWinScreenTime.end()) continue;
        mData->mWinScreenTime[screen] = 0;
        screenFilter.append(screen);
    }
    mData->mScreenMonitor.addScreenFilter(screenFilter);
}

void ScreenTimeRecorder::removeRecordScreen(const QStringList screenList)
{
    foreach(const QString screen,screenList)
    {
        if(mData->mWinScreenTime.find(screen) != mData->mWinScreenTime.end()) continue;
        mData->mWinScreenTime.remove(screen);
    }
}

ScreenTimeRecorder::~ScreenTimeRecorder()
{
    delete mData;
}

QStringList ScreenTimeRecorder::recordScreenList() const
{
    DataItr itr(mData->mWinScreenTime);
    QStringList screenList;
    while (itr.hasNext())
    {
        itr.next();
        screenList.append(itr.key());
    }
    return screenList;
}

void ScreenTimeRecorder::onStateChanged()
{

    switch(mData->mState)
    {
    case State::Running:
    {
        connect(&mData->mScreenMonitor,&ScreenTimeMonitor::screenChanged,this,&ScreenTimeRecorder::appendScreenTime);
        connect(mData->mRecordTimer, &QTimer::timeout, this, &ScreenTimeRecorder::saveData);

        mData->mScreenMonitor.setState(ScreenTimeMonitor::State::Running);
        mData->mScreenMonitor.start();
        mData->mRecordTimer->start(Record_Time_Out);
        break;
    }
    case State::Stopped:
    {
        mData->mRecordTimer->stop();
        mData->mScreenMonitor.setState(ScreenTimeMonitor::State::Stopped);

        disconnect(&mData->mScreenMonitor,&ScreenTimeMonitor::screenChanged,this,&ScreenTimeRecorder::appendScreenTime);
        disconnect(mData->mRecordTimer, &QTimer::timeout, this, &ScreenTimeRecorder::saveData);
        break;
    }
    case State::Paused:
    {
        disconnect(mData->mRecordTimer, &QTimer::timeout, this, &ScreenTimeRecorder::saveData);

        mData->mRecordTimer->stop();
        mData->mScreenMonitor.setState(ScreenTimeMonitor::State::Paused);
        break;
    }
    case State::Resumed:
    {
        connect(mData->mRecordTimer, &QTimer::timeout, this, &ScreenTimeRecorder::saveData);

        mData->mRecordTimer->start(Record_Time_Out);
        mData->mScreenMonitor.setState(ScreenTimeMonitor::State::Resumed);
        break;
    }
    default:    break;
    }
}

void ScreenTimeRecorder::appendScreenTime(const QString screen,const int time)
{
    if(mData->mWinScreenTime.find(screen) == mData->mWinScreenTime.end()) return;
    mData->mWinScreenTime[screen] += time;
    mData->mDataUpdated = true;
    qDebug()<<screen<< " : "<<time << mData->mWinScreenTime[screen];
}

void ScreenTimeRecorder::loadData()
{
    mData->mWinScreenTime = mData->mDataHandler->getData();
    mData->mScreenMonitor.addScreenFilter(this->recordScreenList());
}

void ScreenTimeRecorder::saveData()
{
    if(!mData->mDataUpdated) return;

    qDebug()<<"saveData";
    const Data toSave = mData->mWinScreenTime;
    mData->mDataHandler->saveData(toSave);
    mData->mDataUpdated = false;
}
