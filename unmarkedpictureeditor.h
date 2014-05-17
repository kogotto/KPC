#ifndef UNMARKEDPICTUREEDITOR_H
#define UNMARKEDPICTUREEDITOR_H

#include "pictureeditor.h"

class TUnmarkedPicture;
class TPicturesProject;

class TUnmarkedPictureEditor:
        public IPictureEditor
{
public:
    TUnmarkedPictureEditor(TUnmarkedPicture * picture, size_t pictureIndex, TPicturesProject * pictureProject);

    virtual const QImage & getPicture() const;
    virtual void accept();

private:
    TUnmarkedPicture * picture;
    size_t pictureIndex;
    TPicturesProject * pictureProject;

    static struct TFoo {
        TFoo()
        {
            int a = 0;
            int b = a;
            a = b;
        }
    } foo;
};

#endif // UNMARKEDPICTUREEDITOR_H
