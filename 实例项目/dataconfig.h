#ifndef DATACONFIG_H
#define DATACONFIG_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QVector>

class dataConfig : public QObject
{
    Q_OBJECT
public:

    explicit dataConfig();
    void init(int level);

    int*  array1 = nullptr;
signals:
};

#endif // DATACONFIG_H
