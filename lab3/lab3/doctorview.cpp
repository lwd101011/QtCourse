#include "doctorview.h"
#include "ui_doctorview.h"
#include "idatabase.h"

DoctorView::DoctorView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DoctorView)
{
    ui->setupUi(this);

    // 设置表格视图属性
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    // 初始化医生数据模型
    IDatabase &iDatabase = IDatabase::getInstance();
    if (iDatabase.initDoctorModel()) {
        ui->tableView->setModel(iDatabase.doctorTabModel);
        ui->tableView->setSelectionModel(iDatabase.theDoctorSelection);

        // 设置表格列宽自适应
        ui->tableView->horizontalHeader()->setStretchLastSection(true);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    }
}

DoctorView::~DoctorView()
{
    delete ui;
}

void DoctorView::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewDoctor();
    emit goDoctorEditView(currow);
}

void DoctorView::on_btSearch_clicked()
{
    QString filter = QString("name like '%%1%' or title like '%%2%'")
    .arg(ui->txtSearch->text())
        .arg(ui->txtSearch->text());
    IDatabase::getInstance().searchDoctor(filter);
}

void DoctorView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentDoctor();
}

void DoctorView::on_btEdit_clicked()
{
    QModelIndex curIndex =
        IDatabase::getInstance().theDoctorSelection->currentIndex();

    emit goDoctorEditView(curIndex.row());
}

void DoctorView::on_btSubmit_clicked()
{
    IDatabase::getInstance().submitDoctorEdit();
}

void DoctorView::on_btRevert_clicked()
{
    IDatabase::getInstance().revertDoctorEdit();
}
