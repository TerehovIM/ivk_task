#include "jsontableview.h"
#include "jsondirwatcher.h"
#include "ui_jsontableview.h"

#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>

JsonTableView::JsonTableView(QWidget *parent) : QMainWindow(parent), ui(new Ui::JsonTableView)
{
    ui->setupUi(this);
    ui->lineEdit->setText(jsonFilesPath);
    ui->lineEdit->clearFocus();

    watcher = new JsonDirWatcher(jsonFilesPath);
    watcher->moveToThread(&watcherThread);
    watcherThread.start();

    model = new QTableViewModel();
    this->ui->tableView->setModel(model);
    connect(watcher, SIGNAL(jsonReaded(QList<JsonInfo>)), this, SLOT(jsonInfoChanged(jsonReaded(QList<JsonInfo>))));
}

void JsonTableView::jsonInfoChanged(QList<JsonInfo> inf)
{
    model->populate(&inf);
}

JsonTableView::~JsonTableView()
{
    watcherThread.quit();
    watcherThread.wait();
    delete ui;
}

void JsonTableView::on_lineEdit_editingFinished()
{
    QString newPath = ui->lineEdit->text();
    if(QFileInfo(newPath).isDir()&&QDir(newPath).exists())
    {
        jsonFilesPath = newPath;
        watcher->setPath(jsonFilesPath);
    }
    else
        ui->lineEdit->setText(jsonFilesPath);
}

void JsonTableView::on_pushButton_clicked()
{
    ui->lineEdit->clearFocus();
}

