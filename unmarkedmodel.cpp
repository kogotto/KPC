#include "unmarkedmodel.h"
#include "picturesproject.h"

#include <assert.h>

TUnmarkedModel::TUnmarkedModel(TPicturesProject *pp):
    pp(pp)
{
    assert(pp != 0);
}

int TUnmarkedModel::rowCount(const QModelIndex &) const
{
    return pp->unmarkedPictures.size();
}

QVariant TUnmarkedModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return pp->unmarkedPictures[index.row()].name;
    }

    return QVariant();
}

void TUnmarkedModel::append()
{
    const size_t rowIndex = pp->unmarkedPictures.size();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    pp->append();
    endInsertRows();
}
