#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    data = NULL;
    objDial = NULL;
    connect(objDial, SIGNAL(addObject(MyObject*)),
            this, SLOT(insetObject(MyObject*)));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_panelBox_accepted()
{

}

void MainWindow::on_panelBox_rejected()
{

}

void MainWindow::on_addData_triggered()
{
    // Тестовая версия
    const int maxRow = 1000;
    const int maxColomn = 3;
    QStandardItemModel *model = new QStandardItemModel(maxRow, maxColomn, this);
    data = new double*[maxRow];
    for(int i = 0; i < maxRow; ++i)
    {
        data[i] = new double[maxRow];
        for(int j = 0; j < maxColomn; ++j)
        {
            QModelIndex idx = model->index(i, j);
            data[i][j] = i+j;
            model->setData(idx, data[i][j]);
        }
    }
    ui->tableLeardData->setModel(model);
}

void MainWindow::on_addObj_triggered()
{
    objDial = new DialogObj;
    objDial->exec();
    delete objDial;
    objDial = NULL;
    this->update();
}

void MainWindow::insetObject(MyObject *obj)
{
    _lmod.addObj(obj);
}
