#include "find.h"
#include "ui_find.h"

find::find(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::find)
{
    ui->setupUi(this);
}

find::~find()
{
    delete ui;
}
