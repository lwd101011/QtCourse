#ifndef APPOINTMENTVIEW_H
#define APPOINTMENTVIEW_H

#include <QObject>

class appointmentview : public QObject
{
    Q_OBJECT
public:
    explicit appointmentview(QObject *parent = nullptr);

signals:
};

#endif // APPOINTMENTVIEW_H
