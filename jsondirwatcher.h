#ifndef JSONDIRWATCHER_H
#define JSONDIRWATCHER_H

#include <QObject>
#include <QTimer>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

#include "qtableviewmodel.h"

class JsonDirWatcher : public QObject
{
    Q_OBJECT
public:
    JsonDirWatcher(QString path);
    void setPath(QString path);
private:
    QTimer *timer;
    int timerPeriod = 100;
    QString jsonFilesPath;
    QFileInfoList lastInfo;
    QTableViewModel getInfoFromFiles(QFileInfoList infoList);
private slots:
    void checkJsonDir();

};

#endif // JSONDIRWATCHER_H
