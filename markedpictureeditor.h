#ifndef MARKEDPICTUREEDITOR_H
#define MARKEDPICTUREEDITOR_H

#include "pictureeditor.h"

class TMarkedPicture;

class TMarkedPictureEditor:
        public IPictureEditor
{
public:
    TMarkedPictureEditor(TMarkedPicture * picture);

    virtual const QImage & getPicture() const;
    virtual void accept();

private:
    TMarkedPicture * picture;
};

#endif // MARKEDPICTUREEDITOR_H
