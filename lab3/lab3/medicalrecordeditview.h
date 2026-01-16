#ifndef MEDICALRECORDEDITVIEW_H
#define MEDICALRECORDEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>


namespace Ui {
class MedicalRecordEditView;
}

class MedicalRecordEditView : public QWidget
{
    Q_OBJECT

public:
    explicit MedicalRecordEditView(QWidget *parent = nullptr, int rowNo = -1);
    ~MedicalRecordEditView();

private slots:
    void on_btSave_clicked();
    void on_btCancel_clicked();

signals:
    void goPreviousView();

private:
    Ui::MedicalRecordEditView *ui;
    QDataWidgetMapper *mapper;
    int currentRow;
};

#endif // MEDICALRECORDEDITVIEW_H
