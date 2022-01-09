#ifndef JSONDIRWATCHER_H
#define JSONDIRWATCHER_H

#include "jsoninfo.h"
#include <QObject>
#include <QTimer>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

class JsonDirWatcher : public QObject
{
    Q_OBJECT
signals:
    void jsonReaded(QList<JsonInfo>);
    void jsonError(QString);
public:
    JsonDirWatcher(QString path);
    void setPath(QString path);
private:
    QTimer *timer;
    int timerPeriod = 100;
    QString jsonFilesPath;
    QFileInfoList lastInfo;
    QList<JsonInfo> readInfoFromFiles(QFileInfoList infoList);
private slots:
    void checkJsonDir();

};

#endif // JSONDIRWATCHER_H
