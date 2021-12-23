#ifndef JSONTABLEVIEW_H
#define JSONTABLEVIEW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QDir>
#include <QAbstractListModel>
#include <QThread>

#include "qtableviewmodel.h"
#include "jsoninfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class JsonTableView; }
QT_END_NAMESPACE

class JsonTableView : public QMainWindow
{
    Q_OBJECT

public:
    JsonTableView(QWidget *parent = nullptr);
    ~JsonTableView();

    const QString jsonFilesPath = QDir::currentPath() + "/JsonFiles";

private:
    QThread watcherThread;
    Ui::JsonTableView *ui;
};
#endif // JSONTABLEVIEW_H
