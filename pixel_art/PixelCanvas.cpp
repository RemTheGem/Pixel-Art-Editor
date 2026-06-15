#include "PixelCanvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QColorDialog>
#include <QImage>
#include <QFileDialog>

PixelCanvas::PixelCanvas(QWidget *parent)
    : QWidget(parent)
{

    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            pixels[y][x] = Qt::white;
        }
    }

    setMouseTracking(true);
}
void PixelCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {

            QRect rect(
                x * pixelSize,
                y * pixelSize,
                pixelSize,
                pixelSize
                );

            painter.fillRect(rect, pixels[y][x]);
            painter.drawRect(rect);
        }
    }
}
void PixelCanvas::mousePressEvent(QMouseEvent *event)
{
    isDrawing = true;

    int x = event->position().x() / pixelSize;
    int y = event->position().y() / pixelSize;

    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        switch(currentTool){
        case Tool::Brush:
            pixels[y][x] = currentColor;
            break;
        case Tool::Eraser:
            pixels[y][x] = Qt::white;
            break;
        }
        update();
    }

}
void PixelCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (!isDrawing) return;

    int x = event->position().x() / pixelSize;
    int y = event->position().y() / pixelSize;

    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        switch(currentTool){
        case Tool::Brush:
            pixels[y][x] = currentColor;
            break;
        case Tool::Eraser:
            pixels[y][x] = Qt::white;
            break;
        }
        update();
    }
}
void PixelCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    isDrawing = false;
}
void PixelCanvas::clear()
{
    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            pixels[y][x] = Qt::white;
        }
    }
    update();
}
void PixelCanvas::saveImage()
{
    QImage image(gridSize * pixelSize, gridSize * pixelSize, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);

    for (int y = 0; y<gridSize; y++){
        for (int x = 0; x<gridSize; x++){
            QRect rect(
                x * pixelSize,
                y * pixelSize,
                pixelSize,
                pixelSize);
            painter.fillRect(rect, pixels[y][x]);
        }
    }
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save Image",
        "",
        "PNG Files (*.png)");
    if(!fileName.isEmpty()){
        if(!fileName.endsWith(".png")){
            fileName += ".png";
        }
        image.save(fileName);
    }
}
void PixelCanvas::setTool(Tool tool){
    currentTool = tool;
}