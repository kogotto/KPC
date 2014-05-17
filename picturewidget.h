#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QRect>

class IPictureEditor;

class TPictureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TPictureWidget( QWidget *parent = 0, Qt::WindowFlags f=0 );
    void setPictureEditor(IPictureEditor * pictureEditor);
    QImage getFramedImage();

protected:
    void closeEvent(QCloseEvent * e);
    void paintEvent(QPaintEvent *);

signals:
    void closeSignal();

private slots:
    void mousePressEvent( QMouseEvent *e );
    void mouseMoveEvent( QMouseEvent *e );
    void mouseReleaseEvent( QMouseEvent *e );

private:
    void setImage(QImage vimage);
    bool drawingFrame;
    bool frameDrawn;
    QPoint firstFramePoint;
    QPoint secondFramePoint;
    QRect frame;
    QImage image;
    IPictureEditor * pictureEditor;

};

#endif // IMAGEWIDGET_H
