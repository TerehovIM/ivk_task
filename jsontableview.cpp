#include "jsontableview.h"
#include "ui_jsontableview.h"

JsonTableView::JsonTableView(QWidget *parent) : QMainWindow(parent), ui(new Ui::JsonTableView)
{
    QString test = jsonFilesPath;
    ui->setupUi(this);


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

