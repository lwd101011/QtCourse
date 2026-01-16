#include "medicineeditview.h"
#include "ui_medicineeditview.h"
#include "idatabase.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDate>

MedicineEditView::MedicineEditView(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::MedicineEditView)
{
    ui->setupUi(this);

    // 设置窗口标题
    this->setWindowTitle("药品信息编辑");

    // 创建数据映射器
    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().medicineTabModel;
    dataMapper->setModel(IDatabase::getInstance().medicineTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    // 绑定表单控件到数据模型字段
    dataMapper->addMapping(ui->txtID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->txtName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->txtSpecification, tabModel->fieldIndex("SPECIFICATION"));
    dataMapper->addMapping(ui->txtUnit, tabModel->fieldIndex("UNIT"));
    dataMapper->addMapping(ui->spnPrice, tabModel->fieldIndex("PRICE"));
    dataMapper->addMapping(ui->spnStock, tabModel->fieldIndex("STOCK_QUANTITY"));
    dataMapper->addMapping(ui->spnMinStock, tabModel->fieldIndex("MIN_STOCK"));
    dataMapper->addMapping(ui->txtStorage, tabModel->fieldIndex("STORAGE_LOCATION"));

    // 处理有效期日期（数据库存储为字符串，UI使用QDateEdit）
    // 需要在保存时进行转换

    // 设置当前编辑行
    if (index >= 0) {
        dataMapper->setCurrentIndex(index);

        // 初始化有效期日期
        QSqlRecord curRec = tabModel->record(index);
        QString expiryDate = curRec.value("EXPIRY_DATE").toString();
        if (!expiryDate.isEmpty()) {
            QDate date = QDate::fromString(expiryDate, "yyyy-MM-dd");
            if (date.isValid()) {
                ui->dateExpiry->setDate(date);
            }
        }
    }
}

MedicineEditView::~MedicineEditView()
{
    delete ui;
    delete dataMapper;
}

void MedicineEditView::on_btSave_clicked()
{
    // 手动设置有效期日期到模型
    int currentIndex = dataMapper->currentIndex();
    if (currentIndex >= 0) {
        QSqlTableModel *tabModel = IDatabase::getInstance().medicineTabModel;
        QString expiryDate = ui->dateExpiry->date().toString("yyyy-MM-dd");
        tabModel->setData(tabModel->index(currentIndex, tabModel->fieldIndex("EXPIRY_DATE")), expiryDate);
    }

    // 提交所有更改到数据库
    IDatabase::getInstance().submitMedicineEdit();
    emit goPreviousView();
}

void MedicineEditView::on_btCancel_clicked()
{
    // 撤销所有未提交的更改
    IDatabase::getInstance().revertMedicineEdit();
    emit goPreviousView();
}
