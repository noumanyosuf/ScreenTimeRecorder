#include "screentimeviewer.h"
#include "pieview.h"
#include "jsondatahandler.h"
#include <QtWidgets>
#include <QHBoxLayout>

static const QString SERVICE_PATH = "../screentime_bin/release";
static const QString SERVICE_NAME = "screentimeservice.exe";
static const QColor colours[10]   = {QColor(255,0,0), QColor(0,255,0), QColor(0,0,255),
                  QColor(0,0,0), QColor(255,255,255),
                  QColor(0,128,64)};

ScreenTimeViewer::ScreenTimeViewer(QWidget *parent)
    : QWidget(parent),
      mDataHandler(new JsonDataHandler()),
      mServiceController(SERVICE_PATH+"/"+SERVICE_NAME)
{
    mDataHandler->setFilePath("D:/");
    qDebug()<<mServiceController.install(SERVICE_PATH+"/"+SERVICE_NAME);

    setupModel();
    setupViews();
    loadFile();
}

ScreenTimeViewer::~ScreenTimeViewer()
{
}

void ScreenTimeViewer::startRecording()
{
    qDebug()<<mServiceController.start();
}

void ScreenTimeViewer::stopRecording()
{
    qDebug()<<mServiceController.stop();
}

void ScreenTimeViewer::pauseRecording()
{
    qDebug()<<mServiceController.pause();
}

void ScreenTimeViewer::resumeRecording()
{
    qDebug()<<mServiceController.resume();
}

void ScreenTimeViewer::setupModel()
{
    model = new QStandardItemModel(8, 2, this);
    model->setHeaderData(0, Qt::Horizontal, tr("Screen"));
    model->setHeaderData(1, Qt::Horizontal, tr("Time Spend"));
}

void ScreenTimeViewer::setupViews()
{
    QSplitter *splitter = new QSplitter;
    QTableView *table = new QTableView;
    pieChart = new PieView;
    splitter->addWidget(table);
    splitter->addWidget(pieChart);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);

    table->setModel(model);
    pieChart->setModel(model);

    QItemSelectionModel *selectionModel = new QItemSelectionModel(model);
    table->setSelectionModel(selectionModel);
    pieChart->setSelectionModel(selectionModel);

    QHeaderView *headerView = table->horizontalHeader();
    headerView->setStretchLastSection(true);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(splitter);
    this->setLayout(layout);
}

void ScreenTimeViewer::loadFile()
{
    Data screenTimeData = mDataHandler->getData();

    model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
    int row = 0;
    DataItr itr(screenTimeData);

    while (itr.hasNext())
    {
        itr.next();

        qDebug()<<itr.key()<< " : "<<screenTimeData[itr.key()];
        model->insertRows(row, 1, QModelIndex());
        model->setData(model->index(row, 0, QModelIndex()),
                       itr.key());
        model->setData(model->index(row, 1, QModelIndex()),
                       screenTimeData[itr.key()]);
        model->setData(model->index(row, 0, QModelIndex()),
                       colours[row%10], Qt::DecorationRole);
        row++;
    }
}

