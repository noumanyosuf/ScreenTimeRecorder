#ifndef JSONDATAHANDLER_H
#define JSONDATAHANDLER_H

#include <QFile>
#include "idatahandler.h"
#include "globalexport.h"

class SCREEN_TIME_EXPORT JsonDataHandler : public IDataHandler
{
public:
    JsonDataHandler();
    ~JsonDataHandler();
    void setFilePath(const QString& path) override;
    bool saveData(const Data& data) override;
    Data getData() override;

private:
    Data readFromJsonObject(const QJsonObject &json) const;
    void writeToJsonObject(QJsonObject &json,const Data& data);
    void openFile();

    QString mFilePath;
    QFile mFile;
};

#endif // JSONDATAHANDLER_H
