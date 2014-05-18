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

public slots:

protected:
    virtual void closeEvent(QCloseEvent *);
    virtual void paintEvent(QPaintEvent *);

    virtual void mousePressEvent(QMouseEvent * e);
    virtual void mouseMoveEvent(QMouseEvent * e);

private slots:
    void accept();

private:
    void deletePreviousEditor();
    QRect getRect() const;

    QAction * acceptAction;

    IPictureEditor * pictureEditor;
    QPoint first;
    QPoint second;
};

#endif // TPICTURE_WIDGET_H
