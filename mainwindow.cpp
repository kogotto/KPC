#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <assert.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    changed(false),
    pictureWidget(0),
    pictureProject(0),
    unmarkedModel(0),
    markedModel(0)
{
    setupUi(this);

    openPictureProject("C:\\tp\\proj\\KPC\\new_gate");

    connect(actionOpen, SIGNAL(triggered()),
            this, SLOT(openSlot()));

    connect(actionSave, SIGNAL(triggered()),
            this, SLOT(saveSlot()));

    connect(unmarkedList, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(unmarkedListObjectSelectSlot(const QModelIndex &)));

    connect(markedList, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(markedListObjectSelectSlot(const QModelIndex &)));

    connect(button, SIGNAL(clicked()),
            this, SLOT(appendSlot()));

}

MainWindow::~MainWindow()
{
    closePictureProject();
}

void MainWindow::openSlot()
{
    QFileDialog openDirectoryDialog(
                this,
                "Open pictures dir",
                "c:\\tp\\proj\\KPC",
                "");
    openDirectoryDialog.setFileMode(QFileDialog::DirectoryOnly);

    QStringList pathList;
    if (openDirectoryDialog.exec()) {
        pathList = openDirectoryDialog.selectedFiles();
    }

    if (pathList.empty()) {
        return;
    }

    QString path = pathList[0];

    label->setText(path);


    closePictureProject();
    openPictureProject(path);
}

void MainWindow::saveSlot()
{
    if (pictureProject == 0) {
        return;
    }

    pictureProject->save();
    changed = false;
}

void MainWindow::unmarkedListObjectSelectSlot(const QModelIndex & index)
{
    label->setText(pictureProject->unmarkedPictures[index.row()].name);
    if (pictureWidget == 0) {
        return;
    }

    pictureWidget->setPictureEditor(
                pictureProject->createUnmarkedEditor(index.row())
                );
}

void MainWindow::markedListObjectSelectSlot(const QModelIndex &index)
{
    label->setText(pictureProject->markedPictures[index.row()].name);
    if (pictureWidget == 0){
        return;
    }

    pictureWidget->setPictureEditor(
                pictureProject->createMarkedEditor(index.row())
                );
}

void MainWindow::unmarkedListDoubleClicked(QModelIndex index)
{
    if (pictureWidget == 0)
    {
        createPictureWidget();
    }

    pictureWidget->setPictureEditor(
                pictureProject->createUnmarkedEditor(index.row())
                );
}

void MainWindow::markedListDoubleClicked(QModelIndex index)
{
    if (pictureWidget == 0) {
        createPictureWidget();
    }

    pictureWidget->setPictureEditor(
                pictureProject->createMarkedEditor(index.row())
                );
}

void MainWindow::closePictureWidgetSlot()
{
    pictureWidget = 0;
}

void MainWindow::appendSlot()
{
    unmarkedModel->append();
    markedModel->append();
}


bool MainWindow::closePictureProject()
{
    if (pictureProject == 0) {
        return true;
    }

    if (changed) {

        const int result = QMessageBox::question(
                    this,
                    "Save changes",
                    "Save changes?",
                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                    QMessageBox::Save
                    );

        //TODO better replace "switch" by "if"
        switch (result) {
        case QMessageBox::Save:
            saveSlot();
            break;
        case QMessageBox::Discard:
            // do nothing, just return true
            break;
        case QMessageBox::Cancel:
            return false;
        default:
            assert(false);
        }

    }

    delete pictureProject;
    pictureProject = 0;

    delete markedModel;
    markedModel = 0;

    delete unmarkedModel;
    unmarkedModel = 0;

    return true;

}

void MainWindow::openPictureProject(const QString &path)
{
    pictureProject = new TPicturesProject(path);
    unmarkedModel = new TUnmarkedModel(pictureProject);
    unmarkedList->setModel(unmarkedModel);
    markedModel = new TMarkedModel(pictureProject);
    markedList->setModel(markedModel);
}

void MainWindow::createPictureWidget()
{
    pictureWidget = new TPictureWidget(0, Qt::Window);
    pictureWidget->setAttribute(Qt::WA_DeleteOnClose);
    pictureWidget->setWindowModality(Qt::NonModal);
    pictureWidget->setGeometry(100,100,200,200);

    connect(pictureWidget, SIGNAL(closeSignal()),
            this, SLOT(closePictureWidgetSlot()));

    pictureWidget->show();
    pictureWidget->repaint();
}
