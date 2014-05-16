#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <assert.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    pictureProject(0),
    unmarkedModel(0),
    markedModel(0)
{
    setupUi(this);
    //pictureProject->load("C:\\tp\\proj\\KPC\\pictures");

    //unmarkedList->setModel(unmarkedModel);
    //markedList->setModel(markedModel);

    QString s(QString::number(horizontalLayout->count()));
    horizontalLayout->addWidget(pictureWidget );

    connect(actionOpen, SIGNAL(triggered()),
            this, SLOT(openSlot()));

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

void MainWindow::unmarkedListObjectSelectSlot(const QModelIndex & index)
{
    pictureEditor = pictureProject->getUnmarkedEditor(index.row());
    label->setText(pictureProject->unmarkedPictures[index.row()].name);
}

void MainWindow::markedListObjectSelectSlot(const QModelIndex &index)
{
    pictureEditor = pictureProject->getMarkedEditor(index.row());
    label->setText(pictureProject->markedPictures[index.row()].name);
}

void MainWindow::appendSlot()
{
    unmarkedModel->append();
    markedModel->append();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;

    painter.begin(pictureWidget);
    painter.drawImage(0,0, pictureEditor.getPicture());
    painter.end();
}

bool MainWindow::closePictureProject()
{
    if (pictureProject == 0) {
        return true;
    }

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
        // save and return true
        break;
    case QMessageBox::Discard:
        // do nothing, just return true
        break;
    case QMessageBox::Cancel:
        return false;
    default:
        assert(false);
    };

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
