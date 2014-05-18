#ifndef UNMARKEDPICTUREEDITOR_H
#define UNMARKEDPICTUREEDITOR_H

#include "pictureeditor.h"

class TUnmarkedPicture;
class TPicturesProject;
class TMarkedModel;
class TUnmarkedModel;

class TUnmarkedPictureEditor:
        public IPictureEditor
{
public:
    TUnmarkedPictureEditor(TUnmarkedPicture * picture, size_t pictureIndex, TPicturesProject * pictureProject);

    virtual const QImage & getPicture() const;
    virtual void accept();

    void setMarkedModel(TMarkedModel * markedModel);
    void setUnmarkedModel(TUnmarkedModel * unmarkedModel);

private:
    TUnmarkedPicture * picture;
    size_t pictureIndex;
    TPicturesProject * pictureProject;
    TMarkedModel * markedModel;
    TUnmarkedModel * unmarkedModel;
};

#endif // UNMARKEDPICTUREEDITOR_H
