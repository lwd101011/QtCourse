#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>
#include "statisticsthread.h"

namespace Ui {
class WelcomeView;
}

class WelcomeView : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeView(QWidget *parent = nullptr);
    ~WelcomeView();

signals:
    void goDepartmentView();
    void goDoctorView();
    void goPatientView();
    void goMedicalRecordView();
    void goMedicineView();
    void goAppointmentView();

private slots:
    void onStatisticsUpdated(int patientCount, int doctorCount,
                             int appointmentCount, int medicineCount,
                             int todayAppointments, int medicalRecordCount);

    void on_btDepartment_clicked();
    void on_btDoctor_clicked();
    void on_btPatient_clicked();
    void on_btMedicalRecord_clicked();
    void on_btMedicine_clicked();
    void on_btAppointment_clicked();

private:
    Ui::WelcomeView *ui;
    StatisticsThread *statisticsThread;
};

#endif // WELCOMEVIEW_H
