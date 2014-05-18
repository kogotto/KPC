#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "picturesproject.h"
#include "unmarkedmodel.h"
#include "markedmodel.h"
#include "pictureeditor.h"

class TPictureWidget;
class IPictureEditor;

class MainWindow:
        public QMainWindow,
        private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openSlot();
    void saveSlot();

    void unmarkedListObjectSelectSlot(const QModelIndex & index);
    void markedListObjectSelectSlot(const QModelIndex & index);

    void unmarkedListDoubleClickedSlot(const QModelIndex & index);
    void markedListDoubleClickedSlot(const QModelIndex & index);

    void getNextPicture(IPictureEditor *&nextPicture);

    void closePictureWidgetSlot();

protected:

private:

    bool closePictureProject();
    void openPictureProject(const QString & path);

    void createPictureWidget();

    IPictureEditor *createUnmarkedEditor(int row);

    bool changed;

    TPictureWidget * pictureWidget;

    TPicturesProject * pictureProject;

    TUnmarkedModel * unmarkedModel;
    TMarkedModel * markedModel;
};

#endif // MAINWINDOW_H
