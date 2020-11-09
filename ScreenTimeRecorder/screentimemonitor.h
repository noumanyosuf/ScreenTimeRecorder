#ifndef SCREENTIMELISTENER_H
#define SCREENTIMELISTENER_H

#include <QObject>
#include <QThread>
#include <QElapsedTimer>
#include <QMutex>
#include <QWaitCondition>

class ScreenTimeMonitor : public QThread
{
    Q_OBJECT
public:
    enum class  State { Stopped, Running, Paused, Resumed };

    explicit ScreenTimeMonitor(QThread *parent = nullptr);
    State state() const;
    void setState(const State state);
    QStringList screenFilter() const;
    void addScreenFilter(const QStringList screenFilter);
    void removeScreenFilter(const QStringList screenFilter);

protected:
    void run();

signals:
    void screenChanged(QString,int);

private:
    QString currentScreenTitle() const;
    QStringList filterEquivalentNames(const QString screen);
    void onStateChanged();

    State                        mState;
    QMutex                       mFilterMutex;
    QMutex                       mStateMutex;
    QWaitCondition               mStateWaitCond;
    QElapsedTimer                mScreenActiveTimer;
    QStringList                  mScreenFilter;
};

#endif // SCREENTIMELISTENER_H
