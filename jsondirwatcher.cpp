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
        emit jsonReaded(readInfoFromFiles(newInfo));
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
        for(int n = 0; n < jsonArray.count(); n++)
        {
            QJsonObject obj = jsonArray[n].toObject();
            //obj.take(QString::number(0)).toInt();
            JsonInfo jsonInf(obj.take("id").toInt(),
                             obj.take("name").toString(),
                             obj.take("status").toBool(),
                             obj.take("price").toDouble());
            buffer.append(jsonInf);
        }
    }
    return buffer;
}
