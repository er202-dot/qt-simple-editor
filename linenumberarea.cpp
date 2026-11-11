#include "linenumberarea.h"
#include <QPainter>
#include <QTextBlock>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>

LineNumberArea::LineNumberArea(QPlainTextEdit *editor)
    : QWidget(editor), m_editor(editor)
{

}

int LineNumberArea::areaWidth() const
{
    int digits = 1;
    int max = qMax(1, m_editor->blockCount());
    while (max >= 10)
    {
        max /= 10;
        digits++;
    }
    int space = 3 + m_editor->fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
    return space;
}

void LineNumberArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(event->rect(), QColor(240,240,240));

    // ✅ 从 document 获取第一个文本块（修复 firstBlock 报错）
    QTextBlock block = m_editor->document()->firstBlock();
    int blockNumber = block.blockNumber();

    QRect viewRect = m_editor->viewport()->rect();
    auto layout = m_editor->document()->documentLayout();

    painter.setPen(QColor(80,80,80));
    while (block.isValid())
    {
        // ✅ 使用 documentLayout 的公开接口获取block矩形，不再调用protected函数！
        QRectF blockRect = layout->blockBoundingRect(block);
        int bTop = qRound(blockRect.top());
        int bBottom = qRound(blockRect.bottom());

        if (bBottom >= viewRect.top() && bTop <= viewRect.bottom())
        {
            painter.drawText(0, bTop, this->width()-4, m_editor->fontMetrics().height(),
                             Qt::AlignRight, QString::number(blockNumber+1));
        }
        block = block.next();
        blockNumber ++;
    }
}
