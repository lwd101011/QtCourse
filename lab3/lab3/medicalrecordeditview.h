#ifndef MEDICALRECORDEDITVIEW_H
#define MEDICALRECORDEDITVIEW_H

#include <QObject>

class medicalrecordeditview : public QObject
{
    Q_OBJECT
public:
    explicit medicalrecordeditview(QObject *parent = nullptr);

signals:
};

#endif // MEDICALRECORDEDITVIEW_H
