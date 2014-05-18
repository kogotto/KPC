#ifndef MARKEDMODEL_H
#define MARKEDMODEL_H

#include <QAbstractListModel>

class TPicturesProject;

class TMarkedModel:
        public QAbstractListModel
{
    friend class TUnmarkedPictureEditor;
public:
    explicit TMarkedModel(TPicturesProject * pp);

    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:

   TPicturesProject * pp;
};

#endif // MARKEDMODEL_H
