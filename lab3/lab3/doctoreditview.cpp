#include "doctoreditview.h"
#include "ui_doctoreditview.h"
#include "idatabase.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>

DoctorEditView::DoctorEditView(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::DoctorEditView)
{
    ui->setupUi(this);

    // 设置窗口标题
    this->setWindowTitle("医生信息编辑");

    // 创建数据映射器
    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().doctorTabModel;
    dataMapper->setModel(IDatabase::getInstance().doctorTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    // 绑定表单控件到数据模型字段
    dataMapper->addMapping(ui->txtID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->txtName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->txtTitle, tabModel->fieldIndex("TITLE"));
    dataMapper->addMapping(ui->txtPhone, tabModel->fieldIndex("PHONE"));
    dataMapper->addMapping(ui->txtSpecialty, tabModel->fieldIndex("SPECIALTY"));

    // 初始化性别下拉框
    ui->cmbGender->addItem("男");
    ui->cmbGender->addItem("女");
    dataMapper->addMapping(ui->cmbGender, tabModel->fieldIndex("GENDER"));

    // 初始化科室下拉框
    QSqlQuery query;
    query.exec("SELECT ID, name FROM department");
    while (query.next()) {
        ui->cmbDepartment->addItem(query.value("name").toString(), query.value("ID"));
    }

    // 设置当前编辑行
    if (index >= 0) {
        dataMapper->setCurrentIndex(index);

        // 初始化科室下拉框的选中状态
        QSqlRecord curRec = tabModel->record(index);
        QString deptId = curRec.value("DEPARTMENT_ID").toString();
        if (!deptId.isEmpty()) {
            int deptIndex = ui->cmbDepartment->findData(deptId);
            if (deptIndex >= 0) {
                ui->cmbDepartment->setCurrentIndex(deptIndex);
            }
        }
    }
}

DoctorEditView::~DoctorEditView()
{
    delete ui;
    delete dataMapper;
}

void DoctorEditView::on_btSave_clicked()
{
    // 手动设置科室ID和科室名称到模型
    int currentIndex = dataMapper->currentIndex();
    if (currentIndex >= 0) {
        QSqlTableModel *tabModel = IDatabase::getInstance().doctorTabModel;
        QString deptId = ui->cmbDepartment->currentData().toString();
        QString deptName = ui->cmbDepartment->currentText();
        tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("DEPARTMENT_ID")), deptId);
        tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("DEPARTMENT_NAME")), deptName);
    }

    // 提交所有更改到数据库
    IDatabase::getInstance().submitDoctorEdit();
    emit goPreviousView();
}

void DoctorEditView::on_btCancel_clicked()
{
    // 撤销所有未提交的更改
    IDatabase::getInstance().revertDoctorEdit();
    emit goPreviousView();
}
//医生编辑
