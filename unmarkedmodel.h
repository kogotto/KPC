#ifndef UNMARKEDMODEL_H
#define UNMARKEDMODEL_H

#include <QAbstractListModel>

class TPicturesProject;

class TUnmarkedModel:
        public QAbstractListModel
{
    friend class TUnmarkedPictureEditor;
public:
    explicit TUnmarkedModel(TPicturesProject * pp);

    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void append();

private:

   TPicturesProject * pp;
};

#endif // UNMARKEDMODEL_H
