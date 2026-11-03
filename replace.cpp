#include "replace.h"
#include "ui_replace.h"

replace::replace(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::replace)
{
    ui->setupUi(this);
}

replace::~replace()
{
    delete ui;
}
