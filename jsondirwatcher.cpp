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
    }
}
