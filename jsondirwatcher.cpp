#include "jsondirwatcher.h"

JsonDirWatcher::JsonDirWatcher(QString path)
{
    jsonFilesPath = path;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkJsonDir()));
    timer->start(timerPeriod);
}
void JsonDirWatcher::setPath(QString path)
{
    jsonFilesPath = path;
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
        getInfoFromFiles(newInfo);
    }
}
QTableViewModel JsonDirWatcher::getInfoFromFiles(QFileInfoList infoList)
{
    QFile jsonFile(jsonFilesPath);
    if(!jsonFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,"","Ошибка чтения файла "+QFileInfo(jsonFile).fileName());
        return NULL;
    }
    QByteArray jsonFileData = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError parseError;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(jsonFileData,&parseError));



    if(parseError.error != QJsonParseError::NoError)
    {
        QString err = QString("Error at"+QString.fromInt(parseError.offset)+" : "+parseError.errorString());
    }

    QJsonObject jsonObj = jsonDocument.object();
    QJsonArray jsonArray;
    jsonArray = jsonObj["list"].toArray();
    foreach(QJsonValue val, jsonArray)
    {
        QJsonObject obj = val.toObject();
        int t = obj.value(0).toInt();

        QString tt = obj.value(1).toString();
        bool ttt = obj.value(2).toBool();
        double tttt = obj.value(3).toDouble();
        QString test = "0";




            QList<JsonInfo> *values = new QList<JsonInfo>;
            values->append(JsonInfo(1,"test",0,1.2));


            QTableViewModel *model = new QTableViewModel();
            model->populate(values);
            this->ui->tableView->setModel(model);
    }
}


