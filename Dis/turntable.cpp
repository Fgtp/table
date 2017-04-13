#include "turntable.h"
#include <iostream>

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
        for(int k = 0; k < row; ++k)
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
                        pr[i] += w[j][i]*function_G(et[k], et[j], sko);
                    }
                    sum  += pr[i];
                }
                QVector<double> err;
                for(int j = 0; j < column; ++j)
                {
                    std::cout << "P["<<j<<"] = " << pr[j]/sum << "  ";
                    err.push_back(ePap[k][j] - pr[j]/sum);
                }
                std::cout << std::endl;
                foreach (double er, err)
                {
                    if(er < pres && er > -pres)
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
                        w[j][i] += st * err[i] * function_G(et[k], et[j], sko);
                        if(w[j][i] < 0)
                            w[j][i] = t;
                    }
                }
                norm();
            }
        }
        ++c;
        st /= 2;
    }
}

void TurnTable::init()
{
    column = 3;
    row = 1;
    sko = 100;
    w.resize(row);
    for(int i = 0; i < row; ++i)
    {
        w[i].resize(column);
        for(int j = 0; j < column; ++j)
        {
            w[i][j] = 1/(double)column;
        }
    }

    et.resize(row);
    et = {1000};

    ePap.resize(row);
    for(int i = 0; i < row; ++i)
    {
        ePap[i].resize(column);
    }

    ePap[0] = {0.60, 0.3, 0.1 };

    pres = 0.005;

    st = 2;
}

void TurnTable::norm()
{
    for(int j = 0; j < row; ++j)
    {
        double sum = 0;
        for(int i = 0; i < column; ++i)
        {
            sum += w[j][i];
        }
        for(int i = 0; i < column; ++i)
        {
            w[j][i] /= sum;
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
