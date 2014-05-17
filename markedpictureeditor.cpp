#include "markedpictureeditor.h"

#include "picturestructs.h"

TMarkedPictureEditor::TMarkedPictureEditor(TMarkedPicture *picture):
    picture(picture)
{
}

const QImage &TMarkedPictureEditor::getPicture() const
{
    return picture->picture;
}

void TMarkedPictureEditor::accept()
{
    picture->objects.clear();
    picture->objects.push_back(getRect());
}
