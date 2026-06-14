#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PixelCanvas.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QToolBar>
#include <QAction>
#include <QColorDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto canvas = new PixelCanvas(this);
    canvas->setFixedSize(800, 800);
    QWidget *container = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(container);

    layout->addStretch();
    layout->addWidget(canvas);
    layout->addStretch();

    setCentralWidget(container);

    QToolBar *toolbar = addToolBar("Palette");
    QAction *pickColor = toolbar->addAction("Pick Color");
    QAction *eraseBoard = toolbar->addAction("Clear Canvas");
    QAction *saveDrawing = toolbar->addAction("Save Drawing");

    connect(pickColor, &QAction::triggered, [=]() {
        QColor color = QColorDialog::getColor(Qt::white, this);
        if (color.isValid()) {
            canvas->setColor(color);
        }
    });
    connect(eraseBoard, &QAction::triggered, [=](){
        canvas->clear();
    });
    connect(saveDrawing, &QAction::triggered, [=]() {
        canvas->saveImage();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}