#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H
#include <QWidget>
#include <QPlainTextEdit>

class LineNumberArea : public QWidget
{
    Q_OBJECT
public:
    explicit LineNumberArea(QPlainTextEdit *editor);
    int areaWidth() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPlainTextEdit *m_editor;
};

#endif // LINENUMBERAREA_H
