#include "appointmenteditview.h"
#include "ui_appointmenteditview.h"
#include "idatabase.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QDateTime>

AppointmentEditView::AppointmentEditView(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::AppointmentEditView)
{
    ui->setupUi(this);

    // 设置窗口标题
    this->setWindowTitle("预约信息编辑");

    // 创建数据映射器
    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().appointmentTabModel;
    dataMapper->setModel(IDatabase::getInstance().appointmentTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    // 初始化患者下拉框
    QSqlQuery patientQuery;
    patientQuery.exec("SELECT ID, name FROM patient");
    while (patientQuery.next()) {
        ui->cmbPatient->addItem(patientQuery.value("name").toString(), patientQuery.value("ID"));
    }

    // 初始化科室下拉框
    QSqlQuery deptQuery;
    deptQuery.exec("SELECT ID, name FROM department");
    while (deptQuery.next()) {
        ui->cmbDepartment->addItem(deptQuery.value("name").toString(), deptQuery.value("ID"));
    }

    // 初始化预约状态下拉框
    ui->cmbStatus->addItem("待确认", "待确认");
    ui->cmbStatus->addItem("已确认", "已确认");
    ui->cmbStatus->addItem("已就诊", "已就诊");
    ui->cmbStatus->addItem("已取消", "已取消");

    // 绑定表单控件到数据模型字段
    dataMapper->addMapping(ui->txtID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->cmbStatus, tabModel->fieldIndex("STATUS"));
    dataMapper->addMapping(ui->txtNotes, tabModel->fieldIndex("NOTES"));

    // 设置当前编辑行
    if (index >= 0) {
        dataMapper->setCurrentIndex(index);

        // 加载当前预约的患者、科室、医生信息
        QSqlRecord curRec = tabModel->record(index);
        QString patientId = curRec.value("PATIENT_ID").toString();
        QString deptId = curRec.value("DEPARTMENT_ID").toString();
        QString doctorId = curRec.value("DOCTOR_ID").toString();
        QString appointmentDate = curRec.value("APPOINTMENT_DATE").toString();
        QString appointmentTime = curRec.value("APPOINTMENT_TIME").toString();

        // 设置患者选中状态
        if (!patientId.isEmpty()) {
            int patientIndex = ui->cmbPatient->findData(patientId);
            if (patientIndex >= 0) {
                ui->cmbPatient->setCurrentIndex(patientIndex);
            }
        }

        // 设置科室选中状态
        if (!deptId.isEmpty()) {
            int deptIndex = ui->cmbDepartment->findData(deptId);
            if (deptIndex >= 0) {
                ui->cmbDepartment->setCurrentIndex(deptIndex);
                loadDoctorsByDepartment(deptId);
            }
        }

        // 设置医生选中状态
        if (!doctorId.isEmpty()) {
            int doctorIndex = ui->cmbDoctor->findData(doctorId);
            if (doctorIndex >= 0) {
                ui->cmbDoctor->setCurrentIndex(doctorIndex);
            }
        }

        // 设置日期
        if (!appointmentDate.isEmpty()) {
            QDate date = QDate::fromString(appointmentDate, "yyyy-MM-dd");
            if (date.isValid()) {
                ui->dateAppointment->setDate(date);
            }
        }

        // 设置时间
        if (!appointmentTime.isEmpty()) {
            QTime time = QTime::fromString(appointmentTime, "HH:mm");
            if (time.isValid()) {
                ui->timeAppointment->setTime(time);
            }
        }
    }

    // 连接科室选择变化信号
    connect(ui->cmbDepartment, SIGNAL(currentIndexChanged(int)),
            this, SLOT(on_cmbDepartment_currentIndexChanged(int)));
}

AppointmentEditView::~AppointmentEditView()
{
    delete ui;
    delete dataMapper;
}

void AppointmentEditView::loadDoctorsByDepartment(const QString &departmentId)
{
    // 清空医生下拉框
    ui->cmbDoctor->clear();

    if (departmentId.isEmpty()) {
        return;
    }

    // 根据科室ID加载医生
    QSqlQuery query;
    query.prepare("SELECT ID, name FROM doctor WHERE department_id = :DEPT_ID");
    query.bindValue(":DEPT_ID", departmentId);
    query.exec();

    while (query.next()) {
        ui->cmbDoctor->addItem(query.value("name").toString(), query.value("ID"));
    }
}

void AppointmentEditView::on_cmbDepartment_currentIndexChanged(int index)
{
    if (index >= 0) {
        QString deptId = ui->cmbDepartment->itemData(index).toString();
        loadDoctorsByDepartment(deptId);
    }
}

void AppointmentEditView::on_btSave_clicked()
{
    // 手动设置关联字段到模型
    int currentIndex = dataMapper->currentIndex();
    if (currentIndex >= 0) {
        QSqlTableModel *tabModel = IDatabase::getInstance().appointmentTabModel;

        // 获取并设置患者ID和患者姓名
        if (ui->cmbPatient->currentIndex() >= 0) {
            QString patientId = ui->cmbPatient->currentData().toString();
            QString patientName = ui->cmbPatient->currentText();
            tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("PATIENT_ID")), patientId);
            tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("PATIENT_NAME")), patientName);
        }

        // 获取并设置科室ID和科室名称
        if (ui->cmbDepartment->currentIndex() >= 0) {
            QString deptId = ui->cmbDepartment->currentData().toString();
            QString deptName = ui->cmbDepartment->currentText();
            tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("DEPARTMENT_ID")), deptId);
            tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("DEPARTMENT_NAME")), deptName);
        }

        // 获取并设置医生ID和医生姓名
        if (ui->cmbDoctor->currentIndex() >= 0) {
            QString doctorId = ui->cmbDoctor->currentData().toString();
            QString doctorName = ui->cmbDoctor->currentText();
            tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("DOCTOR_ID")), doctorId);
            tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("DOCTOR_NAME")), doctorName);
        }

        // 设置日期和时间
        QString appointmentDate = ui->dateAppointment->date().toString("yyyy-MM-dd");
        QString appointmentTime = ui->timeAppointment->time().toString("HH:mm");
        tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("APPOINTMENT_DATE")), appointmentDate);
        tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("APPOINTMENT_TIME")), appointmentTime);
    }

    // 提交所有更改到数据库
    IDatabase::getInstance().submitAppointmentEdit();
    emit goPreviousView();
}

void AppointmentEditView::on_btCancel_clicked()
{
    // 撤销所有未提交的更改
    IDatabase::getInstance().revertAppointmentEdit();
    emit goPreviousView();
}
