#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include "loginview.h"
#include "doctorview.h"
#include "doctoreditview.h"
#include "departmentview.h"
#include "patientview.h"
#include "patienteditview.h"
#include "welcomeview.h"
#include "departmenteditview.h"
#include "medicalrecordview.h"
#include "medicalrecordeditview.h"
#include "medicineview.h"
#include "medicineeditview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MasterView;
}
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();

public slots:
    void goLoginView();
    void goWelcomeView();
    void goDoctorView();
    void goDoctorEditView(int rowNo);
    void goDepartmentView();
    void goDepartmentEditView(int rowNo);
    void goPatientEditView(int rowNo);
    void goPatientView();
    void goMedicalRecordView();
    void goMedicalRecordEditView(int rowNo);
    void goMedicineView();
    void goMedicineEditView(int rowNo);
    void goPreviousView();

private slots:
    void on_btBack_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_btLogout_clicked();

private:
    void pushWidgetToStackView(QWidget *widget);

    Ui::MasterView *ui;

    WelcomeView *welcomeView;
    DoctorView *doctorView;
    DoctorEditView *doctorEditView;
    DepartmentView *departmentView;
    DepartmentEditView *departmentEditView;
    PatientView *patientView;
    LoginView *loginView;
    PatientEditView *patientEditView;
    MedicalRecordView *medicalRecordView;
    MedicalRecordEditView *medicalRecordEditView;
    MedicineView *medicineView;
    MedicineEditView *medicineEditView;
};
#endif // MASTERVIEW_H
