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
    QFileInfoList newInfo = QDir(jsonFilesPath).entryInfoList(QDir::Files|QDir::NoDotAndDotDot|QDir::NoSymLinks|QDir::Readable, QDir::Time);
    QMutableListIterator<QFileInfo> infoIt(newInfo);
    while(infoIt.hasNext())
    {
        if(infoIt.next().suffix() != "json")
            infoIt.remove();
    }
    if(newInfo!=lastInfo)
    {
        lastInfo.clear();
        lastInfo = newInfo;
        readInfoFromFiles(newInfo);
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
            //QMessageBox::warning(this,"",QString("Ошибка чтения файла "+fileInfo.absoluteFilePath()));
            return buffer;
        }
        QByteArray jsonFileData = jsonFile.readAll();
        jsonFile.close();

        QJsonParseError parseError;
        QJsonDocument jsonDocument(QJsonDocument::fromJson(jsonFileData,&parseError));
        if(parseError.error != QJsonParseError::NoError)
        {
            //QMessageBox::warning(this,"",QString("Error at"+QString.fromInt(parseError.offset)+" : "+parseError.errorString()));
            return buffer;
        }

        QJsonObject jsonObj = jsonDocument.object();
        QJsonArray jsonArray;
        jsonArray = jsonObj["list"].toArray();
        foreach(QJsonValue val, jsonArray)
        {
            QJsonObject obj = val.toObject();
            JsonInfo jsonInf(obj.value(QString::number(0)).toInt(),
                             obj.value(QString::number(1)).toString(),
                             obj.value(QString::number(2)).toBool(),
                             obj.value(QString::number(3)).toDouble());
            buffer.append(jsonInf);
        }
    }
    return buffer;
}
