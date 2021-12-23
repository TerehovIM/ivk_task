#ifndef JSONDIRWATCHER_H
#define JSONDIRWATCHER_H

#include <QObject>
#include <QTimer>
#include <QFileInfo>
#include <QFile>
#include <QDir>

class JsonDirWatcher : public QObject
{
    Q_OBJECT
public:
    JsonDirWatcher(QString path);
private:
    void checkJsonDir(QString path);
    unsigned int timerPeriod = 500;
    QString jsonFilesPath;
    QFileInfoList lastInfo;

};

#endif // JSONDIRWATCHER_H
