#ifndef DIALOGOBJ_H
#define DIALOGOBJ_H

#include <QDialog>
#include "object.h"

namespace Ui {
class DialogObj;
}

class DialogObj : public QDialog
{
    Q_OBJECT

public:
    explicit DialogObj(QWidget *parent = 0);
    ~DialogObj();

signals:
    void addObject(MyObject* obj);

private slots:
    void on_buttonBox_accepted();

    void on_addParam_clicked();

    void on_buttonBox_rejected();

private:
    Ui::DialogObj *ui;
    QVector<Parameter*> prs;
};


#endif // DIALOGOBJ_H
