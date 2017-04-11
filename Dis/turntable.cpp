#include "turntable.h"

TurnTable::TurnTable()
{
    init();
}

TurnTable::~TurnTable()
{

}

void TurnTable::compute()
{
    bool fl = false;
    int c = 0;
    while(c < cnt)
    {
        for(int k = 0; k < column; ++k)
        {
            fl = true;
            while(fl)
            {
                QVector<double> pr(column);
                double sum = 0;
                for(int i = 0; i < column; ++i)
                {
                    for(int j = 0; j < row; ++j)
                    {
                        pr[i] += w[i][i]*function_G(et[k], et[j], sko);
                    }
                    sum  += pr[i];
                }
                QVector<double> err;
                for(int j = 0; j < column; ++j)
                {
                    err.push_back(ePap[k][j] - pr[j]/sum);
                }
                for(int i = 0; i < column; ++i)
                {
                    if(err[i] < pres && err[i] > -pres)
                    {
                        fl = false;
                    }
                    else
                    {
                        fl = true;
                        break;
                    }
                }
                for(int i = 0; i < column; ++i)
                {
                    for(int j = 0; j < row; ++j)
                    {
                        double t = w[j][i];
                        w[j][i] += st * err[i] * function_G(et[i], et[j], sko);
                        if(w[j][i] < 0)
                            w[j][i] = t;
                    }
                }
                norm();
            }
        }

        ++c;
        /*
        for(int m = row - 1; m>=0; ++m)
        {
            fl = true;
            QVector<double> pr(column);
            while(fl)
            {
                double sum = 0;
                for(int j = 0; j < column - 1; ++j)
                {
                    for(int k = 0; k < row; ++k)
                    {
                        pr[j] += objs[j]->getW(k)*objs[j]->getDist(objs[m], j);
                    }
                    sum += pr[j];
                }
                QVector<double> pap(column);
                for(int j = 0; j < column - 1; ++j)
                {
                    pap[j] = pr[j]/sum;
                    err.push_back(ePap[m][j] - pap[j]);
                }
                for(int j = 0; j < column -1; ++j)
                {
                    if(abs(err[j]) < pres)
                    {
                        fl = false;
                    }
                    else
                    {
                        fl = true;
                        break;
                    }
                }
                for(int j = 0; j < column - 1; ++j)
                {
                    for(int k = 0; k < row; ++k)
                    {
                        double t = objs[j]->getW(k);
                        double w = t + st*objs[j]->getDist(learnData[j], j);
                        if(w < 0)
                            w = t;
                        objs[j]->setW(j, w);
                    }
                }
                norm();
            }
        }
        */
    }
}

void TurnTable::init()
{
    column = 3;
    row = 3;
    sko = 100;
    for(int i = 0; i < 3; ++i)
    {
        ObjNormalDist* ptr = new ObjNormalDist(1/column);
        Parameter p;
        p.m = 1000 + i*1000;
        ptr->setParam(p);
        objs.push_back(ptr);
        ptr->setSko(100);
    }

    et.resize(column);
    et = {1000, 2000, 3000};

    ePap.resize(column);
    w.resize(column);
    for(int i = 0; i < row; ++i)
    {
        ePap[i].resize(row);
        w[i].resize(row);
        w[i] = {0.33, 0.33, 0.33};
    }

    ePap[0] = {0.60, 0.3, 0.1 };
    ePap[1] = {0.10, 0.7, 0.2 };
    ePap[2] = {0.25, 0.5, 0.25};

    pres = 0.0001;

    st = 2;
}

void TurnTable::norm()
{
    for(int i = 0; i < column; ++i)
    {
        double sum = 0;
        for(int j = 0; j < row; ++j)
        {
            sum += w[i][j];
        }
        for(int j = 0; j < row; ++j)
        {
            w[i][j] = w[i][j]/sum;
        }
    }
}

int TurnTable::getColumn() const
{
    return column;
}

void TurnTable::setColumn(const int &value)
{
    column = value;
}

int TurnTable::getRow() const
{
    return row;
}

void TurnTable::setRow(const int &value)
{
    row = value;
}

int TurnTable::getCnt() const
{
    return cnt;
}

QVector<MyObject *> TurnTable::getObjs() const
{
    return objs;
}

void TurnTable::setObjs(const QVector<MyObject *> &value)
{
    objs = value;
}

void TurnTable::pushObj(const MyObject &/*val*/)
{
    ObjNormalDist* cp = new ObjNormalDist(1);
    objs.push_back(cp);
}

double TurnTable::getPres() const
{
    return pres;
}

void TurnTable::setPres(double value)
{
    pres = value;
}

void TurnTable::setEPap(const QVector<QVector<double> > &value)
{
    ePap = value;
}

void TurnTable::setSt(double value)
{
    st = value;
}

double TurnTable::function_G(const double &x,
                             const double &m,
                             const double &sko)
{
    return exp(-_POW2(m - x)/(_POW2(sko)*2))/(sko * sqrt(2*M_PI));
}

void TurnTable::setCnt(const int &value)
{
    cnt = value;
}
