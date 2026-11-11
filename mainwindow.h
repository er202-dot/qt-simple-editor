#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "linenumberarea.h"

#include <QMainWindow>
#include <QLabel>
#include <QCloseEvent>
#include <QClipboard>
#include <QFontDialog>
#include <QColorDialog>
#include <QTextCharFormat>
#include <QTextCursor>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_actionAbout_triggered();
    void on_actionFind_triggered();
    void on_actionReplace_triggered();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered(bool fromSave = false);

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionRedo_triggered();

    void on_actionSelectAll_triggered();

    // ========== 状态刷新槽函数（用来控制按钮灰亮） ==========
    void updateCutCopyState(bool hasSelect);
    void updateUndoState(bool canUndo);
    void updateRedoState(bool canRedo);
    void updatePasteState();


    void on_actionUndo_triggered();

    void on_actionPaste_triggered();

    void on_actionFont_triggered();

    void on_actionFontColor_triggered();

    void on_actionBgColor_triggered();

    // 同步行号区域宽度、重绘行号
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);

    void on_actionShowLinenumber_triggered(bool checked);

    void on_actionTextWrap_triggered(bool checked);

    void on_actionToolbar_triggered(bool checked);

    void on_actionStatusbar_triggered(bool checked);

    void on_actionExit_triggered();
    void doFindText(QString target, bool caseSensitive, bool searchUp);
    void doReplace(QString target, QString replaceText, bool caseSensitive, bool searchUp);
    void doReplaceAll(QString target, QString replaceText, bool caseSensitive);
    void updateStatusBarInfo();

private:
    Ui::MainWindow *ui;

    QLabel statusCursorLabel;
    QLabel statusLabel;
    QString currentFilePath;

    QClipboard *m_clipboard;

    bool isModified;

    bool maybeSave();
    LineNumberArea *m_lineArea;

    QTextCursor m_searchCursor; // 记录查找光标，连续查找用
};
#endif // MAINWINDOW_H
