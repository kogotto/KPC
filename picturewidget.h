#ifndef TPICTURE_WIDGET_H
#define TPICTURE_WIDGET_H

#include <QWidget>
#include <QAction>

class IPictureEditor;

class TPictureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TPictureWidget(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~TPictureWidget();
    void setPictureEditor(IPictureEditor * pictureEditor);

signals:
    void closeSignal();
    void needNextPicture(IPictureEditor *& nextPicture);
    void changed();

public slots:

protected:
    virtual void closeEvent(QCloseEvent *);
    virtual void paintEvent(QPaintEvent *);

    virtual void mousePressEvent(QMouseEvent * e);
    virtual void mouseMoveEvent(QMouseEvent * e);

private slots:
    void accept();

    void moveRectLeft() {
        moveRect(QPoint(-1,0));
    }

    void moveRectDown() {
        moveRect(QPoint(0,1));
    }

    void moveRectUp() {
        moveRect(QPoint(0,-1));
    }

    void moveRectRight() {
        moveRect(QPoint(1,0));
    }

    void decreaseRectWidth() {
        resizeRect(QPoint(-1,0));
    }

    void increaseRectHeight() {
        resizeRect(QPoint(0,1));
    }

    void decreaseRectHeight() {
        resizeRect(QPoint(0,-1));
    }

    void increaseRectWidth() {
        resizeRect(QPoint(1,0));
    }

private:
    void deletePreviousEditor();
    QRect getRect() const;
    bool noRect() const;

    void moveRect(QPoint delta);
    void resizeRect(QPoint delta);

    QRect getPictureRect() const;

    QAction * acceptAction;

    QAction * moveLeftAction;
    QAction * moveDownAction;
    QAction * moveUpAction;
    QAction * moveRightAction;

    QAction * decreaseWidthAction;
    QAction * increaseHeightAction;
    QAction * decreaseHeightAction;
    QAction * increaseWidthAction;

    IPictureEditor * pictureEditor;
    QPoint first;
    QPoint second;
};

#endif // TPICTURE_WIDGET_H
