#include "jsontableview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    jsonTableView w;
    w.show();
    return a.exec();
}
