#ifndef TPICTURE_WIDGET_H
#define TPICTURE_WIDGET_H

#include <QWidget>

class IPictureEditor;

class TPictureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TPictureWidget(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~TPictureWidget();
    void setPictureEditor(IPictureEditor * pictureEditor);

signals:
    void closeSignal();

public slots:

protected:
    virtual void closeEvent(QCloseEvent *);
    virtual void paintEvent(QPaintEvent *);

private:
    void deletePreviousEditor();
    IPictureEditor * pictureEditor;

};

#endif // TPICTURE_WIDGET_H
