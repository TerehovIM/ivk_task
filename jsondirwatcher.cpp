#include "jsondirwatcher.h"

JsonDirWatcher::JsonDirWatcher(QString path)
{
    jsonFilesPath = path;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkJsonDir()));
    timer->start(timerPeriod);
}

void JsonDirWatcher::checkJsonDir()
{
    QFileInfoList buffer = lastInfo;
    QFileInfoList newInfo = QDir(jsonFilesPath).entryInfoList(QDir::Files|QDir::NoDotAndDotDot|QDir::NoSymLinks|QDir::Readable, QDir::Time);
    QMutableListIterator<QFileInfo> infoIt(newInfo);
    while(infoIt.hasNext())
    {
        if(infoIt.next().suffix() != "json")
            infoIt.remove();
        else
        {
            for(int n = 0; n < buffer.count(); n++)
            {
                if(infoIt.value().absoluteFilePath() == buffer.at(n).absoluteFilePath() && infoIt.value().lastModified() == buffer.at(n).lastModified())
                {
                    buffer.removeAt(n);
                    break;
                }
            }
        }
    }
    if(!buffer.isEmpty()||lastInfo.count() < newInfo.count())
    {
        lastInfo.clear();
        lastInfo = newInfo;
        emit jsonReaded(readInfoFromFiles(newInfo));
        return;
    }
}

void JsonDirWatcher::setPath(QString path)
{
    jsonFilesPath = path;
}

QList<JsonInfo> JsonDirWatcher::readInfoFromFiles(QFileInfoList infoList)
{
    QList<JsonInfo> buffer;
    foreach(QFileInfo fileInfo, infoList)
    {
        QFile jsonFile(fileInfo.absoluteFilePath());
        if(!jsonFile.open(QIODevice::ReadOnly))
        {
            emit jsonError("Error while opening file " + fileInfo.absoluteFilePath());
            continue;
        }
        QByteArray jsonFileData = jsonFile.readAll();
        jsonFile.close();

        QJsonParseError parseError;
        QJsonDocument jsonDocument(QJsonDocument::fromJson(jsonFileData,&parseError));
        if(parseError.error != QJsonParseError::NoError)
        {
            emit jsonError("Error while reading file " + fileInfo.absoluteFilePath());
            continue;
        }

        QJsonObject jsonObj = jsonDocument.object();
        QJsonArray jsonArray;
        jsonArray = jsonObj["list"].toArray();
        for(int n = 0; n < jsonArray.count(); n++)
        {
            QJsonObject obj = jsonArray[n].toObject();
            JsonInfo jsonInf(obj.take("id").toInt(),
                             obj.take("name").toString(),
                             obj.take("status").toBool(),
                             obj.take("price").toDouble());
            buffer.append(jsonInf);
        }
    }
    return buffer;
}
