#include "picturewidget.h"
#include <QPainter>
#include <QMouseEvent>
#include "pictureeditor.h"

TPictureWidget::TPictureWidget(QWidget *parent, Qt::WindowFlags flags) :
    QWidget(parent, flags),
    acceptAction(new QAction(this)) ,
    pictureEditor(0)
{
    acceptAction->setShortcut(Qt::Key_Space);
    connect(acceptAction, SIGNAL(triggered()),
            this, SLOT(accept()));
    addAction(acceptAction);
}

TPictureWidget::~TPictureWidget()
{
    deletePreviousEditor();
}

void TPictureWidget::setPictureEditor(IPictureEditor *pictureEditor)
{
    if (pictureEditor == 0){
        close();
    }

    deletePreviousEditor();

    this->pictureEditor = pictureEditor;
    resize(pictureEditor->getPicture().size());
    first = pictureEditor->getRect().topLeft();
    second = pictureEditor->getRect().bottomRight();
    update();
}

void TPictureWidget::closeEvent(QCloseEvent *)
{
    emit closeSignal();
}

void TPictureWidget::paintEvent(QPaintEvent *)
{
    if (pictureEditor == 0) {
        return;
    }

    QPainter painter(this);

    const QImage & picture = pictureEditor->getPicture();
    if (!picture.isNull()) {
        painter.drawImage(0, 0, picture);
    }

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    pen.setColor(Qt::yellow);
    painter.setPen(pen);

    painter.drawRect(getRect());
}

void TPictureWidget::mousePressEvent(QMouseEvent *e)
{
    if ( e->button() == Qt::LeftButton )
    {
        const int x = e->x();
        const int y = e->y();

        first.setX(x);
        first.setY(y);

        second = first;
    }
}

void TPictureWidget::mouseMoveEvent(QMouseEvent *e)
{
    const QImage & picture = pictureEditor->getPicture();

    int x = e->x();
    if ( x < 0 )
        x = 0;
    else if ( x > picture.size().width() )
        x = picture.size().width() - 2;

    int y = e->y();
    if ( y < 0 )
        y = 0;
    else if ( y > picture.size().height() )
        y = picture.size().height() - 2;

    second.setX(x);
    second.setY(y);
    update();
}

void TPictureWidget::accept()
{
    pictureEditor->setRect(getRect());
    pictureEditor->accept();

    IPictureEditor * nextPictureEditor = 0;
    emit needNextPicture(nextPictureEditor);
    setPictureEditor(nextPictureEditor);
}

void TPictureWidget::deletePreviousEditor()
{
    delete pictureEditor;
    pictureEditor = 0;
}

QRect TPictureWidget::getRect() const
{
    return QRect(first, second);
}
