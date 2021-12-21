#include "jsontableview.h"
#include "ui_jsontableview.h"

jsonTableView::jsonTableView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::jsonTableView)
{
    ui->setupUi(this);
}

jsonTableView::~jsonTableView()
{
    delete ui;
}

