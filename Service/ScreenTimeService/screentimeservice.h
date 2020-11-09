#ifndef MYSERVICE_H
#define MYSERVICE_H

#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include "qtservice.h"

class ScreenTimeRecorder;

class ScreenTimeService : public QtService<QCoreApplication>
{
public:
    /**
     * @brief The constructor
     * @param argc
     * @param argv
     */
    ScreenTimeService(int argc, char **argv);

    /**
     * @brief The deconstructor
     */
    ~ScreenTimeService();

    /**
     * @brief Start the service
     */
    void start();

    /**
     * @brief Pause the service
     */
    void pause();

    /**
     * @brief Resume the service
     */
    void resume();

    /**
     * @brief Stop the service
     */
    void stop();

private:
    ScreenTimeRecorder *mScreenTimeRecorder;
};

#endif // MYSERVICE_H
