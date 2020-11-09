#ifndef IDATAHANDLER_H
#define IDATAHANDLER_H
#include <QMap>
#include "globalexport.h"

typedef QMap<QString,int> Data;
typedef QMapIterator<QString, int> DataItr;

class SCREEN_TIME_EXPORT IDataHandler
{
public:
    virtual void setFilePath(const QString&) = 0;
    virtual bool saveData(const Data&) = 0;
    virtual Data getData() = 0;
};

#endif // IDATAHANDLER_H
