#ifndef DOCTOREDITVIEW_H
#define DOCTOREDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class DoctorEditView;
}

class DoctorEditView : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorEditView(QWidget *parent = nullptr, int index = -1);
    ~DoctorEditView();

private slots:
    void on_btSave_clicked();
    void on_btCancel_clicked();

signals:
    void goPreviousView();

private:
    Ui::DoctorEditView *ui;
    QDataWidgetMapper *dataMapper;
};

#endif // DOCTOREDITVIEW_H
