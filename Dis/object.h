#ifndef OBJECT_H
#define OBJECT_H

#define _USE_MATH_DEFINES

#include <QVector>
#include <QMap>
#include <QDebug>
#include <math.h>
#include <QString>

#define _POW2(x)  ((x)*(x))

struct Parameter
{
    QString name;

    double sko; // Среднеквадратичное отклонение
    double m;   // Мат. ожидание

    double w;
};


class MyObject
{
public:
    MyObject(const double& pr);
    virtual ~MyObject()
    {
        qDeleteAll(_params);
    }

    void setSize(const int& s);
    int getSize() const;
    Parameter *getParam(const int &pos) const;

    double getProb() const;
    void setProb(const double &value);

    void setName(const QString &name);
    bool setM(const int& pr, const double& v);
    bool setW(const int& pr, const double &v);
    static void setSko(const double& v);
    void setParam(const Parameter &pr);
    void setSum(const double& aProb);

    QString getName() const;
    double getM(const int& pr) const;
    static double getSko();
    double getSum() const;
    double getW(const int& pr) const;
    double getAccFunction() const;

    double P() const;

    double Pa() const;
    void Norm();

    void compute(const QVector<double> &v);
    // Плотность распределение
    virtual double getDist(const double& x, const int& p) = 0;
    // Производная плотности распределения
    virtual double Der(const int& p) = 0;

private:

    static double _sko;
    QString _name; // Название объекта
    double _prob; // Априорная вероятность
    double _sum; // Cумма вероятностей
    double _accF;  // Накопительная функция
    QVector<Parameter*> _params; //Вектор эталонных параметров
};


class ObjNormalDist : public MyObject
{
public:
    ObjNormalDist(const double& pr) : MyObject(pr){}
    virtual ~ObjNormalDist(){}

    virtual double getDist(const double& x, const int& p)
    {
        if(abs(0 - getSko()) > 1E-8)
            return exp(-_POW2(getM(p) - x)/(_POW2(getSko())*2))/(getSko() * sqrt(2*M_PI));
        return 0.;
    }

    virtual double Der(const int& p)
    {
        double res = 1.;
        for(int i = 0; i < this->getSize(); ++i)
        {
            if(p != i)
            {
                res *= this->getAccFunction()*this->getW(i);
            }
        }
        return res * this->getProb();
    }
};



#endif // OBJECT_H
