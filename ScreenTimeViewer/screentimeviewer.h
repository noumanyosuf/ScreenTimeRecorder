#ifndef SCREENTIMEVIEWER_H
#define SCREENTIMEVIEWER_H

#include <QWidget>
#include <idatahandler.h>
#include "qtservice.h"

class QAbstractItemModel;
class QAbstractItemView;

class ScreenTimeViewer : public QWidget
{
    Q_OBJECT

public:
    ScreenTimeViewer(QWidget *parent = nullptr);
    ~ScreenTimeViewer();

public slots:
    void startRecording();
    void stopRecording();
    void pauseRecording();
    void resumeRecording();

private:
    void setupModel();
    void setupViews();
    void loadFile();

    QScopedPointer<IDataHandler> mDataHandler;
    QAbstractItemModel *model   = nullptr;
    QAbstractItemView *pieChart = nullptr;
    QtServiceController mServiceController;
};
#endif // SCREENTIMEVIEWER_H
