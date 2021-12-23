#include "jsondirwatcher.h"

JsonDirWatcher::JsonDirWatcher(QString path)
{
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(checkJsonDir(path)));
    timer->start(timerPeriod);

}
void JsonDirWatcher::checkJsonDir(QString path)
{
    QFileInfoList newInfo = QDir(path).entryInfoList(QDir::Files|QDir::NoDotAndDotDot|QDir::NoSymLinks|QDir::Readable, QDir::Time);
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
