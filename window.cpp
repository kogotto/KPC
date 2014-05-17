#include "window.h"
#include <QPainter>

TWindow::TWindow(QWidget *parent, Qt::WindowFlags flags) :
    QLabel(parent, flags)
{
}

void TWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.drawRect(0, 0, 100, 200);
}
