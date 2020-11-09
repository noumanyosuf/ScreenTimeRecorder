#include <QCoreApplication>
#include "screentimeservice.h"

int main(int argc, char *argv[])
{
    ScreenTimeService service(argc, argv);
    qDebug()<<argc<< " : " <<argv[0] << " : "<<argv[1];
    return service.exec();

}
