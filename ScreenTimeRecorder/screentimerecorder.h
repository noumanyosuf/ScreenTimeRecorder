#ifndef SCREENTIMERECORDER_H
#define SCREENTIMERECORDER_H
#include <QObject>
#include <QMutex>
#include <QTimer>
#include "globalexport.h"

class ScreenTimeRecorderPrivate;

class  SCREEN_TIME_EXPORT ScreenTimeRecorder : public QObject
{
    Q_OBJECT
public:
    enum class  State { Stopped, Running, Paused, Resumed };

    static ScreenTimeRecorder* getInstance();

    State state() const;
    void setState(const State state);

    QStringList recordScreenList() const;
    void addRecordScreen(const QStringList screenList);
    void removeRecordScreen(const QStringList screenList);

    ~ScreenTimeRecorder();

public slots:
    void loadData();
    void saveData();

private slots:
    void appendScreenTime(const QString screen, const int time);

private:
    void onStateChanged();
    ScreenTimeRecorderPrivate*    mData;
    static ScreenTimeRecorder*   mInstance;
    static QMutex                mInstanceMutex;

    ScreenTimeRecorder();
    ScreenTimeRecorder(const ScreenTimeRecorder*)=delete;
};

#endif // SCREENTIMERECORDER_H
