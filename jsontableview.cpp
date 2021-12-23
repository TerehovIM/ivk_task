#include "jsontableview.h"
#include "jsondirwatcher.h"
#include "ui_jsontableview.h"

#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>

JsonTableView::JsonTableView(QWidget *parent) : QMainWindow(parent), ui(new Ui::JsonTableView)
{
    QString test = jsonFilesPath;
    ui->setupUi(this);

    JsonDirWatcher *watcher = new JsonDirWatcher(jsonFilesPath);


    QList<JsonInfo> *values = new QList<JsonInfo>;
    values->append(JsonInfo(1,"test",0,1.2));


    QTableViewModel *model = new QTableViewModel();
    model->populate(values);
    this->ui->tableView->setModel(model);

}

JsonTableView::~JsonTableView()
{
    delete ui;
}

