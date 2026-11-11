#include "replace.h"
#include "ui_replace.h"

Replace::Replace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Replace)
{
    ui->setupUi(this);
}

Replace::~Replace()
{
    delete ui;
}

void Replace::on_btn_findNext_clicked()
{
    QString findStr = ui->lineEdit_find->text();
    bool caseFlag = ui->chk_case->isChecked();
    bool up = ui->radio_up->isChecked();
    emit sendFind(findStr, caseFlag, up);
}

void Replace::on_btn_replace_clicked()
{
    QString findStr = ui->lineEdit_find->text();
    QString repStr = ui->lineEdit_replace->text();
    bool caseFlag = ui->chk_case->isChecked();
    bool up = ui->radio_up->isChecked();
    emit sendReplace(findStr, repStr, caseFlag, up);
}

void Replace::on_btn_replaceAll_clicked()
{
    QString findStr = ui->lineEdit_find->text();
    QString repStr = ui->lineEdit_replace->text();
    bool caseFlag = ui->chk_case->isChecked();
    emit sendReplaceAll(findStr, repStr, caseFlag);
}

void Replace::on_btn_cancel_clicked()
{
    this->close();
}
