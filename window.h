#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>

class TWindow : public QLabel
{
    Q_OBJECT
public:
    explicit TWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);

signals:

public slots:

protected:
    virtual void paintEvent(QPaintEvent *);

};

#endif // WINDOW_H
