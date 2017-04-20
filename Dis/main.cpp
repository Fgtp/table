#include "mainwindow.h"
#include <QApplication>
#include "learningmodul.h"
#include "turntable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time (NULL));
//    for(int i = 0; i < 1000; ++i )
//    {
        LearningModul l;
        l.Learn(0);
//    }
//     TurnTable t;
//     t.compute();
//    MainWindow w;
//    w.show();

    return a.exec();
}
