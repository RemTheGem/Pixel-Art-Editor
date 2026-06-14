#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PixelCanvas.h"
#include <QMouseEvent>
#include <QPaintEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto canvas = new PixelCanvas(this);
    setCentralWidget(canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}