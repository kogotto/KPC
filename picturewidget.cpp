#include "picturewidget.h"
#include <QPainter>
#include "pictureeditor.h"

TPictureWidget::TPictureWidget(QWidget *parent, Qt::WindowFlags flags) :
    QWidget(parent, flags),
    pictureEditor(0)
{
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
    pen.setWidth(2);
    pen.setColor(Qt::yellow);
    painter.setPen(pen);

    painter.drawRect(pictureEditor->getRect());
}

void TPictureWidget::deletePreviousEditor()
{
    delete pictureEditor;
    pictureEditor = 0;
}
