#include "WelcomeView.h"
#include "ui_WelcomeView.h"
#include <QDebug>
#include <QDateTime>

WelcomeView::WelcomeView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeView)
    , statisticsThread(nullptr)
{
    qDebug() << "create WelcomeView";
    ui->setupUi(this);

    // 初始化并启动后台统计线程
    statisticsThread = new StatisticsThread(this);
    connect(statisticsThread, &StatisticsThread::statisticsUpdated,
            this, &WelcomeView::onStatisticsUpdated);
    statisticsThread->startStatistics();
}

WelcomeView::~WelcomeView()
{
    qDebug() << "destroy WelcomeView";
    if (statisticsThread) {
        statisticsThread->stopStatistics();
        delete statisticsThread;
    }
    delete ui;
}

void WelcomeView::onStatisticsUpdated(int patientCount, int doctorCount,
                                         int appointmentCount, int medicineCount,
                                         int todayAppointments, int medicalRecordCount)
{
    // 更新UI显示
    ui->lblPatientCount->setText(QString::number(patientCount));
    ui->lblDoctorCount->setText(QString::number(doctorCount));
    ui->lblAppointmentCount->setText(QString::number(appointmentCount));
    ui->lblMedicineCount->setText(QString::number(medicineCount));
    ui->lblTodayAppointments->setText(QString::number(todayAppointments));
    ui->lblMedicalRecordCount->setText(QString::number(medicalRecordCount));

    // 更新时间戳
    ui->lblLastUpdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    qDebug() << "UI updated with latest statistics";
}

void WelcomeView::on_btDepartment_clicked()
{
    emit goDepartmentView();
}

void WelcomeView::on_btDoctor_clicked()
{
    emit goDoctorView();
}

void WelcomeView::on_btPatient_clicked()
{
    emit goPatientView();
}

void WelcomeView::on_btMedicalRecord_clicked()
{
    emit goMedicalRecordView();
}

void WelcomeView::on_btMedicine_clicked()
{
    emit goMedicineView();
}

void WelcomeView::on_btAppointment_clicked()
{
    emit goAppointmentView();
}
