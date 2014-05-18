#ifndef PICTUREEDITOR_H
#define PICTUREEDITOR_H

#include <QRect>

class QImage;

class IPictureEditor
{
public:
    virtual ~IPictureEditor();
    virtual const QImage & getPicture() const = 0;

    void setRect(const QRect & rect) {
        this->rect = rect;
    }

    const QRect & getRect() const {
        return rect;
    }

    virtual const QString & getName() const = 0;

    virtual void accept() = 0;

private:
    QRect rect;

};

#endif // PICTUREEDITOR_H
