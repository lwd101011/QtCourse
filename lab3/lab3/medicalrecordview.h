#ifndef MEDICALRECORDVIEW_H
#define MEDICALRECORDVIEW_H

#include <QObject>

class medicalrecordview : public QObject
{
    Q_OBJECT
public:
    explicit medicalrecordview(QObject *parent = nullptr);

signals:
};

#endif // MEDICALRECORDVIEW_H
