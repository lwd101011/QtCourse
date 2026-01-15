#ifndef MEDICINEVIEW_H
#define MEDICINEVIEW_H

#include <QObject>

class medicineview : public QObject
{
    Q_OBJECT
public:
    explicit medicineview(QObject *parent = nullptr);

signals:
};

#endif // MEDICINEVIEW_H
