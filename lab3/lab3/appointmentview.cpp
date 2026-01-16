#include "appointmentview.h"
#include "ui_appointmentview.h"
#include "idatabase.h"

AppointmentView::AppointmentView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AppointmentView)
{
    ui->setupUi(this);

    // 设置表格视图属性
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    // 初始化预约数据模型并绑定到表格视图
    IDatabase &iDatabase = IDatabase::getInstance();
    if (iDatabase.initAppointmentModel()) {
        ui->tableView->setModel(iDatabase.appointmentTabModel);
        ui->tableView->setSelectionModel(iDatabase.theAppointmentSelection);

        // 隐藏ID列，只显示名称列
        QSqlTableModel *tabModel = iDatabase.appointmentTabModel;

        // 隐藏ID列
        ui->tableView->setColumnHidden(tabModel->fieldIndex("PATIENT_ID"), true);
        ui->tableView->setColumnHidden(tabModel->fieldIndex("DOCTOR_ID"), true);
        ui->tableView->setColumnHidden(tabModel->fieldIndex("DEPARTMENT_ID"), true);

        // 设置列宽自适应
        ui->tableView->horizontalHeader()->setStretchLastSection(true);
    }
}

AppointmentView::~AppointmentView()
{
    delete ui;
}

void AppointmentView::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewAppointment();
    emit goAppointmentEditView(currow);
}

void AppointmentView::on_btSearch_clicked()
{
    QString dateStr = ui->dateSearch->date().toString("yyyy-MM-dd");
    QString filter = QString("appointment_date = '%1'").arg(dateStr);
    IDatabase::getInstance().searchAppointment(filter);
}

void AppointmentView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentAppointment();
}

void AppointmentView::on_btEdit_clicked()
{
    QModelIndex curIndex = IDatabase::getInstance().theAppointmentSelection->currentIndex();
    emit goAppointmentEditView(curIndex.row());
}

void AppointmentView::on_btSubmit_clicked()
{
    IDatabase::getInstance().submitAppointmentEdit();
}

void AppointmentView::on_btRevert_clicked()
{
    IDatabase::getInstance().revertAppointmentEdit();
}
