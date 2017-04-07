#include "significancetable.h"


SignificanceTable::SignificanceTable(const uint &Nparam,
                                     const uint &step,
                                     const int &tt)
{
    t = pow(10,tt);

    // Вычисление размерности таблицы вес. коэф.
    uint res = CountCombination(Nparam, step);
    _table.resize(res);

    for(uint i = 0; i < res; ++i)
    {
        _table[i].resize(Nparam);
    }

    _st = (double)(t/step);
    _colomn = Nparam;
    _table[0][0] = t;
    CreateTable();
}

SignificanceTable::~SignificanceTable()
{
}

uint SignificanceTable::CountCombination(const uint &Nparam,
                                         const uint &step)
{
    uint res = 1;
    for(uint i = 1; i <= Nparam - 1; ++i)
    {
        res *= step+i;
        res /= i;
    }

    return res;
}

QVector<QVector<int> > SignificanceTable::getTable() const
{
    return this->_table;
}

QVector<int> SignificanceTable::getRow(const int &r) const
{
    if(r < _table.size())
        return _table[r];
    return QVector<int>(_colomn);
}

int SignificanceTable::size() const
{
    return _table.size();
}

void SignificanceTable::CreateTable()
{
    int i = 0;
    for(int j = _colomn - 1; _table[i][_colomn - 1] < t ; --j)
    {
        if(_table[i][j] >= _st)
        {
            for(int k = 0; k < j; ++k)
                _table[i + 1][k] = _table[i][k];
            if(j >= _colomn - 1)
            {
                int k = _colomn - 2;

                for(;_table[i + 1][k] < _st; --k);
                _table[i + 1][k] -= _st;
                _table[i + 1][k + 1] = _table[i][_colomn - 1] + _st;
            }
            else
            {
                _table[i + 1][j] = _table[i][j] - _st;
                _table[i + 1][j + 1] = _table[i][j + 1] + _st;
            }
            if(++i < _table.size() - 1)
                j = _colomn;
        }
    }

    for(QVector<QVector<int> >::iterator it = _table.begin(); it != _table.end();)
    {
        int cnt = 0;
        for (int i = 0; i < (*it).size(); ++i)
        {
            if((*it)[i] < 1)
                ++cnt;
        }
        if(cnt > 1 || _colomn - cnt < 2)
            _table.erase(it);
        else
            ++it;
    }
}
