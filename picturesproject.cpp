#include "picturesproject.h"

#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <algorithm>
#include <assert.h>

TPicturesProject::TPicturesProject(const QString & dirPath)
{
    QDir dir(dirPath);
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

}

IPictureEditor TPicturesProject::getUnmarkedEditor(size_t row)
{
    return IPictureEditor(unmarkedPictures[row].picture);
}

IPictureEditor TPicturesProject::getMarkedEditor(size_t row)
{
    return IPictureEditor(markedPictures[row].picture);
}

void TPicturesProject::append()
{
}

void TPicturesProject::loadPictures(const QDir & dir, const QStringList & pictureNameList)
{
    for (int i = 0; i < pictureNameList.size(); ++i)
    {
        const QString fileName(pictureNameList[i]);
        const QString fullFileName = dir.absoluteFilePath(fileName);
        QFile pictureFile(fullFileName);
        if (!pictureFile.exists()) {
            continue;
        }

        unmarkedPictures.push_back(TUnmarkedPicture(fileName,QImage(fileName)));
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


