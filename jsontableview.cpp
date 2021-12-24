#include "jsontableview.h"

JsonTableView::JsonTableView(QWidget *parent) : QMainWindow(parent), ui(new Ui::JsonTableView)
{
    ui->setupUi(this);
    ui->lineEdit->setText(jsonFilesPath);
    ui->lineEdit->clearFocus();

    watcher = new JsonDirWatcher(jsonFilesPath);
    watcher->moveToThread(&watcherThread);
    watcherThread.start();







//    QList<JsonInfo> *values = new QList<JsonInfo>;
//    values->append(JsonInfo(1,"test",0,1.2));


//    QTableViewModel *model = new QTableViewModel();
//    model->populate(values);
//    this->ui->tableView->setModel(model);
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

