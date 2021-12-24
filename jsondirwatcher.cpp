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
            for(int n = 0; n < lastInfo.count(); n++)
            {
                if(infoIt.value() == lastInfo.at(n))
                {
                    lastInfo.removeAt(n);
                    infoIt.remove();
                    break;
                }
            }
        }
    }
    foreach(QFileInfo toAdd, newInfo)
    {
        //addToModel(newInfo)
        buffer.
    }

    //removeFromMode(lastInfo)
    //lastInfo = getModelList()

    if(newInfo!=lastInfo)
    {
        lastInfo.clear();
        lastInfo = newInfo;
    }
}
