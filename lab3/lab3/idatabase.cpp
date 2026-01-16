#include "idatabase.h"
#include <QUuid>
#include <QDebug>
#include <QSqlError>

void IDatabase::ininDatabase()
{
    database=QSqlDatabase::addDatabase("QSQLITE");
    QString aFile="E:/QT/QTCourse/lab3/lab4a.db";
    database.setDatabaseName(aFile);

    if(!database.open()){
        qDebug() <<"failed to open database";
        qDebug() << database.lastError();
    }
    else
        qDebug() <<"open database is ok";

    // 初始化所有数据表
    QSqlQuery query;

    // 用户表
    query.exec("CREATE TABLE IF NOT EXISTS user ("
               "ID VARCHAR(64) PRIMARY KEY, "
               "username VARCHAR(32), "
               "password VARCHAR(32), "
               "CREATEDTIMESTAMP VARCHAR(32))");

    // 科室表
    query.exec("CREATE TABLE IF NOT EXISTS department ("
               "ID VARCHAR(64) PRIMARY KEY, "
               "name VARCHAR(64), "
               "location VARCHAR(128), "
               "phone VARCHAR(32), "
               "description VARCHAR(256), "
               "CREATEDTIMESTAMP VARCHAR(32))");

    // 医生表
    query.exec("CREATE TABLE IF NOT EXISTS doctor ("
               "ID VARCHAR(64) PRIMARY KEY, "
               "name VARCHAR(32), "
               "gender VARCHAR(8), "
               "title VARCHAR(32), "
               "department_id VARCHAR(64), "
               "phone VARCHAR(32), "
               "specialty VARCHAR(128), "
               "CREATEDTIMESTAMP VARCHAR(32), "
               "FOREIGN KEY (department_id) REFERENCES department(ID))");

    // 患者表
    query.exec("CREATE TABLE IF NOT EXISTS patient ("
               "ID VARCHAR(64) PRIMARY KEY, "
               "name VARCHAR(32), "
               "gender VARCHAR(8), "
               "birth_date VARCHAR(16), "
               "phone VARCHAR(32), "
               "address VARCHAR(256), "
               "emergency_contact VARCHAR(64), "
               "emergency_phone VARCHAR(32), "
               "medical_history VARCHAR(512), "
               "allergy_info VARCHAR(256), "
               "CREATEDTIMESTAMP VARCHAR(32))");

    // 药品库存表
    query.exec("CREATE TABLE IF NOT EXISTS medicine ("
               "ID VARCHAR(64) PRIMARY KEY, "
               "name VARCHAR(64), "
               "specification VARCHAR(64), "
               "unit VARCHAR(32), "
               "price DOUBLE, "
               "stock_quantity INT, "
               "min_stock INT, "
               "manufacturer VARCHAR(128), "
               "category VARCHAR(32), "
               "expiry_date VARCHAR(16), "
               "storage_location VARCHAR(64), "
               "CREATEDTIMESTAMP VARCHAR(32))");

    // 就诊记录表
    query.exec("CREATE TABLE IF NOT EXISTS medical_record ("
               "ID VARCHAR(64) PRIMARY KEY, "
               "patient_id VARCHAR(64), "
               "doctor_id VARCHAR(64), "
               "department_id VARCHAR(64), "
               "visit_date VARCHAR(16), "
               "symptom VARCHAR(256), "
               "diagnosis VARCHAR(256), "
               "treatment_plan VARCHAR(512), "
               "prescription VARCHAR(512), "
               "notes VARCHAR(512), "
               "CREATEDTIMESTAMP VARCHAR(32), "
               "FOREIGN KEY (patient_id) REFERENCES patient(ID), "
               "FOREIGN KEY (doctor_id) REFERENCES doctor(ID), "
               "FOREIGN KEY (department_id) REFERENCES department(ID))");

    // 预约排班表
    query.exec("CREATE TABLE IF NOT EXISTS appointment ("
               "ID VARCHAR(64) PRIMARY KEY, "
               "patient_id VARCHAR(64), "
               "doctor_id VARCHAR(64), "
               "department_id VARCHAR(64), "
               "appointment_date VARCHAR(16), "
               "appointment_time VARCHAR(16), "
               "status VARCHAR(16), "
               "appointment_type VARCHAR(32), "
               "notes VARCHAR(256), "
               "CREATEDTIMESTAMP VARCHAR(32), "
               "FOREIGN KEY (patient_id) REFERENCES patient(ID), "
               "FOREIGN KEY (doctor_id) REFERENCES doctor(ID), "
               "FOREIGN KEY (department_id) REFERENCES department(ID))");

    // 插入初始管理员用户
    query.exec("SELECT * FROM user WHERE username = 'admin'");
    if (!query.next()) {
        query.prepare("INSERT INTO user (ID, username, password, CREATEDTIMESTAMP) "
                      "VALUES (?, ?, ?, ?)");
        query.addBindValue(QUuid::createUuid().toString(QUuid::WithoutBraces));
        query.addBindValue("admin");
        query.addBindValue("admin123");
        query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
        query.exec();
    }
}

// 多线程统计查询实现
int IDatabase::getPatientCount()
{
    QSqlQuery query(database);
    query.exec("SELECT COUNT(*) FROM Patient");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int IDatabase::getDoctorCount()
{
    QSqlQuery query(database);
    query.exec("SELECT COUNT(*) FROM doctor");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int IDatabase::getAppointmentCount()
{
    QSqlQuery query(database);
    query.exec("SELECT COUNT(*) FROM appointment");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int IDatabase::getMedicineCount()
{
    QSqlQuery query(database);
    query.exec("SELECT COUNT(*) FROM medicine");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int IDatabase::getTodayAppointments()
{
    QString today = QDate::currentDate().toString("yyyy-MM-dd");
    QSqlQuery query(database);
    query.prepare(QString("SELECT COUNT(*) FROM appointment WHERE appointment_date = :today"));
    query.bindValue(":today", today);
    query.exec();
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int IDatabase::getMedicalRecordCount()
{
    QSqlQuery query(database);
    query.exec("SELECT COUNT(*) FROM medical_record");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

bool IDatabase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this,database);
    patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    patientTabModel->setSort(patientTabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(patientTabModel->select()))
        return false;

    thePatientSelection = new QItemSelectionModel(patientTabModel);
    return true;
}

int IDatabase::addNewPatient()
{
    patientTabModel->insertRow(patientTabModel->rowCount(),QModelIndex());
    QModelIndex curIndex = patientTabModel->index(patientTabModel->rowCount() - 1,1);

    int curRecNo = curIndex.row();
    QSqlRecord curRec = patientTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));

    patientTabModel->setRecord(curRecNo,curRec);

    return curIndex.row();
}

bool IDatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}

bool IDatabase::deleteCurrentPatient()
{
    if (!thePatientSelection->hasSelection()) {
        return false;
    }

    QModelIndex curIndex = thePatientSelection->currentIndex();
    if (curIndex.isValid()) {
        patientTabModel->removeRow(curIndex.row());
        return patientTabModel->submitAll();
    }
    return false;
}

bool IDatabase::submitPatientEdit()
{
    return patientTabModel->submitAll();
}

void IDatabase::revertPatientEdit()
{
    return patientTabModel->revertAll();
}

bool IDatabase::initDepartmentModel()
{
    departmentTabModel = new QSqlTableModel(this,database);
    departmentTabModel->setTable("department");
    departmentTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    departmentTabModel->setSort(departmentTabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(departmentTabModel->select()))
        return false;

    theDepartmentSelection = new QItemSelectionModel(departmentTabModel);
    return true;
}

int IDatabase::addNewDepartment()
{
    departmentTabModel->insertRow(departmentTabModel->rowCount(),QModelIndex());
    QModelIndex curIndex = departmentTabModel->index(departmentTabModel->rowCount() - 1,1);

    int curRecNo = curIndex.row();
    QSqlRecord curRec = departmentTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));

    departmentTabModel->setRecord(curRecNo,curRec);

    return curIndex.row();
}

bool IDatabase::searchDepartment(QString filter)
{
    departmentTabModel->setFilter(filter);
    return departmentTabModel->select();
}

bool IDatabase::deleteCurrentDepartment()
{
    if (!theDepartmentSelection->hasSelection()) {
        return false;
    }

    QModelIndex curIndex = theDepartmentSelection->currentIndex();
    if (curIndex.isValid()) {
        departmentTabModel->removeRow(curIndex.row());
        return departmentTabModel->submitAll();
    }
    return false;
}

bool IDatabase::submitDepartmentEdit()
{
    return departmentTabModel->submitAll();
}

void IDatabase::revertDepartmentEdit()
{
    return departmentTabModel->revertAll();
}

bool IDatabase::initDoctorModel()
{
    doctorTabModel = new QSqlTableModel(this,database);
    doctorTabModel->setTable("doctor");
    doctorTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    doctorTabModel->setSort(doctorTabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(doctorTabModel->select()))
        return false;

    theDoctorSelection = new QItemSelectionModel(doctorTabModel);
    return true;
}

int IDatabase::addNewDoctor()
{
    doctorTabModel->insertRow(doctorTabModel->rowCount(),QModelIndex());
    QModelIndex curIndex = doctorTabModel->index(doctorTabModel->rowCount() - 1,1);

    int curRecNo = curIndex.row();
    QSqlRecord curRec = doctorTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));

    doctorTabModel->setRecord(curRecNo,curRec);

    return curIndex.row();
}

bool IDatabase::searchDoctor(QString filter)
{
    doctorTabModel->setFilter(filter);
    return doctorTabModel->select();
}

bool IDatabase::deleteCurrentDoctor()
{
    if (!theDoctorSelection->hasSelection()) {
        return false;
    }

    QModelIndex curIndex = theDoctorSelection->currentIndex();
    if (curIndex.isValid()) {
        doctorTabModel->removeRow(curIndex.row());
        return doctorTabModel->submitAll();
    }
    return false;
}

bool IDatabase::submitDoctorEdit()
{
    return doctorTabModel->submitAll();
}

void IDatabase::revertDoctorEdit()
{
    return doctorTabModel->revertAll();
}

bool IDatabase::initMedicalRecordModel()
{
    medicalRecordTabModel = new QSqlTableModel(this,database);
    medicalRecordTabModel->setTable("medical_record");
    medicalRecordTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    medicalRecordTabModel->setSort(medicalRecordTabModel->fieldIndex("visit_date"),Qt::DescendingOrder);
    if(!(medicalRecordTabModel->select()))
        return false;

    theMedicalRecordSelection = new QItemSelectionModel(medicalRecordTabModel);
    return true;
}

int IDatabase::addNewMedicalRecord()
{
    medicalRecordTabModel->insertRow(medicalRecordTabModel->rowCount(),QModelIndex());
    QModelIndex curIndex = medicalRecordTabModel->index(medicalRecordTabModel->rowCount() - 1,1);

    int curRecNo = curIndex.row();
    QSqlRecord curRec = medicalRecordTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));

    medicalRecordTabModel->setRecord(curRecNo,curRec);

    return curIndex.row();
}

bool IDatabase::searchMedicalRecord(QString filter)
{
    medicalRecordTabModel->setFilter(filter);
    return medicalRecordTabModel->select();
}

bool IDatabase::deleteCurrentMedicalRecord()
{
    if (!theMedicalRecordSelection->hasSelection()) {
        return false;
    }

    QModelIndex curIndex = theMedicalRecordSelection->currentIndex();
    if (curIndex.isValid()) {
        medicalRecordTabModel->removeRow(curIndex.row());
        return medicalRecordTabModel->submitAll();
    }
    return false;
}

bool IDatabase::submitMedicalRecordEdit()
{
    return medicalRecordTabModel->submitAll();
}

void IDatabase::revertMedicalRecordEdit()
{
    return medicalRecordTabModel->revertAll();
}

bool IDatabase::initMedicineModel()
{
    medicineTabModel = new QSqlTableModel(this,database);
    medicineTabModel->setTable("medicine");
    medicineTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    medicineTabModel->setSort(medicineTabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(medicineTabModel->select()))
        return false;

    theMedicineSelection = new QItemSelectionModel(medicineTabModel);
    return true;
}

int IDatabase::addNewMedicine()
{
    medicineTabModel->insertRow(medicineTabModel->rowCount(),QModelIndex());
    QModelIndex curIndex = medicineTabModel->index(medicineTabModel->rowCount() - 1,1);

    int curRecNo = curIndex.row();
    QSqlRecord curRec = medicineTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));

    medicineTabModel->setRecord(curRecNo,curRec);

    return curIndex.row();
}

bool IDatabase::searchMedicine(QString filter)
{
    medicineTabModel->setFilter(filter);
    return medicineTabModel->select();
}

bool IDatabase::deleteCurrentMedicine()
{
    if (!theMedicineSelection->hasSelection()) {
        return false;
    }

    QModelIndex curIndex = theMedicineSelection->currentIndex();
    if (curIndex.isValid()) {
        medicineTabModel->removeRow(curIndex.row());
        return medicineTabModel->submitAll();
    }
    return false;
}

bool IDatabase::submitMedicineEdit()
{
    return medicineTabModel->submitAll();
}

void IDatabase::revertMedicineEdit()
{
    return medicineTabModel->revertAll();
}

bool IDatabase::initAppointmentModel()
{
    appointmentTabModel = new QSqlTableModel(this,database);
    appointmentTabModel->setTable("appointment");
    appointmentTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    appointmentTabModel->setSort(appointmentTabModel->fieldIndex("appointment_date"),Qt::AscendingOrder);
    if(!(appointmentTabModel->select()))
        return false;

    theAppointmentSelection = new QItemSelectionModel(appointmentTabModel);
    return true;
}

int IDatabase::addNewAppointment()
{
    appointmentTabModel->insertRow(appointmentTabModel->rowCount(),QModelIndex());
    QModelIndex curIndex = appointmentTabModel->index(appointmentTabModel->rowCount() - 1,1);

    int curRecNo = curIndex.row();
    QSqlRecord curRec = appointmentTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));
    curRec.setValue("status", "待确认");

    appointmentTabModel->setRecord(curRecNo,curRec);

    return curIndex.row();
}

bool IDatabase::searchAppointment(QString filter)
{
    appointmentTabModel->setFilter(filter);
    return appointmentTabModel->select();
}

bool IDatabase::deleteCurrentAppointment()
{
    if (!theAppointmentSelection->hasSelection()) {
        return false;
    }

    QModelIndex curIndex = theAppointmentSelection->currentIndex();
    if (curIndex.isValid()) {
        appointmentTabModel->removeRow(curIndex.row());
        return appointmentTabModel->submitAll();
    }
    return false;
}

bool IDatabase::submitAppointmentEdit()
{
    return appointmentTabModel->submitAll();
}

void IDatabase::revertAppointmentEdit()
{
    return appointmentTabModel->revertAll();
}

QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query;
    query.prepare("select username,password from user where username = :USER");
    query.bindValue(":USER",userName);
    query.exec();
    if (query.first() && query.value("username").isValid()){
        QString passwd = query.value("password").toString();
        if(passwd == password)
        {
            qDebug() <<"login ok";
            return "loginOK";
        }
        else
        {
            qDebug() <<"wrong password";
            return "wrongPassword";
        }
    }
    else{
        qDebug()<< "no such user";
        return "wrongUsername";
    }
}

IDatabase::IDatabase(QObject *parent) : QObject(parent)
{
    ininDatabase();
}
