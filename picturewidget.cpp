#include "picturewidget.h"
#include <QPainter>
#include <QMouseEvent>
#include "pictureeditor.h"

TPictureWidget::TPictureWidget(QWidget *parent, Qt::WindowFlags flags) :
    QWidget(parent, flags),
    acceptAction(new QAction(this)),
    moveLeftAction(new QAction(this)),
    moveDownAction(new QAction(this)),
    moveUpAction(new QAction(this)),
    moveRightAction(new QAction(this)),
    decreaseWidthAction(new QAction(this)),
    increaseHeightAction(new QAction(this)),
    decreaseHeightAction(new QAction(this)),
    increaseWidthAction(new QAction(this)),
    pictureEditor(0)
{
    acceptAction->setShortcut(Qt::Key_Space);
    connect(acceptAction, SIGNAL(triggered()),
            this, SLOT(accept()));
    addAction(acceptAction);

    moveLeftAction->setShortcut((Qt::Key_H));
    connect(moveLeftAction, SIGNAL(triggered()),
            this, SLOT(moveRectLeft()));
    addAction(moveLeftAction);

    moveDownAction->setShortcut((Qt::Key_J));
    connect(moveDownAction, SIGNAL(triggered()),
            this, SLOT(moveRectDown()));
    addAction(moveDownAction);

    moveUpAction->setShortcut((Qt::Key_K));
    connect(moveUpAction, SIGNAL(triggered()),
            this, SLOT(moveRectUp()));
    addAction(moveUpAction);

    moveRightAction->setShortcut((Qt::Key_L));
    connect(moveRightAction, SIGNAL(triggered()),
            this, SLOT(moveRectRight()));
    addAction(moveRightAction);

    decreaseWidthAction->setShortcut((Qt::Key_Y));
    connect(decreaseWidthAction, SIGNAL(triggered()),
            this, SLOT(decreaseRectWidth()));
    addAction(decreaseWidthAction);

    increaseHeightAction->setShortcut((Qt::Key_U));
    connect(increaseHeightAction, SIGNAL(triggered()),
            this, SLOT(increaseRectHeight()));
    addAction(increaseHeightAction);

    decreaseHeightAction->setShortcut((Qt::Key_I));
    connect(decreaseHeightAction, SIGNAL(triggered()),
            this, SLOT(decreaseRectHeight()));
    addAction(decreaseHeightAction);

    increaseWidthAction->setShortcut((Qt::Key_O));
    connect(increaseWidthAction, SIGNAL(triggered()),
            this, SLOT(increaseRectWidth()));
    addAction(increaseWidthAction);
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

    const QRect & rect = pictureEditor->getRect();
    if (rect.isNull()) {
        first = QPoint();
        second = QPoint();
    } else {
        first = rect.topLeft();
        second = rect.bottomRight();
    }

    setWindowTitle(pictureEditor->getName());
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
    if ((e->buttons() & Qt::LeftButton) == 0)  {
        return;
    }

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
    if (noRect()) {
        return;
    }

    pictureEditor->setRect(getRect());
    pictureEditor->accept();
    emit changed();

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
    const int left = std::min(first.x(), second.x());
    const int top = std::min(first.y(), second.y());
    const int width = std::abs(first.x() - second.x());
    const int height = std::abs(first.y() - second.y());

    return QRect(left, top, width, height);
}

bool TPictureWidget::noRect() const
{
    QPoint rectSize = first - second;
    bool tooClose = (abs(rectSize.x()) < 2) || (abs(rectSize.y()) < 2);
    return (first.isNull() && second.isNull()) || tooClose;
}

void TPictureWidget::moveRect(QPoint delta) {
    if (noRect()) {
        return;
    }

    QPoint newFirst = first + delta;
    QPoint newSecond = second + delta;
    QRect pictureRect = getPictureRect();
    if (pictureRect.contains(newFirst) && pictureRect.contains(newSecond)) {
        first += delta;
        second += delta;
        update();
    }
}

void TPictureWidget::resizeRect(QPoint delta)
{
    if (noRect()) {
        return;
    }

    QRect newRect(first, second);
    newRect.setBottomRight(newRect.bottomRight() + delta);
    if (getPictureRect().contains(newRect)) {
        int & bottom = first.y() > second.y() ? first.ry() : second.ry();
        int & right = first.x() > second.x() ? first.rx() : second.rx();

        bottom += delta.y();
        right += delta.x();
    }
    update();
}

QRect TPictureWidget::getPictureRect() const
{
    return QRect(QPoint(0,0), pictureEditor->getPicture().size());
}

