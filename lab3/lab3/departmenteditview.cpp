#include "departmenteditview.h"
#include "ui_departmenteditview.h"
#include "idatabase.h"
#include <QSqlTableModel>
#include <QSqlRecord>

DepartmentEditView::DepartmentEditView(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::DepartmentEditView)
{
    ui->setupUi(this);

    // 创建数据映射器
    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().departmentTabModel;
    dataMapper->setModel(IDatabase::getInstance().departmentTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    // 绑定表单控件到数据模型字段
    dataMapper->addMapping(ui->txtID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->txtName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->txtLocation, tabModel->fieldIndex("LOCATION"));
    dataMapper->addMapping(ui->txtPhone, tabModel->fieldIndex("PHONE"));

    // 设置当前编辑行
    if (index >= 0) {
        dataMapper->setCurrentIndex(index);
    }
}

DepartmentEditView::~DepartmentEditView()
{
    delete ui;
    delete dataMapper;
}

void DepartmentEditView::on_btSave_clicked()
{
    // 提交所有更改到数据库
    IDatabase::getInstance().submitDepartmentEdit();
    emit goPreviousView();
}

void DepartmentEditView::on_btCancel_clicked()
{
    // 撤销所有未提交的更改
    IDatabase::getInstance().revertDepartmentEdit();
    emit goPreviousView();
}
