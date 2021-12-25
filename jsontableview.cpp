#include "jsontableview.h"

JsonTableView::JsonTableView(QWidget *parent) : QMainWindow(parent), ui(new Ui::JsonTableView)
{
JsonTableView::JsonTableView(QWidget *parent) : QMainWindow(parent), ui(new Ui::JsonTableView)
{
    ui->lineEdit->setText(jsonFilesPath);
    ui->lineEdit->clearFocus();
    ui->setupUi(this);
    ui->lineEdit->setText(jsonFilesPath);
    ui->lineEdit->clearFocus();

    watcher = new JsonDirWatcher(jsonFilesPath);
    watcher->moveToThread(&watcherThread);
    watcherThread.start();

    model = new QTableViewModel();
    this->ui->tableView->setModel(model);

    connect(watcher, &JsonDirWatcher::jsonReaded, this, &JsonTableView::jsonInfoChanged);
}

void JsonTableView::jsonInfoChanged(QList<JsonInfo> inf)
{
    model->update(inf);
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

