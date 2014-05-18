#include "markedmodel.h"
#include "picturesproject.h"

#include <assert.h>

TMarkedModel::TMarkedModel(TPicturesProject *pp):
    pp(pp)
{
    assert(pp != 0);
}

int TMarkedModel::rowCount(const QModelIndex &) const
{
    return pp->markedPictures.size();
}

QVariant TMarkedModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return pp->markedPictures[index.row()].name;
    }

    return QVariant();
}

