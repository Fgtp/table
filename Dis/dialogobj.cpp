#include "dialogobj.h"
#include "ui_dialogobj.h"

DialogObj::DialogObj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogObj)
{
    ui->setupUi(this);
}

DialogObj::~DialogObj()
{
    delete ui;
    qDeleteAll(prs);
}

void DialogObj::on_buttonBox_accepted()
{
    MyObject *obj = new ObjNormalDist(0.);
    obj->setName(ui->lineObjName->text());
    foreach (Parameter* pr, prs)
    {
        obj->setParam(*pr);
    }

    emit addObject(obj);
    this->close();
}

void DialogObj::on_addParam_clicked()
{
    Parameter* pr = new Parameter;
    pr->name = ui->lineParamName->text();
    pr->sko = ui->skoSpinBox->value();
    pr->m = ui->mSpinBox->value();

    ui->lineParamName->clear();
    ui->skoSpinBox->setValue(0.);
    ui->mSpinBox->setValue(0.);

    prs.push_back(pr);

    int sz = ui->comboParams->count();
    ui->comboParams->insertItem(sz + 1, pr->name);
}

void DialogObj::on_buttonBox_rejected()
{
    this->close();
}
