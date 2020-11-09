#include "jsondatahandler.h"
#include <QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>

static const QString JSON_FILENAME   = "screentimeanalyser.json";
static const QString JSON_NAME       = "Info";
static const QString JSON_SITE       = "Site";
static const QString JSON_SCREENTIME = "ScreenTime";

JsonDataHandler::JsonDataHandler(){}

JsonDataHandler::~JsonDataHandler()
{
    mFile.close();
}

void JsonDataHandler::setFilePath(const QString &path)
{
    mFilePath = path;
}

bool JsonDataHandler::saveData(const Data& data)
{
    openFile();
    QJsonObject info;
    writeToJsonObject(info,data);
    mFile.write(QJsonDocument(info).toJson());
    return true;
}

Data JsonDataHandler::getData()
{
    openFile();
    const QByteArray info = mFile.readAll();
    return readFromJsonObject(QJsonDocument::fromJson(info).object());
}

void JsonDataHandler::writeToJsonObject(QJsonObject &json, const Data& data)
{
    QJsonArray infoList;
    DataItr itr(data);
    while (itr.hasNext())
    {
        itr.next();
        QJsonObject jsonData;
        jsonData[JSON_SITE]       = itr.key();
        jsonData[JSON_SCREENTIME] = data[itr.key()];
        infoList.append(jsonData);
      }
    json[JSON_NAME] = infoList;
}

void JsonDataHandler::openFile()
{
    if(!mFile.isOpen())
    {
        mFile.setFileName(mFilePath+JSON_FILENAME);
        mFile.open(QIODevice::ReadWrite);
    }
    mFile.seek(0);
}

Data JsonDataHandler::readFromJsonObject(const QJsonObject &json) const
{
    Data data;
    const QJsonArray infoList = json[JSON_NAME].toArray();
    foreach(const QJsonValue &jObject, infoList)
    {
        const QString siteName = jObject[JSON_SITE].toString();
        const int screenTime   = jObject[JSON_SCREENTIME].toInt();
        data[siteName]         = screenTime;
    }
    return data;
}
