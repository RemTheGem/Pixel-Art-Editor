#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PixelCanvas.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QToolBar>
#include <QAction>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto canvas = new PixelCanvas(this);
    setCentralWidget(canvas);

    QToolBar *toolbar = addToolBar("Palette");
    QAction *pickColor = toolbar->addAction("Pick Color");
    QAction *eraseBoard = toolbar->addAction("Clear Canvas");

    connect(pickColor, &QAction::triggered, [=]() {
        QColor color = QColorDialog::getColor(Qt::white, this);
        if (color.isValid()) {
            canvas->setColor(color);
        }
    });
    connect(eraseBoard, &QAction::triggered, [=](){
        canvas->clear();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}