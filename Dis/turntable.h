#ifndef TURNTABLE_H
#define TURNTABLE_H

#define _USE_MATH_DEFINES

#include <QVector>
#include <QDebug>
#include <math.h>
#include "object.h"

class TurnTable
{
public:
    TurnTable();
    ~TurnTable();

    void compute();
    void init();
    void norm();

    int getColumn() const;
    void setColumn(const int &value);

    int getRow() const;
    void setRow(const int &value);

    int getCnt() const;
    void setCnt(const int &value);

    QVector<MyObject *> getObjs() const;
    void setObjs(const QVector<MyObject *> &value);

    void pushObj(const MyObject &);

    double getPres() const;
    void setPres(double value);
    
    void setEPap(const QVector<QVector<double> > &value);

    void setSt(double value);

    double function_G(const double &x,
                      const double &m,
                      const double &sko);

private:
    
    int cnt;
    int row;
    int column;
    double pres;
    double st;
    double sko;
    QVector<QVector<double> >w;
    QVector<MyObject* > objs;
    QVector<double> et;
    QVector<QVector<double> >ePap;
    QVector<double> learnData;
};

#endif // TURNTABLE_H
