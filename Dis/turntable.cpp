#include "turntable.h"

TurnTable::TurnTable()
{

}

TurnTable::~TurnTable()
{

}

void TurnTable::compute()
{

    for(int i = 0; i < cnt; ++i)
    {
        QVector<double> pr(column);
        do
        {
            double sum = 0;
            for(int j = 0; j < column - 1; ++j)
            {
                for(int k = 0; k < row; ++k)
                {
                    pr[j] = pr[j] + objs[j]->getW(k)*objs[j]->getDist(learnData[j][i], j);
                }
                sum += pr[j];
            }
            QVector<double> pap(column);
            for(int j = 0; j < column - 1; ++j)
            {
                pap[j] = pr[j]/sum;
                if(abs(pap[j] - ePap[j]) < e);
            }

        }while(true);
    }
}

void TurnTable::init()
{

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

void TurnTable::setCnt(const int &value)
{
    cnt = value;
}
