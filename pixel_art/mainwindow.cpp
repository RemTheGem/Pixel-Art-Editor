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
#include <QActionGroup>

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
    // Toolbar
    QToolBar *toolbar = addToolBar("Palette");
    QAction *pickColor = toolbar->addAction("Pick Color");
    QAction *eraseBoard = toolbar->addAction("Clear Canvas");
    QAction *saveDrawing = toolbar->addAction("Save Drawing");
    QAction *brushAction = toolbar->addAction("Brush");
    QAction *eraserAction = toolbar->addAction("Eraser");
    // UI
    brushAction->setChecked(true);
    brushAction->setCheckable(true);
    eraserAction->setCheckable(true);
    canvas->setTool(PixelCanvas::Tool::Brush);
    QActionGroup *toolGroup = new QActionGroup(this);
    toolGroup->setExclusive(true);
    toolGroup->addAction(brushAction);
    toolGroup->addAction(eraserAction);

    //Toolbar actions
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
    connect(brushAction, &QAction::triggered, [=](){
        canvas->setTool(PixelCanvas::Tool::Brush);
    });
    connect(eraserAction, &QAction::triggered, [=](){
        canvas->setTool(PixelCanvas::Tool::Eraser);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}