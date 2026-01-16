#ifndef APPOINTMENTEDITVIEW_H
#define APPOINTMENTEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class AppointmentEditView;
}

class AppointmentEditView : public QWidget
{
    Q_OBJECT

public:
    explicit AppointmentEditView(QWidget *parent = nullptr, int index = -1);
    ~AppointmentEditView();

private slots:
    void on_btSave_clicked();
    void on_btCancel_clicked();
    void on_cmbDepartment_currentIndexChanged(int index);
    void on_cmbPatient_currentIndexChanged(int index);

signals:
    void goPreviousView();

private:
    Ui::AppointmentEditView *ui;
    QDataWidgetMapper *dataMapper;
    void loadDoctorsByDepartment(const QString &departmentId);
    void loadPatientName(const QString &patientId);
};

#endif // APPOINTMENTEDITVIEW_H
