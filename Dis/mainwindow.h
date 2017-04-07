#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QTabWidget>
#include <QGroupBox>
#include <QLayout>
#include <dialogobj.h>
#include <learningmodul.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_panelBox_accepted();

    void on_panelBox_rejected();

    void on_addData_triggered();

    void on_addObj_triggered();

    void insetObject(MyObject* obj);

private:

    double** data;
    QStandardItemModel *model;
    QTableWidget* _tableDataL;

    Ui::MainWindow *ui;
    DialogObj* objDial;
    LearningModul _lmod;
};

#endif // MAINWINDOW_H
