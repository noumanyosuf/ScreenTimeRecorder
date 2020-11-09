#include "screentimemonitor.h"
#include <QtDebug>
#include <QMutexLocker>
#include <windows.h>

ScreenTimeMonitor::ScreenTimeMonitor(QThread *parent) : QThread(parent),
    mState(State::Paused){}

void ScreenTimeMonitor::setState(const ScreenTimeMonitor::State state)
{
    if(state == mState) return;
    QMutexLocker locker(&mStateMutex);
    mState = state;
    locker.unlock();
    onStateChanged();
}

ScreenTimeMonitor::State ScreenTimeMonitor::state() const
{
    return mState;
}

void ScreenTimeMonitor::addScreenFilter(const QStringList screenFilter)
{
    QMutexLocker locker(&mFilterMutex);
    mScreenFilter.append(screenFilter);
}

void ScreenTimeMonitor::removeScreenFilter(const QStringList screenFilter)
{
    foreach(const QString filter,screenFilter)
    {
        if(!mScreenFilter.contains(filter)) continue;
        mScreenFilter.removeOne(filter);
    }
}

QStringList ScreenTimeMonitor::screenFilter() const
{
    return mScreenFilter;
}

void ScreenTimeMonitor::run()
{
    qDebug()<<"Started..";
    QMutexLocker stateLocker(&mStateMutex);
    stateLocker.unlock();

    QString previousOpenedScreen;
    QString currentScreen;
    bool isScreenSwitched = false;
    QString switchedScreen;

    mState = State::Running;
    mScreenActiveTimer.start();

    while(State::Stopped != mState)
    {
        isScreenSwitched = false;
        stateLocker.relock();
        if(State::Paused == mState) mStateWaitCond.wait(&mStateMutex); //check for thread pause
        stateLocker.unlock();

        currentScreen = currentScreenTitle();

        if(previousOpenedScreen != currentScreen)
        {
            previousOpenedScreen = currentScreen;
            if(previousOpenedScreen.isEmpty()) isScreenSwitched=true;
            else switchedScreen = previousOpenedScreen;
        }

        if(isScreenSwitched)
        {
            const auto filterName = filterEquivalentNames(switchedScreen);
            if(!filterName.isEmpty())
            {
                const auto elapsedTime = mScreenActiveTimer.elapsed()*0.001;
                foreach(const auto filter,filterName)
                emit screenChanged(filter,elapsedTime);
            }
            mScreenActiveTimer.restart();
        }
    }
    qDebug()<<"Thread exit.";
}

void ScreenTimeMonitor::onStateChanged()
{
    switch(mState)
    {
    case State::Resumed: mState = State::Running; mStateWaitCond.wakeAll();
    default: break;
    }
}

QString ScreenTimeMonitor::currentScreenTitle() const
{
    char wnd_title[256];
    HWND hwnd=GetForegroundWindow(); // currently active window handle
    GetWindowText(hwnd, (LPWSTR) wnd_title, 254);
    return QString::fromWCharArray((const wchar_t *)wnd_title); //current window title;
}

QStringList ScreenTimeMonitor::filterEquivalentNames(const QString screen)
{
    QStringList filterNames;
    QString screenSimplyfied = screen;
    screenSimplyfied = screenSimplyfied.remove(QRegExp("\\s")).toLower();
    QString filterSimplyfied;

    QMutexLocker filterlocker(&mFilterMutex);
    foreach(const QString filter,mScreenFilter)
    {
        filterSimplyfied = filter;
        filterSimplyfied = filterSimplyfied.remove(QRegExp("\\s")).toLower();
        if(screenSimplyfied.indexOf(filterSimplyfied) != -1) filterNames.append(filter);
    }
    return filterNames;
}
