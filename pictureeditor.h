#ifndef PICTUREEDITOR_H
#define PICTUREEDITOR_H

#include <QImage>

class IPictureEditor
{
public:
    IPictureEditor(){}

    explicit IPictureEditor(const QImage & picture):
        picture(picture)
    {}

    const QImage & getPicture() const {
        return picture;
    }


private:
    QImage picture;

};

#endif // PICTUREEDITOR_H
