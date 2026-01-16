#ifndef MEDICALRECORDVIEW_H
#define MEDICALRECORDVIEW_H

#include <QWidget>

namespace Ui {
class MedicalRecordView;
}

class MedicalRecordView : public QWidget
{
    Q_OBJECT

public:
    explicit MedicalRecordView(QWidget *parent = nullptr);
    ~MedicalRecordView();

private slots:
    void on_btAdd_clicked();
    void on_btSearch_clicked();
    void on_btDelete_clicked();
    void on_btEdit_clicked();
    void on_btSubmit_clicked();
    void on_btRevert_clicked();

signals:
    void goMedicalRecordEditView(int idx);

private:
    Ui::MedicalRecordView *ui;
};

#endif // MEDICALRECORDVIEW_H
