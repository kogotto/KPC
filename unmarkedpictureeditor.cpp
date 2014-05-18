#include "unmarkedpictureeditor.h"

#include "picturestructs.h"
#include "picturesproject.h"

TUnmarkedPictureEditor::TUnmarkedPictureEditor(TUnmarkedPicture *picture,
                                               size_t pictureIndex,
                                               TPicturesProject *pictureProject):
    picture(picture),
    pictureIndex(pictureIndex),
    pictureProject(pictureProject)
{
}

const QImage &TUnmarkedPictureEditor::getPicture() const
{
    return picture->picture;
}

void TUnmarkedPictureEditor::accept()
{
    TMarkedPicture * markedPicture = pictureProject->makeMarked(pictureIndex);
    markedPicture->objects.clear();
    markedPicture->objects.push_back(getRect());
}


