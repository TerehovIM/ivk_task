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
    QTimer *timer;
    int timerPeriod = 100;
    QString jsonFilesPath;
    QFileInfoList lastInfo;
private slots:
    void checkJsonDir();

};

#endif // JSONDIRWATCHER_H
