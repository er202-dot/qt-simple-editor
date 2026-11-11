#ifndef REPLACE_H
#define REPLACE_H

#include <QDialog>

namespace Ui {
class Replace;
}

class Replace : public QDialog
{
    Q_OBJECT
public:
    explicit Replace(QWidget *parent = nullptr);
    ~Replace();

signals:
    // 查找
    void sendFind(QString target, bool caseSensitive, bool searchUp);
    // 单个替换
    void sendReplace(QString target, QString replaceText, bool caseSensitive, bool searchUp);
    // 全部替换
    void sendReplaceAll(QString target, QString replaceText, bool caseSensitive);

private slots:
    void on_btn_findNext_clicked();
    void on_btn_replace_clicked();
    void on_btn_replaceAll_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::Replace *ui;
};

#endif // REPLACE_H
