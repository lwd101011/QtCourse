#ifndef STATISTICSTHREAD_H
#define STATISTICSTHREAD_H

#include <QThread>
#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QSqlQuery>
#include "idatabase.h"

class StatisticsThread : public QThread
{
    Q_OBJECT

public:
    explicit StatisticsThread(QObject *parent = nullptr);
    ~StatisticsThread();

    // 启动统计线程
    void startStatistics();
    // 停止统计线程
    void stopStatistics();

    // 获取统计数据
    int getPatientCount() const { return patientCount; }
    int getDoctorCount() const { return doctorCount; }
    int getAppointmentCount() const { return appointmentCount; }
    int getMedicineCount() const { return medicineCount; }
    int getTodayAppointments() const { return todayAppointments; }
    int getMedicalRecordCount() const { return medicalRecordCount; }
    QString getLastUpdateTime() const { return lastUpdateTime; }

signals:
    // 统计数据更新信号
    void statisticsUpdated(int patientCount, int doctorCount,
                           int appointmentCount, int medicineCount,
                           int todayAppointments, int medicalRecordCount);
    void errorOccurred(const QString &message);

protected:
    void run() override;

private:
    void calculateStatistics();
    void performQuery(const QString &query, int &result, const QString &errorMsg);

    bool isRunning;
    QTimer *timer;
    int patientCount;
    int doctorCount;
    int appointmentCount;
    int medicineCount;
    int todayAppointments;
    int medicalRecordCount;
    QString lastUpdateTime;

    // 数据库连接
    QSqlDatabase database;
};

#endif // STATISTICSTHREAD_H
