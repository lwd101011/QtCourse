#include "medicalrecordeditview.h"
#include "ui_medicalrecordeditview.h"
#include "idatabase.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>


MedicalRecordEditView::MedicalRecordEditView(QWidget *parent, int rowNo)
    : QWidget(parent)
    , ui(new Ui::MedicalRecordEditView)
{
    ui->setupUi(this);
    currentRow = rowNo;

    // 创建数据映射器
    mapper = new QDataWidgetMapper(this);
    IDatabase &iDatabase = IDatabase::getInstance();
    mapper->setModel(iDatabase.medicalRecordTabModel);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    // 将UI控件映射到数据库字段
    mapper->addMapping(ui->txtID, iDatabase.medicalRecordTabModel->fieldIndex("ID"));
    mapper->addMapping(ui->cmbPatient, iDatabase.medicalRecordTabModel->fieldIndex("patient_id"));
    mapper->addMapping(ui->cmbDepartment, iDatabase.medicalRecordTabModel->fieldIndex("department_id"));
    mapper->addMapping(ui->cmbDoctor, iDatabase.medicalRecordTabModel->fieldIndex("doctor_id"));
    mapper->addMapping(ui->dateVisit, iDatabase.medicalRecordTabModel->fieldIndex("visit_date"));
    mapper->addMapping(ui->txtSymptom, iDatabase.medicalRecordTabModel->fieldIndex("symptom"));
    mapper->addMapping(ui->txtDiagnosis, iDatabase.medicalRecordTabModel->fieldIndex("diagnosis"));
    mapper->addMapping(ui->txtTreatment, iDatabase.medicalRecordTabModel->fieldIndex("treatment_plan"));
    mapper->addMapping(ui->txtPrescription, iDatabase.medicalRecordTabModel->fieldIndex("prescription"));
    mapper->addMapping(ui->txtNotes, iDatabase.medicalRecordTabModel->fieldIndex("notes"));

    // 加载患者数据到下拉框
    QSqlQueryModel *patientModel = new QSqlQueryModel(this);
    patientModel->setQuery("SELECT name, ID FROM patient", iDatabase.getDatabase());
    ui->cmbPatient->setModel(patientModel);
    ui->cmbPatient->setModelColumn(0);

    // 加载科室数据到下拉框
    QSqlQueryModel *departmentModel = new QSqlQueryModel(this);
    departmentModel->setQuery("SELECT name, ID FROM department", iDatabase.getDatabase());
    ui->cmbDepartment->setModel(departmentModel);
    ui->cmbDepartment->setModelColumn(0);

    // 加载医生数据到下拉框
    QSqlQueryModel *doctorModel = new QSqlQueryModel(this);
    doctorModel->setQuery("SELECT name, ID FROM doctor", iDatabase.getDatabase());
    ui->cmbDoctor->setModel(doctorModel);
    ui->cmbDoctor->setModelColumn(0);

    // 跳转到当前行
    mapper->setCurrentIndex(rowNo);
}

MedicalRecordEditView::~MedicalRecordEditView()
{
    delete ui;
}

void MedicalRecordEditView::on_btSave_clicked()
{
    mapper->submit();

    IDatabase &iDatabase = IDatabase::getInstance();
    if (iDatabase.submitMedicalRecordEdit()) {
        QMessageBox::information(this, "成功", "就诊记录保存成功！");
        emit goPreviousView();
    } else {
        QMessageBox::warning(this, "错误", "保存就诊记录失败！");
    }
}

void MedicalRecordEditView::on_btCancel_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();
    iDatabase.revertMedicalRecordEdit();
    emit goPreviousView();
}
