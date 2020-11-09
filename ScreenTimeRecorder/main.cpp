#include <QCoreApplication>
#include "screentimerecorder.h"
#include "qdebug.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    ScreenTimeRecorder *sr = ScreenTimeRecorder::getInstance();
    sr->addRecordScreen(QStringList()<<"google"<<"stackoverflow");
    sr->setState(ScreenTimeRecorder::State::Running);


//    JsonDataHandler j;
//     Data d = j.getData();
//     qWarning()<<"    "<<d["google"];
//    {
//        d["google"] = 50;
////        d["utube"] = 500;
////        d["stackoverflow"] = 10;
//        j.saveData(d);
//    }
//    {
//        Data ss = j.getData();
//        qWarning()<<ss.size()<<"++++++++++++++++++++++++++++";

//        DataItr i(ss);
//        while (i.hasNext()) {
//            i.next();
//            qWarning() << i.key() << ": " << i.value() << Qt::endl;
//        }
//    }

//    {
//        d["google"] = 100000;
//        j.saveData(d);
//    }
//    {
//        Data ss = j.getData();
//        qWarning()<<ss.size()<<"--------------------------";

//        DataItr i(ss);
//        while (i.hasNext()) {
//            i.next();
//            qWarning() << i.key() << ": " << i.value() << Qt::endl;
//        }
//    }

    return a.exec();
}
