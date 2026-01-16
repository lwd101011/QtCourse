#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QtSql>
#include <QsqlDatabase>
#include <QDataWidgetMapper>

class IDatabase : public QObject
{
    Q_OBJECT
public:
    static IDatabase &getInstance()
    {
        static IDatabase instance;
        return instance;
    }

    QString userLogin(QString userName,QString password);

    // 获取数据库实例的公共方法
    QSqlDatabase getDatabase() const { return database; }

private:
    explicit IDatabase(QObject *parent = nullptr);
    IDatabase(IDatabase const &) = delete;
    void operator=(IDatabase const &) = delete;

    QSqlDatabase database;
    void ininDatabase();

signals:
    void dataChanged();

public:
    // 患者管理
    bool initPatientModel();
    int addNewPatient();
    bool searchPatient(QString filter);
    bool deleteCurrentPatient();
    bool submitPatientEdit();
    void revertPatientEdit();

    QSqlTableModel *patientTabModel;
    QItemSelectionModel *thePatientSelection;

    // 科室管理
    bool initDepartmentModel();
    int addNewDepartment();
    bool searchDepartment(QString filter);
    bool deleteCurrentDepartment();
    bool submitDepartmentEdit();
    void revertDepartmentEdit();

    QSqlTableModel *departmentTabModel;
    QItemSelectionModel *theDepartmentSelection;

    // 医生管理
    bool initDoctorModel();
    int addNewDoctor();
    bool searchDoctor(QString filter);
    bool deleteCurrentDoctor();
    bool submitDoctorEdit();
    void revertDoctorEdit();

    QSqlTableModel *doctorTabModel;
    QItemSelectionModel *theDoctorSelection;

    // 就诊记录管理
    bool initMedicalRecordModel();
    int addNewMedicalRecord();
    bool searchMedicalRecord(QString filter);
    bool deleteCurrentMedicalRecord();
    bool submitMedicalRecordEdit();
    void revertMedicalRecordEdit();

    QSqlTableModel *medicalRecordTabModel;
    QItemSelectionModel *theMedicalRecordSelection;

    // 药品库存管理
    bool initMedicineModel();
    int addNewMedicine();
    bool searchMedicine(QString filter);
    bool deleteCurrentMedicine();
    bool submitMedicineEdit();
    void revertMedicineEdit();

    QSqlTableModel *medicineTabModel;
    QItemSelectionModel *theMedicineSelection;

    // 预约排班管理
    bool initAppointmentModel();
    int addNewAppointment();
    bool searchAppointment(QString filter);
    bool deleteCurrentAppointment();
    bool submitAppointmentEdit();
    void revertAppointmentEdit();

    QSqlTableModel *appointmentTabModel;
    QItemSelectionModel *theAppointmentSelection;
};

#endif // IDATABASE_H
