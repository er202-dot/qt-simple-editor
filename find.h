#ifndef FIND_H
#define FIND_H

#include <QDialog>

namespace Ui {
class Find;
}

class Find : public QDialog
{
    Q_OBJECT
public:
    explicit Find(QWidget *parent = nullptr);
    ~Find();

    // 自定义信号：把查找参数传给主窗口
signals:
    void sendFindInfo(QString targetText, bool caseSensitive, bool searchUp);

private slots:
    // 【查找下一个】按钮点击槽函数
    void on_btn_findNext_clicked();
    // 【取消】按钮点击槽函数
    void on_btn_cancel_clicked();

private:
    Ui::Find *ui;
};

#endif // FIND_H
