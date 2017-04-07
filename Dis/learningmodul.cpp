#include "learningmodul.h"


bool LearningModul::Learn(const int& n)
{
    if (n >= data.size())
    {
        qDebug() << "Указан ошибочный объект";
        return false;
    }

    int sz = 2;
    QVector<double> v(sz);
    for(int i = 0; i < 2; ++i)
    {
        v[0] = rand()%30 + (rand()%5) * cos(i);
        v[1] = rand()%30 + (rand()%5) * sin(i);

        for(int j = 0; j < data.size(); ++j)
            data[j]->compute(v);
    }

    compute(n);
    search(n);

    return true;
}

bool LearningModul::compute(const int &n)
{
    double sum = this->getSum(n);
    SignificanceTable t(4, 5, pres);
    int res = 0;
    double max = 0.;
    //Считаем знаменатель;
    for(int i = 0; i < t.size(); ++i)
    {
        double b = 1.;
        for(int j = 0; j < t[i].size(); ++j)
        {
            b *= (double) t[i][j] / pow(10, pres);
        }
        b *= data[n]->getAccFunction() * data[n]->getProb();
        if(max < b/(sum+b))
        {
            max = b/(sum+b);
            res = i;
        }
    }

    std::cout << "Result:" << std::endl;
    std::cout << "Prob = " << max << std::endl;
    for(int i = 0; i < data[n]->getSize(); ++i)
    {
        data[n]->setW(i, t[res][i]/pow(10, pres));
        std::cout << "w["<<i<<"] = " <<  data[n]->getW(i) << " ";
    }
    cout << endl;
    data[n]->setSum(sum);

    return true;
}

void LearningModul::analize(const int& n)
{
    delta(data[n]->getSize());
    for (int i = 0; i < data.size(); ++i)
    {
        if (i != n)
        {
            for (int j = 0; j < data[i]->getSize(); ++j)
            {
                double b = abs(data[i]->getM(j) - data[n]->getM(j)) - 2 * data[i]->getSko();
                if ( b < 0)
                    delta[j] += b;
            }
        }
    }
}

bool LearningModul::test()
{
    double sum = 0.;
    for(int i = 0; i < data.size(); ++i)
    {
        sum = getSum(i);
        double p = data[i]->P();

        std::cout << "Result: " << std::endl;
        std::cout<<"Object =" << i << std::endl;
        std::cout << "Prob = " << p/(sum + p) << std::endl;
        for(int j = 0; j < data[i]->getSize(); ++j)
        {
            std::cout << "w["<<j<<"] = " << data[i]->getW(j) << " ";
        }
        std::cout << std::endl;
    }
    return true;
}

void LearningModul::createData()
{
    int cnt = 3;
    int size = 4;

    for(int i = 1; i < cnt; ++i)
    {
        ObjNormalDist *ob = new ObjNormalDist((double) 1/size);
        ob->setSize(size);
        data.append(ob);
        for(int j = 0; j < size; ++j)
        {
            ob->setM(j, rand() % 15);
            ob->setW(j, 1/(double)size);
        }
        ob->setSko(10);
    }
}

void LearningModul::search(const int& n)
{
    const int max = 1000;
    const double e = 0.0000001;
    const double e2 = 0.00001;
    double st = 10;
    for(int i = 0; i < max; ++i)
    {
        double gr = grad(n);
        if(gr < e)
            return;
        double prob = data[n]->Pa();
        QVector<double> we;
        for(int j = 0; j < data[n]->getSize(); ++j)
        {
            we.append(data[n]->getW(j));
            double w = data[n]->getW(j) + st*gr;
            data[n]->setW(j, w);
        }
        data[n]->Norm();
        double p1 = data[n]->Pa();
        if(p1 - prob < 0)
        {
            double res = 0.;
            for(int j = 0; j < data[n]->getSize(); ++j)
            {
                we[j] -= data[n]->getW(j);
                res += _POW2(we[j]);
            }

            if(abs(prob - p1) < e2 && sqrt(res) < e2)
                break;
        }
    }
}

double LearningModul::grad(const int &n)
{
    if(n >= data.size())
        return 0.;
    double gr = 0.;
    for(int i = 0; i < data[n]->getSize(); ++i)
    {
        double p = data[n]->P() / data[n]->getW(i);
        gr += data[n]->getSum() * p
                /_POW2(data[n]->getSum() + data[n]->P());
    }

    return gr;
}

// Числитель апостреиорной вероятности
double LearningModul::aProb(const int &n)
{
    double res = 1.;

    for(int i = 0; i < data[n]->getSize(); ++i)
    {
        // Т.к. значение в.к. на данный момент считается постоянным
        // на всей обучащей выборе, то его можно вынести за скобки
//        res *= data[n]->getVal(i) * data[n]->getW(i);
    }
    res *= data[n]->getProb();

    return res;
}

// Знаменатель апостреиорной вероятности
double LearningModul::getSum(const int &n)
{
    double sum = 0.; // Считаем числитель
    for(int i = 0; i < data.size(); ++i)
    {
        if(i == n)
            continue;
        double b = 1.;
        for(int j = 0; j < data[i]->getSize(); ++j)
        {
            b *= (double) data[i]->getW(j);
        }
        sum +=b * data[i]->getProb() * data[i]->getAccFunction();
    }

    return sum;
}


void LearningModul::addObj(MyObject *obj)
{
    if(obj != NULL)
        data.push_back(obj);
}

const MyObject *LearningModul::getObj(const int &i)
{
    if(i < data.size())
        return data[i];
    return NULL;
}

