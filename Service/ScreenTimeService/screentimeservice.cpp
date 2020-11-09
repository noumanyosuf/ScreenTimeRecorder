#include "screentimeservice.h"
#include "screentimerecorder.h"

static const QString SERVICE_NAME = "ScreenTimeService";

ScreenTimeService::ScreenTimeService(int argc, char **argv) : QtService<QCoreApplication>(argc,argv,SERVICE_NAME)
{
    try
    {
        //Set the service information
        setServiceDescription("Screen time service");
        setServiceFlags(QtServiceBase::CanBeSuspended);

        mScreenTimeRecorder = ScreenTimeRecorder::getInstance();
        mScreenTimeRecorder->addRecordScreen(QStringList()<<"google"<<"stackoverflow");
        mScreenTimeRecorder->loadData();
    }
    catch(...)
    {
        qCritical() << "An unknown error in the constructor";
    }
}

ScreenTimeService::~ScreenTimeService() {}

void ScreenTimeService::start()
{
    try
    {
        qDebug() << "Service started!";
        if(mScreenTimeRecorder)mScreenTimeRecorder->setState(ScreenTimeRecorder::State::Running);
    }
    catch(...)
    {
        qCritical() << "An unknown error in the start";
    }
}

void ScreenTimeService::pause()
{
    try
    {
        qDebug() << "Service paused!";
        if(mScreenTimeRecorder) mScreenTimeRecorder->setState(ScreenTimeRecorder::State::Paused);
    }
    catch(...)
    {
        qCritical() << "An unknown error in the pause";
    }
}

void ScreenTimeService::resume()
{
    try
    {
        qDebug() << "Service resumed!";
        if(mScreenTimeRecorder) mScreenTimeRecorder->setState(ScreenTimeRecorder::State::Resumed);
    }
    catch(...)
    {
        qCritical() << "An unknown error in the resume";
    }
}

void ScreenTimeService::stop()
{
    try
    {
        qDebug() << "Service stopped!";
        if(mScreenTimeRecorder) mScreenTimeRecorder->setState(ScreenTimeRecorder::State::Stopped);
    }
    catch(...)
    {
        qCritical() << "An unknown error in the stop";
    }
}
