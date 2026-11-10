#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QCloseEvent>
#include <QClipboard>

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

private:
    Ui::MainWindow *ui;

    QLabel statusCursorLabel;
    QLabel statusLabel;
    QString currentFilePath;

    QClipboard *m_clipboard;

    bool isModified;

    bool maybeSave();
};
#endif // MAINWINDOW_H
