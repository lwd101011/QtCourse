#include "statisticsthread.h"
#include <QSqlError>

StatisticsThread::StatisticsThread(QObject *parent)
    : QThread(parent)
    , isRunning(false)
    , timer(nullptr)
    , patientCount(0)
    , doctorCount(0)
    , appointmentCount(0)
    , medicineCount(0)
    , todayAppointments(0)
    , medicalRecordCount(0)
    , lastUpdateTime("")
{
    // 获取数据库连接
    database = IDatabase::getInstance().getDatabase();
}

StatisticsThread::~StatisticsThread()
{
    stopStatistics();
    wait();
}

void StatisticsThread::startStatistics()
{
    if (!isRunning) {
        isRunning = true;
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &StatisticsThread::calculateStatistics, Qt::DirectConnection);
        timer->start(5000); // 每5秒更新一次统计
        qDebug() << "Statistics thread started with 5-second interval";
        calculateStatistics(); // 立即执行一次
    }
}

void StatisticsThread::stopStatistics()
{
    if (isRunning) {
        isRunning = false;
        if (timer) {
            timer->stop();
            delete timer;
            timer = nullptr;
        }
        qDebug() << "Statistics thread stopped";
    }
}

void StatisticsThread::run()
{
    qDebug() << "Statistics thread running...";
    exec(); // 启动事件循环
}

void StatisticsThread::calculateStatistics()
{
    if (!isRunning) return;

    qDebug() << "Calculating statistics at:" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    // 查询患者总数
    performQuery("SELECT COUNT(*) FROM Patient", patientCount, "patientCount");

    // 查询医生总数
    performQuery("SELECT COUNT(*) FROM doctor", doctorCount, "doctorCount");

    // 查询预约总数
    performQuery("SELECT COUNT(*) FROM appointment", appointmentCount, "appointmentCount");

    // 查询药品总数
    performQuery("SELECT COUNT(*) FROM medicine", medicineCount, "medicineCount");

    // 查询今日预约数
    QString today = QDate::currentDate().toString("yyyy-MM-dd");
    performQuery(QString("SELECT COUNT(*) FROM appointment WHERE appointment_date = '%1'").arg(today),
                 todayAppointments, "todayAppointments");

    // 查询病历总数
    performQuery("SELECT COUNT(*) FROM medical_record", medicalRecordCount, "medicalRecordCount");

    // 更新时间戳
    lastUpdateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    // 发送更新信号
    emit statisticsUpdated(patientCount, doctorCount,
                           appointmentCount, medicineCount,
                           todayAppointments, medicalRecordCount);

    qDebug() << "Statistics updated - Patients:" << patientCount
             << "Doctors:" << doctorCount
             << "Appointments:" << appointmentCount
             << "Medicines:" << medicineCount
             << "Today Appointments:" << todayAppointments
             << "Medical Records:" << medicalRecordCount;
}

void StatisticsThread::performQuery(const QString &query, int &result, const QString &errorMsg)
{
    QSqlQuery sqlQuery(database);
    if (sqlQuery.exec(query)) {
        if (sqlQuery.next()) {
            result = sqlQuery.value(0).toInt();
        }
    } else {
        qDebug() << errorMsg << "query failed:" << sqlQuery.lastError().text();
        emit errorOccurred(errorMsg + ": " + sqlQuery.lastError().text());
    }
}
