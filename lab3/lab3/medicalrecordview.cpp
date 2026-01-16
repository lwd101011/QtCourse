#include "medicalrecordview.h"
#include "ui_medicalrecordview.h"
#include "idatabase.h"
#include <QHeaderView>

MedicalRecordView::MedicalRecordView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MedicalRecordView)
{
    ui->setupUi(this);

    // 设置表格视图属性
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    // 初始化就诊记录数据模型
    IDatabase &iDatabase = IDatabase::getInstance();
    if (iDatabase.initMedicalRecordModel()) {
        ui->tableView->setModel(iDatabase.medicalRecordTabModel);
        ui->tableView->setSelectionModel(iDatabase.theMedicalRecordSelection);

        // 设置表格列宽自适应
        ui->tableView->horizontalHeader()->setStretchLastSection(true);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

        // 获取SQL表模型用于设置表头
        QSqlTableModel *sqlModel = iDatabase.medicalRecordTabModel;

        // 设置列标题
        sqlModel->setHeaderData(sqlModel->fieldIndex("patient_id"),
                                Qt::Horizontal, "患者姓名");
        sqlModel->setHeaderData(sqlModel->fieldIndex("department_id"),
                                Qt::Horizontal, "科室");
        sqlModel->setHeaderData(sqlModel->fieldIndex("doctor_id"),
                                Qt::Horizontal, "医生");
        sqlModel->setHeaderData(sqlModel->fieldIndex("visit_date"),
                                Qt::Horizontal, "就诊日期");
        sqlModel->setHeaderData(sqlModel->fieldIndex("diagnosis"),
                                Qt::Horizontal, "诊断结果");
        sqlModel->setHeaderData(sqlModel->fieldIndex("symptom"),
                                Qt::Horizontal, "症状描述");
    }
}

MedicalRecordView::~MedicalRecordView()
{
    delete ui;
}

void MedicalRecordView::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewMedicalRecord();
    emit goMedicalRecordEditView(currow);
}

void MedicalRecordView::on_btSearch_clicked()
{
    QString filter = QString("symptom like '%%1%' or diagnosis like '%%2%'")
    .arg(ui->txtSearch->text())
        .arg(ui->txtSearch->text());
    IDatabase::getInstance().searchMedicalRecord(filter);
}

void MedicalRecordView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentMedicalRecord();
}

void MedicalRecordView::on_btEdit_clicked()
{
    QModelIndex curIndex =
        IDatabase::getInstance().theMedicalRecordSelection->currentIndex();

    emit goMedicalRecordEditView(curIndex.row());
}

void MedicalRecordView::on_btSubmit_clicked()
{
    IDatabase::getInstance().submitMedicalRecordEdit();
}

void MedicalRecordView::on_btRevert_clicked()
{
    IDatabase::getInstance().revertMedicalRecordEdit();
}
