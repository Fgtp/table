#ifndef LEARNINGMODUL_H
#define LEARNINGMODUL_H

#include "significancetable.h"
#include "object.h"
#include <QTimer>
#include <ctime>
#include <QMap>
#include <iostream>

class LearningModul
{
public:
    LearningModul()
    {
        pres = 3;
        createData();
    }
    ~LearningModul()
    {
        qDeleteAll(data);
    }
    bool Learn(const int &n);

    bool compute(const int& n);
    void analize(const int &n);
    double getSameParameter(const int &n);

    bool test();
    void addObj(MyObject* obj);
    void createData();
    void search(const int &n);

    double grad(const int& n);
    double aProb(const int& n);
    double getSum(const int &n);

    int size() const;
    const MyObject* getObj(const int& i);


private:
    QVector<MyObject*> data;
    QVector<double> delta;
    int pres;
};

#endif // LEARNINGMODUL_H
