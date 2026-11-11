#include "find.h"
#include "ui_find.h"

Find::Find(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Find)
{
    ui->setupUi(this);
}

Find::~Find()
{
    delete ui;
}

// 查找下一个按钮槽
void Find::on_btn_findNext_clicked()
{
    QString text = ui->lineEdit_find->text();
    bool caseCheck = ui->chk_case->isChecked();
    bool up = ui->radio_up->isChecked(); // 选中向上就是true，向下false
    // 发射信号，传给主窗口
    emit sendFindInfo(text, caseCheck, up);
}

// 取消按钮
void Find::on_btn_cancel_clicked()
{
    this->close();
}
