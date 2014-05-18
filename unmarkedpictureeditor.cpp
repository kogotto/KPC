#include "unmarkedpictureeditor.h"

#include "picturestructs.h"
#include "picturesproject.h"
#include "markedmodel.h"
#include "unmarkedmodel.h"

TUnmarkedPictureEditor::TUnmarkedPictureEditor(TUnmarkedPicture *picture,
                                               size_t pictureIndex,
                                               TPicturesProject *pictureProject):
    picture(picture),
    pictureIndex(pictureIndex),
    pictureProject(pictureProject),
    markedModel(0),
    unmarkedModel(0)
{
    setRect(QRect());
}

const QImage &TUnmarkedPictureEditor::getPicture() const
{
    return picture->picture;
}

const QString &TUnmarkedPictureEditor::getName() const
{
    return picture->name;
}

void TUnmarkedPictureEditor::accept()
{
    unmarkedModel->beginRemoveRows(QModelIndex(), pictureIndex, pictureIndex);
    markedModel->beginInsertRows(QModelIndex(), markedModel->rowCount(), markedModel->rowCount());
    TMarkedPicture * markedPicture = pictureProject->makeMarked(pictureIndex);
    markedPicture->objects.clear();
    markedPicture->objects.push_back(getRect());
    unmarkedModel->endRemoveRows();
    markedModel->endInsertRows();
}

void TUnmarkedPictureEditor::setMarkedModel(TMarkedModel *markedModel)
{
    this->markedModel = markedModel;
}

void TUnmarkedPictureEditor::setUnmarkedModel(TUnmarkedModel *unmarkedModel)
{
    this->unmarkedModel = unmarkedModel;
}


