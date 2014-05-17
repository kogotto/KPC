#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "picturesproject.h"
#include "unmarkedmodel.h"
#include "markedmodel.h"
#include "pictureeditor.h"
#include "picturewidget.h"

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

    void unmarkedListDoubleClicked(QModelIndex index);
    void markedListDoubleClicked(QModelIndex index);

    void closePictureWidgetSlot();

    void appendSlot();

protected:

private:

    bool closePictureProject();
    void openPictureProject(const QString & path);

    void createPictureWidget();

    bool changed;

    TPictureWidget * pictureWidget;

    TPicturesProject * pictureProject;

    TUnmarkedModel * unmarkedModel;
    TMarkedModel * markedModel;
};

#endif // MAINWINDOW_H
