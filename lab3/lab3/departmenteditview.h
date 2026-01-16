#ifndef DEPARTMENTEDITVIEW_H
#define DEPARTMENTEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class DepartmentEditView;
}

class DepartmentEditView : public QWidget
{
    Q_OBJECT

public:
    explicit DepartmentEditView(QWidget *parent = nullptr, int index = -1);
    ~DepartmentEditView();

private slots:
    void on_btSave_clicked();

    void on_btCancel_clicked();

signals:
    void goPreviousView();

private:
    Ui::DepartmentEditView *ui;
    QDataWidgetMapper *dataMapper;
};

#endif // DEPARTMENTEDITVIEW_H
//科室编辑
