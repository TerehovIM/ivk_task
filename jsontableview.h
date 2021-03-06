#ifndef JSONTABLEVIEW_H
#define JSONTABLEVIEW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QDir>
#include <QAbstractListModel>
#include <QThread>

#include "jsondirwatcher.h"
#include "ui_jsontableview.h"
#include "qtableviewmodel.h"
#include "jsoninfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class JsonTableView; }
QT_END_NAMESPACE

class JsonTableView : public QMainWindow
{
    Q_OBJECT
    QThread watcherThread;
public:
    JsonTableView(QWidget *parent = nullptr);
    ~JsonTableView();
public slots:
    void jsonInfoChanged(QList<JsonInfo> inf);
    void jsonErrorShow(QString errMessage);

private slots:
    void on_lineEdit_editingFinished();
    void on_pushButton_clicked();

private:
    JsonDirWatcher *watcher;
    QTableViewModel *model;
    QString jsonFilesPath = QDir::currentPath() + "/JsonFiles";
    Ui::JsonTableView *ui;    
};
#endif // JSONTABLEVIEW_H
