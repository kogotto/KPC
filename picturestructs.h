#ifndef PICTURESTRUCTS_H
#define PICTURESTRUCTS_H

#include <QString>
#include <QImage>
#include <QRect>
#include <vector>

struct TUnmarkedPicture {
    TUnmarkedPicture(QString name, QImage picture):
        name(name),
        picture(picture)
    {}

    QString name;
    QImage picture;
};

struct TMarkedPicture {
    TMarkedPicture(){}
    TMarkedPicture(QString name, QImage picture):
        name(name),
        picture(picture)
    {}

    QString name;
    QImage picture;
    std::vector<QRect> objects;
};

#endif // PICTURESTRUCTS_H
