#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "about.h"
#include "find.h"
#include "replace.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QStringConverter>
#include <QPlainTextEdit>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Simple文本编辑器");

    statusLabel.setMaximumWidth(150);
    statusLabel.setText("length:"+QString::number(0)+"  lines:"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCursorLabel.setMaximumWidth(150);
    statusCursorLabel.setText("Lh:"+QString::number(0)+"  Col:"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author=new QLabel(ui->statusbar);
    author->setText(tr("卢欢欢"));
    ui->statusbar->addPermanentWidget(author);

    currentFilePath = "";
    isModified = false;

    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, this, [=](){
        isModified = true;
    });

    m_clipboard = QApplication::clipboard();
    // ========= 绑定QPlainTextEdit自带信号，刷新按钮状态 =========
    // 选中文字变化 → 控制剪切、复制
    connect(ui->plainTextEdit, &QPlainTextEdit::copyAvailable,
            this, &MainWindow::updateCutCopyState);
    // 可撤销状态变化 → 撤销按钮
    connect(ui->plainTextEdit, &QPlainTextEdit::undoAvailable,
            this, &MainWindow::updateUndoState);
    // 可恢复状态变化 → 恢复按钮
    connect(ui->plainTextEdit, &QPlainTextEdit::redoAvailable,
            this, &MainWindow::updateRedoState);
    // 剪贴板内容变化 → 刷新粘贴按钮
    connect(m_clipboard, &QClipboard::dataChanged,
            this, &MainWindow::updatePasteState);

    // 【初始化界面：一开始全部符合要求，灰色】
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::maybeSave()
{
    if (!isModified)
    {
        return true;
    }
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("提示"),
                                                           tr("文档已修改，是否保存更改？"),
                                                           QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    if (ret == QMessageBox::Save)
    {
        on_actionSave_triggered();
        return true;
    }
    else if (ret == QMessageBox::Discard)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::on_actionAbout_triggered()
{
    about dlg;
    dlg.exec();
}

void MainWindow::on_actionFind_triggered()
{
    class find dlg;
    dlg.exec();
}

void MainWindow::on_actionReplace_triggered()
{
    class replace dlg;
    dlg.exec();
}

void MainWindow::on_actionNew_triggered()
{
    if (!maybeSave())
    {
        return;
    }
    ui->plainTextEdit->clear();
    currentFilePath = "";
    isModified = false;
    this->setWindowTitle("Simple文本编辑器 - 新建文档");
}

void MainWindow::on_actionOpen_triggered()
{
    if (!maybeSave())
    {
        return;
    }
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("打开文件"),
                                                "",
                                                tr("文本文件(*.txt);;所有文件(*.*)"));

    if (path.isEmpty())
        return;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("打开失败"), tr("无法打开文件：") + file.errorString());
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);
    QString content = in.readAll();
    ui->plainTextEdit->setPlainText(content);
    file.close();

    currentFilePath = path;
    isModified = false;
    setWindowTitle("Simple文本编辑器 - " + path);
}

void MainWindow::on_actionSave_triggered()
{
    if (currentFilePath.isEmpty())
    {
        on_actionSaveAs_triggered(true);
        return;
    }

    QFile file(currentFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("保存失败"), tr("无法写入文件：") + file.errorString());
        return;
    }
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    out << ui->plainTextEdit->toPlainText();
    file.close();
    isModified = false;
    QMessageBox::information(this, tr("提示"), tr("保存成功！"));
}

void MainWindow::on_actionSaveAs_triggered(bool fromSave)
{
    QString path = QFileDialog::getSaveFileName(this,
                                                tr("另存为"),
                                                "",
                                                tr("文本文件(*.txt);;所有文件(*.*)"));
    if (path.isEmpty())
        return;

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("保存失败"), tr("无法写入文件：") + file.errorString());
        return;
    }
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    out << ui->plainTextEdit->toPlainText();
    file.close();

    currentFilePath = path;
    isModified = false;
    setWindowTitle("Simple文本编辑器 - " + path);
    if(fromSave)
    {
        QMessageBox::information(this, tr("提示"), tr("保存成功！"));
    }
    else
    {
        QMessageBox::information(this, tr("提示"), tr("另存成功！"));
    }
}

void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}


void MainWindow::on_actionSelectAll_triggered()
{
    ui->plainTextEdit->selectAll();
}

// 剪切、复制按钮：hasSelect=true 有选中文字，可用
void MainWindow::updateCutCopyState(bool hasSelect)
{
    ui->actionCut->setEnabled(hasSelect);
    ui->actionCopy->setEnabled(hasSelect);
}

// 撤销按钮
void MainWindow::updateUndoState(bool canUndo)
{
    ui->actionUndo->setEnabled(canUndo);
}

// 恢复按钮
void MainWindow::updateRedoState(bool canRedo)
{
    ui->actionRedo->setEnabled(canRedo);
}

// 粘贴按钮：判断剪贴板有没有文本内容
void MainWindow::updatePasteState()
{
    bool hasText = !m_clipboard->text().isEmpty();
    ui->actionPaste->setEnabled(hasText);
}


