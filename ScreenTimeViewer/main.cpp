#include "screentimeviewer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScreenTimeViewer w;
    w.show();
    return a.exec();

//        ScreenTimeService service(argc, argv);
//        qDebug()<<argc<< " : " <<argv[0] << " : "<<argv[1];
//        return service.exec();
}
