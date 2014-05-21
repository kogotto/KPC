#include "picturesproject.h"

#include <QFileInfo>
#include <QTextStream>
#include <algorithm>
#include <assert.h>

#include "markedpictureeditor.h"
#include "unmarkedpictureeditor.h"

TPicturesProject::TPicturesProject(const QString & dirPath):
    dir(dirPath)
{
    if (!dir.exists()) {
        assert(false);
    }

    QDir goodDir(dir.absoluteFilePath("good"));
    if (!goodDir.exists()) {
        return;
    }

    QStringList pictureNameList = goodDir.entryList(QDir::Files, QDir::Name);
    loadPictures(goodDir, pictureNameList);

    QFile goodDatFile(dir.absoluteFilePath("good.dat"));
    if (!goodDatFile.exists()) {
        return;
    }

    readGoodDatFile(goodDatFile);

    for (TMarkedPictures::reverse_iterator it = markedPictures.rbegin(); it != markedPictures.rend(); ++it) {

        TUnmarkedPictures::iterator unmarkedPicturesEnd = unmarkedPictures.end();
        TUnmarkedPictures::iterator findedIt = std::find_if(
                    unmarkedPictures.begin(),
                    unmarkedPicturesEnd,
                    TFinder((*it).name));

        if (findedIt == unmarkedPicturesEnd) {
            markedPictures.erase(it.base());
            continue;
        }

        (*it).picture = (*findedIt).picture;
        unmarkedPictures.erase(findedIt);
    }
}

void TPicturesProject::save() const
{
    makeBackup();
    QFile goodDatFile(dir.absoluteFilePath(QString("good.dat")));
    goodDatFile.open(QIODevice::WriteOnly);
    QTextStream stream(&goodDatFile);

    for (TMarkedPictures::const_iterator it = markedPictures.begin(); it != markedPictures.end(); ++it) {
        const TMarkedPicture & picture = *it;
        stream << "good/" << picture.name <<  " ";
        const size_t objectCount = picture.objects.size();
        stream << objectCount;
        for (size_t i = 0; i < objectCount; ++i) {
            const QRect & rect = picture.objects[i];
            stream << " " << rect.left() << " " << rect.top() << " " << rect.width() << " " << rect.height();
        }
        stream << "\n";
    }
}

TUnmarkedPictureEditor *TPicturesProject::createUnmarkedEditor(size_t row)
{
    return new TUnmarkedPictureEditor(&unmarkedPictures[row], row, this);
}

TMarkedPictureEditor *TPicturesProject::createMarkedEditor(size_t row)
{
    return new TMarkedPictureEditor(&markedPictures[row]);
}

TMarkedPicture *TPicturesProject::makeMarked(size_t index)
{
    TUnmarkedPicture & unmarkedPicture = unmarkedPictures[index];

    markedPictures.push_back(TMarkedPicture(
                                 unmarkedPicture.name,
                                 unmarkedPicture.picture)
                             );
    unmarkedPictures.erase(unmarkedPictures.begin() + index);

    return &markedPictures.back();
}

void TPicturesProject::append()
{
}

void TPicturesProject::loadPictures(const QDir & dir, const QStringList & pictureNameList)
{
//    std::vector<QString>
    for (int i = 0; i < pictureNameList.size(); ++i)
    {
        const QString fileName(pictureNameList[i]);
        const QString fullFileName = dir.absoluteFilePath(fileName);
        QFile pictureFile(fullFileName);
        if (!pictureFile.exists()) {
            continue;
        }

        QImage pic;
        if (pic.load(fullFileName)) {
            unmarkedPictures.push_back(TUnmarkedPicture(fileName, pic));
        }
    }
}

void TPicturesProject::readGoodDatFile(QFile & file)
{
    file.open(QIODevice::ReadOnly);
    QTextStream fileStream(&file);

    while(!fileStream.atEnd()) {
        QString string(fileStream.readLine());
        QTextStream stringStream(&string, QIODevice::ReadOnly);

        markedPictures.push_back(TMarkedPicture());
        TMarkedPictures::reference currentMarkedPicture = markedPictures.back();

        QString pictureFileName;
        stringStream >> pictureFileName;
        QFileInfo pictureFileInfo(pictureFileName);
        currentMarkedPicture.name = pictureFileInfo.fileName();

        int objectsSize = 0;
        stringStream >> objectsSize;
        for (int i = 0; i < objectsSize; ++i) {
            int left = 0;
            stringStream >> left;
            int top = 0;
            stringStream >> top;
            int width = 0;
            stringStream >> width;
            int height = 0;
            stringStream >> height;
            currentMarkedPicture.objects.push_back(QRect(left, top, width, height));
        }
    }
}

void TPicturesProject::makeBackup() const
{
    QFile goodDatFile(dir.absoluteFilePath(QString("good.dat")));
    if (!goodDatFile.exists()) {
        return;
    }

    goodDatFile.rename(dir.absoluteFilePath(QString("good.dat.bak")));
}


