#ifndef JSONTABLEVIEW_H
#define JSONTABLEVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class jsonTableView; }
QT_END_NAMESPACE

class jsonTableView : public QMainWindow
{
    Q_OBJECT

public:
    jsonTableView(QWidget *parent = nullptr);
    ~jsonTableView();

private:
    Ui::jsonTableView *ui;
};
#endif // JSONTABLEVIEW_H
