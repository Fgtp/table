#include "object.h"

double MyObject::_sko = 0;

MyObject::MyObject(const double &pr)
{
    _prob = pr;
    _accF = 0.;
    _sum = 0.;
}

void MyObject::setSize(const int &s)
{
    if(_params.size() < s)
    {
        for(int i = 0; i < s; ++i)
        {
            _params.append(new Parameter);
        }
    }
}

int MyObject::getSize() const
{
    return _params.size();
}

double MyObject::getProb() const
{
    return _prob;
}

void MyObject::setProb(const double& value)
{
    _prob = value;
}

Parameter *MyObject::getParam(const int &pos) const
{
    if(_params.size() > pos)
        return NULL;
    return _params[pos];
}

bool MyObject::setM(const int &pr, const double &v)
{
    if(_params.size() > pr && _params[pr] != NULL)
    {
        _params[pr]->m = v;
        return true;
    }
    return false;

}

void MyObject::setSko(const double &v)
{
    _sko = v;
}

void MyObject::setParam(const Parameter &pr)
{
    Parameter* p = new Parameter;
    *p = pr;
    _params.push_back(p);
}

bool MyObject::setW(const int &pr, const double &v)
{
    if(_params.size() > pr && _params[pr] != NULL)
    {
        _params[pr]->w = v;
        return true;
    }
    return false;

}

double MyObject::getM(const int &pr) const
{
    if(_params.size() > pr  && _params[pr] != NULL)
        return _params[pr]->m;
    return 0.;
}

double MyObject::getSko()
{
    return _sko;
}


void MyObject::compute(const QVector<double> &v)
{
    double res = 1.;
    for(int i = 0; i < v.size(); ++i)
    {
        res *= getDist(v[i], i);
    }
    _accF += res;
}

double MyObject::getW(const int &pr) const
{
    if(_params.size() > pr && _params[pr] != NULL)
        return _params[pr]->w;
    return 0.;
}

double MyObject::getAccFunction() const
{
    return _accF;
}

double MyObject::P() const
{
    double buf = 1.;
    for(int i = 0; i < _params.size(); ++i)
    {
        buf *= _params[i]->w;
    }
    return _prob * _accF  * buf;
}

double MyObject::Pa() const
{
    return P()/(_sum + P());
}

void MyObject::Norm()
{
    double sum = 0.;
    for(int i = 0; i < _params.size(); ++i)
        sum += _params[i]->w;
    for(int i = 0; i < _params.size(); ++i)
         _params[i]->w /= sum;
}

QString MyObject::getName() const
{
    return _name;
}

void MyObject::setName(const QString &name)
{
    _name = name;
}

double MyObject::getSum() const
{
    return _sum;
}

void MyObject::setSum(const double& aProb)
{
    _sum = aProb;
}

