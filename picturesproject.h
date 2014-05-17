#ifndef PICTURESPROJECT_H
#define PICTURESPROJECT_H

#include <vector>
#include <utility>
#include <QImage>
#include <QString>
#include <QDir>

#include "picturestructs.h"

class QDir;
class QFile;

class IPictureEditor;

class TPicturesProject
{
    friend class TUnmarkedModel;
    friend class TMarkedModel;
    friend class MainWindow;

public:
    explicit TPicturesProject(const QString & dirPath);
    void save() const;

    IPictureEditor * createUnmarkedEditor(size_t row);
    IPictureEditor * createMarkedEditor(size_t row);

    TMarkedPicture * makeMarked(size_t index);

    void append();

private:


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

    QDir dir;

    typedef std::vector<TUnmarkedPicture> TUnmarkedPictures;
    TUnmarkedPictures unmarkedPictures;

    typedef std::vector<TMarkedPicture> TMarkedPictures;
    TMarkedPictures markedPictures;

};

#endif // PICTURESPROJECT_H
