#include "jsontableview.h"

JsonTableView::JsonTableView(QWidget *parent) : QMainWindow(parent), ui(new Ui::JsonTableView)
{
    ui->setupUi(this);
    ui->lineEdit->setText(jsonFilesPath);
    ui->lineEdit->clearFocus();

    watcher = new JsonDirWatcher(jsonFilesPath);
    watcher->moveToThread(&watcherThread);
    watcherThread.start();

    model = new QTableViewModel();
    connect(watcher, &JsonDirWatcher::jsonReaded, this, &JsonTableView::jsonInfoChanged);
}

void JsonTableView::jsonInfoChanged(QList<JsonInfo> inf)
{
    model->populate(&inf);
    this->ui->tableView->setModel(model);
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

