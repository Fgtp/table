#ifndef TURNTABLE_H
#define TURNTABLE_H

#include <QVector>
#include <QDebug>
#include <cmath>
#include "object.h"

class TurnTable
{
public:
    TurnTable();
    ~TurnTable();

    void compute();
    void init();

    int getColumn() const;
    void setColumn(const int &value);

    int getRow() const;
    void setRow(const int &value);

    int getCnt() const;
    void setCnt(const int &value);

    QVector<MyObject *> getObjs() const;
    void setObjs(const QVector<MyObject *> &value);

    void pushObj(const MyObject &);

    double getE() const;
    void setE(double value);

private:

    int cnt;
    int row;
    int column;
    double pres;
    QVector<MyObject* > objs;
    QVector<double> ePap;
    QVector<double> learnData;
};

#endif // TURNTABLE_H
