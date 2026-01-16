#include "medicineview.h"
#include "ui_medicineview.h"
#include "idatabase.h"

MedicineView::MedicineView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MedicineView)
{
    ui->setupUi(this);

    // 设置表格视图属性
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    // 初始化药品数据模型并绑定到表格视图
    IDatabase &iDatabase = IDatabase::getInstance();
    if (iDatabase.initMedicineModel()) {
        ui->tableView->setModel(iDatabase.medicineTabModel);
        ui->tableView->setSelectionModel(iDatabase.theMedicineSelection);
        // 设置列宽自适应
        ui->tableView->horizontalHeader()->setStretchLastSection(true);
    }
}

MedicineView::~MedicineView()
{
    delete ui;
}

void MedicineView::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewMedicine();
    emit goMedicineEditView(currow);
}

void MedicineView::on_btSearch_clicked()
{
    QString filter = QString("name like '%%1%' or category like '%%1%' or manufacturer like '%%1%'")
    .arg(ui->txtSearch->text());
    IDatabase::getInstance().searchMedicine(filter);
}

void MedicineView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentMedicine();
}

void MedicineView::on_btEdit_clicked()
{
    QModelIndex curIndex = IDatabase::getInstance().theMedicineSelection->currentIndex();
    emit goMedicineEditView(curIndex.row());
}

void MedicineView::on_btSubmit_clicked()
{
    IDatabase::getInstance().submitMedicineEdit();
}

void MedicineView::on_btRevert_clicked()
{
    IDatabase::getInstance().revertMedicineEdit();
}

void MedicineView::on_btLowStock_clicked()
{
    // 显示库存预警，筛选出库存低于最低库存的药品
    QString filter = "stock_quantity < min_stock";
    IDatabase::getInstance().searchMedicine(filter);
}
