#ifndef SIGNIFICANCETABLE_H
#define SIGNIFICANCETABLE_H

#include <QVector>
#include <QDebug>
#include <QList>
#include <iostream>
#include <cmath>

using namespace std;

// Таблица всех возможных значений весовых коэффициентов
class SignificanceTable
{
public:
    SignificanceTable(const uint& Nparam,
                      const uint &step, const int &tt);
    ~SignificanceTable();

    uint CountCombination(const uint& Nparam,
                          const uint &step);
    QVector<QVector<int> > getTable() const;
    QVector<int>  getRow(const int& r) const;
    QVector<int> operator [] (const int& i)
    {
        return _table[i];
    }

    int size() const;

private:
    QVector<QVector<int> > _table;
    uint _colomn;
    double _st;

    int t;
    void CreateTable();

};

#endif // SIGNIFICANCETABLE_H
