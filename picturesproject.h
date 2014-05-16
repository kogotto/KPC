#ifndef PICTURESPROJECT_H
#define PICTURESPROJECT_H

#include <vector>
#include <utility>
#include <QImage>
#include <QString>

#include "pictureeditor.h"

class QDir;
class QFile;

class TPicturesProject
{
    friend class TUnmarkedModel;
    friend class TMarkedModel;
    friend class MainWindow;

public:
    explicit TPicturesProject(const QString & dirPath);
    void save() const;

    IPictureEditor getUnmarkedEditor(size_t row);
    IPictureEditor getMarkedEditor(size_t row);

    void append();

private:

    struct TUnmarkedPicture {
        TUnmarkedPicture(QString name, QImage picture):
            name(name),
            picture(picture)
        {}

        QString name;
        QImage picture;
    };

    struct TMarkedPicture {
        QString name;
        QImage picture;
        std::vector<QRect> objects;
    };

    struct TFinder {
        TFinder(const QString & name): name(name)
        {}

        bool operator() (const TUnmarkedPicture & up) {
            return up.name == name;
        }

    private:
        QString name;
    };

    void loadPictures(const QDir & dir, const QStringList & pictureNameList);
    void readGoodDatFile(QFile & file);

    typedef std::vector<TUnmarkedPicture> TUnmarkedPictures;
    TUnmarkedPictures unmarkedPictures;

    typedef std::vector<TMarkedPicture> TMarkedPictures;
    TMarkedPictures markedPictures;

};

#endif // PICTURESPROJECT_H
