#include "functions.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardItem>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QtQuick/QQuickPaintedItem>
#include <QList>
#include <QVector>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QListWidget>

//^ libraries,classes,and header files

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow() //ui termiantion
{
    delete ui;
}

void MainWindow::on_pushButton_5_clicked() // class select / browse button
{
    QStringList class_ = QFileDialog::getOpenFileNames(  //open up file browser with QFileDialog
                            this,                         //and assign selected file paths to a QStringList of images variable
                            "Select one or more files to open",
                            "/home",                      // default directory
                            "Classes (*.names)");         //filetypes elligible to be selected by user

    filemodel = new QFileSystemModel(this);
    filemodel->setReadOnly(false);

    QStringListModel *model = new QStringListModel();
    model->setStringList(class_);
    ui->listView->setModel(model);
}

void MainWindow::on_listView_activated(const QModelIndex &index)
{

}

void MainWindow::on_pushButton_7_clicked() // image browse / select button
{
    QStringList images = QFileDialog::getOpenFileNames(   //open up file browser with QFileDialog
                                this,                     //and assign selected file paths to a QStringList of images variable
                                "Select one or more files to open",
                                "/home",     // default directory
                                "Images (*.jpg *.jpeg);;PNG (*.png)"); //filetypes elligible to be selected by user

    filemodel = new QFileSystemModel(this); //create a new filemodel
    filemodel->setReadOnly(true); //Filter to disable editing
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs); //remove unwanted directory paths
    ui->listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //To disable editing of file names
    QStringListModel *model = new QStringListModel(); // create a string list model which will store selected image file paths
    model->setStringList(images); // fill the model with file paths that user has selected
    ui->listWidget->addItems(images); // display users selection

}

void MainWindow::on_listView_2_activated(const QModelIndex &index) // image display pane
{

}

void MainWindow::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}

void MainWindow::on_pushButton_8_clicked() //image save button
{

}



void MainWindow::on_listWidget_clicked(const QModelIndex &index) // list widget / image file pane
{
    QList <QListWidgetItem*> items=ui->listWidget->selectedItems(); //input file paths from list widget to QList

    QString imagePath = listTraversal(items,"0"); // Use traversal function on selected item from list widget

    scene = new QGraphicsScene(this); // create new graphics scene

    scene->addPixmap(imagePath); // convert imagepath text into a pixmap scene

    scene->setSceneRect(image.rect()); // create a rectangle on graphics view for the image

    ui->graphicsView->setScene(scene); // fill graphics view with the image
}
